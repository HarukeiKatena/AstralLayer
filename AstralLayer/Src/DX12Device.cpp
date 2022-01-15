#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"
#include "../Include/ATL/AstralDirectX.h"

//==========================================================================
// DX12用サポート
//==========================================================================
D3D12_HEAP_TYPE ConvType(ATL_RESOURCE_TYPE type)
{
    switch (type)
    {
    case ATL_RESOURCE_TYPE::DEFAULT: return D3D12_HEAP_TYPE_DEFAULT;
    case ATL_RESOURCE_TYPE::UPLOAD: return D3D12_HEAP_TYPE_UPLOAD;
    case ATL_RESOURCE_TYPE::READBACK: return D3D12_HEAP_TYPE_READBACK;
    default: return D3D12_HEAP_TYPE_DEFAULT;
    }
}

D3D12_HEAP_PROPERTIES CreateHeapProp(D3D12_HEAP_TYPE Type)
{
    D3D12_HEAP_PROPERTIES prop;
    prop.Type = Type;
    prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    prop.CreationNodeMask = 1;
    prop.VisibleNodeMask = 1;
    return prop;
}



void AstralLayerDirectX12::DX12Device::GetHandle(
    void** ppOut, 
    int Handle)
{
    Handle;
    *ppOut = m_pDevice.Get();
}

//==========================================================================
// デバイス
//==========================================================================
AstralLayerDirectX12::DX12Device::~DX12Device()
{
    /*
    //メモリーリークチェック用
    ID3D12DebugDevice* debugInterface;
    if (SUCCEEDED(m_pDevice->QueryInterface(&debugInterface)))
    {
        debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
        debugInterface->Release();
    }*/
}

AstralLayer::ATLIResource* AstralLayerDirectX12::DX12Device::CreateResource(
    ATL_RESOURCE_DESC& Desc,
    const void* pSrcData)
{
    //エラーチェック
    assert(Desc.Flag != ATL_RESOURCE_FLAG::UNKNOWN);

    //作成処理
    if (Desc.Flag == ATL_RESOURCE_FLAG::CONSTANTBUFFER)//定数バッファ
    {
        DX12ConstantBuffer* pR = new DX12ConstantBuffer();
        if (pR->CreateConstantBuffer(
            m_pDevice.Get(),
            Desc,
            pSrcData) == false)
        {
            ATLAssertMessage(false, "Resourceの作成に失敗しました");
            delete pR;
            pR = nullptr;
        }
        return pR;
    }
    else if (Desc.Flag == ATL_RESOURCE_FLAG::VERTEXBUFFER)//頂点バッファ
    {
        DX12VertexBuffer* pVB = new DX12VertexBuffer();
        if (pVB->CreateVertexBuffer(
            m_pDevice.Get(),
            Desc,
            pSrcData) == false)
        {
            ATLAssertMessage(false, "Resourceの作成に失敗しました");
            delete pVB;
            pVB = nullptr;
        }
        return pVB;
    }
    else if (Desc.Flag == ATL_RESOURCE_FLAG::INDEXBUFFER)//インデックスバッファ
    {
        DX12IndexBuffer* pIB = new DX12IndexBuffer();
        if (pIB->CreateIndexBuffer(
            m_pDevice.Get(),
            Desc,
            pSrcData) == false)
        {
            ATLAssertMessage(false, "Resourceの作成に失敗しました");
            delete pIB;
            pIB = nullptr;
        }
        return pIB;
    }
    else if (Desc.Flag == ATL_RESOURCE_FLAG::TEXTURE2D)//テクスチャ
    {
        DX12Texture2D* pTex = new DX12Texture2D();
        if (pTex->CreateTexture(
            m_pDevice.Get(),
            Desc,
            pSrcData) == false)
        {
            ATLAssertMessage(false, "Resourceの作成に失敗しました");
            delete pTex;
            pTex = nullptr;
        }
        return pTex;
    }
    else
    {
        return nullptr;
    }
}

AstralLayer::ATLIPipeLine* AstralLayerDirectX12::DX12Device::CreatePipeLine(
    ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc)
{
    //パイプライン作成
    DX12PipeLine* pOut = new DX12PipeLine();
    if (pOut->Create(m_pDevice.Get(), Desc) == false)
    {
        ATLAssertMessage(false, "PipeLineの作成に失敗しました");
        delete pOut;
        pOut = nullptr;
    }
    return pOut;
}

AstralLayer::ATLIDepthStencilView* AstralLayerDirectX12::DX12Device::CreateDepthStencilView(
    ATL_DEPTH_STENCIL_VIEW_DESC& Desc)
{
    //デプスステンシルビュー作成
    DX12DepthStencilView* pOut = new DX12DepthStencilView();
    if (pOut->Create(m_pDevice.Get(), Desc) == false)
    {
        ATLAssertMessage(false, "DepthStencilViewの作成に失敗しました");
        delete pOut;
        pOut = nullptr;
    }

    return pOut;
}

AstralLayer::ATLICommandList* AstralLayerDirectX12::DX12Device::CreateCommandList()
{
    //コマンドリスト作成
    DX12CommandList* pOut = new DX12CommandList();
    if (pOut->Create(m_pDevice.Get()) == false)
    {
        ATLAssertMessage(false, "CommandListの作成に失敗しました");
        delete pOut;
        pOut = nullptr;
    }

    return pOut;
}

AstralLayer::ATLICommandQueue* AstralLayerDirectX12::DX12Device::CreateCommandQueue()
{   
    //コマンドキュー作成
    DX12CommandQueue* pOut = new DX12CommandQueue();
    if (pOut->Create(m_pDevice.Get()) == false)
    {
        ATLAssertMessage(false, "CommandQueueの作成に失敗しました");
        delete pOut;
        pOut = nullptr;
    }
    return pOut;
}

AstralLayer::ATLISwapChain* AstralLayerDirectX12::DX12Device::CreateSwapChain(
    ATL_SWAPCHAIN_DESC& Desc, 
    AstralLayer::ATLICommandQueue* pCommandQueue)
{
    //スワップチェイン作成
    DX12SwapChain* pOut = new DX12SwapChain();
    if (pOut->Create(m_pDevice.Get(), Desc, pCommandQueue) == false)
    {
        ATLAssertMessage(false, "SwapChainの作成に失敗しました");
        delete pOut;
        pOut = nullptr;
    }

    return pOut;
}

AstralLayer::ATLIFence* AstralLayerDirectX12::DX12Device::CreateFence()
{
    //フェンス作成
    DX12Fence* pOut = new DX12Fence();
    if (pOut->Create(m_pDevice.Get()) == false)
    {
        ATLAssertMessage(false, "フェンスの作成に失敗しました");
        delete pOut;
        pOut = nullptr;
    }
    return pOut;
}

AstralLayer::ATLIRenderTargetView* AstralLayerDirectX12::DX12Device::CreateRenderTargetView(
    AstralLayer::ATLISwapChain* SwapChain,
    unsigned int ScreenWidth,
    unsigned int ScreenHeight)
{
    //スワップチェイン取得　NULLなら取得しない
    IDXGISwapChain3* swap = nullptr;
    if (SwapChain != nullptr)
        reinterpret_cast<AstralRHI::RHISwapChain*>(SwapChain)->GetHandle(reinterpret_cast<void**>(&swap), 0);

    //レンダーターゲットビュー作成
    DX12RenderTargetView* pOut = new DX12RenderTargetView();
    if (pOut->Create(m_pDevice.Get(), swap, ScreenWidth, ScreenHeight) == false)
    {
        ATLAssertMessage(false, "レンダーターゲットビューの作成に失敗しました");
        delete pOut;
        pOut = nullptr;
    }

    return pOut;
}

void AstralLayerDirectX12::DX12Device::Release()
{
    delete this;
}

bool AstralLayerDirectX12::DX12Device::Create(IDXGIFactory1* pFactory)
{
    //アダプター準備
    IDXGIAdapter1* pAdapter;
    IDXGIAdapter1* vAdapters[8] = {};

    unsigned int id = 0;
  
    for (unsigned int i = 0; S_OK == pFactory->EnumAdapters1(i, &pAdapter); i++)
    {
        DXGI_ADAPTER_DESC1 desc{};
        pAdapter->GetDesc1(&desc);

        if (desc.Flags == DXGI_ADAPTER_FLAG_SOFTWARE)
        {
            pAdapter->Release();
            continue;
        }

        for (unsigned int c = 0; c <= id; c++)
        {
            if (vAdapters[c] == nullptr)
            {
                vAdapters[c] = pAdapter;
                break;
            }

            DXGI_ADAPTER_DESC1 check{};
            vAdapters[c]->GetDesc1(&check);

            //ビデオメモリがチェック先より大きい場合
            if (check.DedicatedVideoMemory < desc.DedicatedVideoMemory)
            {
                IDXGIAdapter1* save = vAdapters[c];
                vAdapters[c] = pAdapter;
                vAdapters[c + 1] = save;
                desc = check;
            }
        }

        id++;

        //IDが8を超えたらアダプターの列挙を終える
        if (id >= 8)
            break;
    }

    //デバイス作成
    for (unsigned int i = 0; i < id; i++)
    {
        if (m_pDevice != nullptr)
        {
            vAdapters[i]->Release();
            vAdapters[i] = nullptr;
            continue;
        }

        D3D12CreateDevice(
            vAdapters[i],
            D3D_FEATURE_LEVEL_11_0,
            IID_PPV_ARGS(&m_pDevice)
        );
        
        vAdapters[i]->Release();
        vAdapters[i] = nullptr;
    }

    if (m_pDevice == nullptr)
        return false;

    m_gi = ATL_GRAPHIC_INTERFACE::DirectX12;

    

    return true;
}
