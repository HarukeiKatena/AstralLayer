#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

//==========================================================================
// レンダーターゲットビュー
//==========================================================================
AstralLayerDirectX12::DX12RenderTargetView::~DX12RenderTargetView()
{
    //RTV解放
    for (unsigned int i = 0; i < m_ArraySize; i++)
    {
        if (m_pRenderTargets[i] == nullptr)
        {
            m_pRenderTargets[i]->Release();
            m_pRenderTargets[i] = nullptr;
        }
    }

    //ヒープ解放
    if (m_pHeap != nullptr)
        m_pHeap->Release();

    delete[] m_pRenderTargets;
}

void AstralLayerDirectX12::DX12RenderTargetView::GetHandle(
    void** ppOut, 
    int Handle)
{
    if (Handle == RTV_HEAP)
    {
        *ppOut = m_pHeap;
    }
    else if(Handle >= RTV_RESOURCE)
    {
        *ppOut = m_pRenderTargets[(Handle - 1) % m_ArraySize];
    }
}

AstralLayer::ATLIResource* AstralLayerDirectX12::DX12RenderTargetView::GetResource(
    AstralLayer::ATLIFence* pFence)
{
    //インデックス取得　FenceがNULLの場合は0
    unsigned int index = 0;
    if (pFence != nullptr)
    {
        unsigned int* back = nullptr;
        reinterpret_cast<AstralRHI::RHIFence*>(pFence)->
            GetHandle(reinterpret_cast<void**>(&back), 0);

        index = *back;
    }

    //専用のリソース準備
    DX12RTVResource* pOut = new DX12RTVResource();
    pOut->SetResource(m_pRenderTargets[index], m_pHeap);

    return pOut;
}

void AstralLayerDirectX12::DX12RenderTargetView::Release()
{
    delete this;
}

bool AstralLayerDirectX12::DX12RenderTargetView::Create(
    ID3D12Device* pDevice, 
    IDXGISwapChain* pSwapChain,
    unsigned int ScreenWidth,
    unsigned int ScreenHeight)
{
    //スワップチェインがある際はバッファーカウントを取得して配列数にする
    if (pSwapChain != nullptr)
    {
        DXGI_SWAP_CHAIN_DESC desc{};
        pSwapChain->GetDesc(&desc);
        m_ArraySize = desc.BufferCount;
    }
    else
    {
        m_ArraySize = 1;//ない場合は1
    }

    //ヒープ作成
    D3D12_DESCRIPTOR_HEAP_DESC hdesc{};
    hdesc.NumDescriptors = m_ArraySize;
    hdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    hdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    hdesc.NodeMask = 0;

    HRESULT hr = pDevice->CreateDescriptorHeap(&hdesc, IID_PPV_ARGS(&m_pHeap));
    if (FAILED(hr))
        return false;

    //リソース準備
    m_pRenderTargets = new ID3D12Resource*[m_ArraySize];
    for (unsigned int i = 0; i < m_ArraySize; i++)
    {
        m_pRenderTargets[i] = nullptr;
    }

    //リソース作成
    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pHeap->GetCPUDescriptorHandleForHeapStart();
    if (pSwapChain != nullptr)
    {
        //スワップチェインがある場合
        for (unsigned int i = 0; i < m_ArraySize; i++)
        {
            hr = pSwapChain->GetBuffer(i, IID_PPV_ARGS(&m_pRenderTargets[i]));
            if (FAILED(hr))
            {
                this->~DX12RenderTargetView();
                return false;
            }
            pDevice->CreateRenderTargetView(m_pRenderTargets[i], nullptr, handle);
            handle.ptr += pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        }
    }
    else
    {
        //スワップチェインがない場合
        D3D12_HEAP_PROPERTIES prop;
        prop.Type = D3D12_HEAP_TYPE_DEFAULT;
        prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        prop.CreationNodeMask = 1;
        prop.VisibleNodeMask = 1;

        D3D12_RESOURCE_DESC desc;
        desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        desc.Alignment = 0;
        desc.Width = ScreenWidth;
        desc.Height = ScreenHeight;
        desc.DepthOrArraySize = 1;
        desc.MipLevels = 0;
        desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
        desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

        hr = pDevice->CreateCommittedResource(
            &prop,
            D3D12_HEAP_FLAG_NONE,
            &desc,
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
            nullptr,
            IID_PPV_ARGS(&m_pRenderTargets[0])
        );
        if (FAILED(hr))
        {
            this->~DX12RenderTargetView();
            return false;
        }
        pDevice->CreateRenderTargetView(m_pRenderTargets[0], nullptr, handle);
    }
    
    return true;
}