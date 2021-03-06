#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

D3D12_DSV_DIMENSION AstralLayerDirectX12::DX12DepthStencilView::ConvDimension(ATL_DSV_DIMENSION dimension)
{
    switch (dimension)
    {
    case ATL_DSV_DIMENSION::TEXTURE1D: return D3D12_DSV_DIMENSION_TEXTURE1D;
    case ATL_DSV_DIMENSION::TEXTURE2D: return D3D12_DSV_DIMENSION_TEXTURE2D;
    case ATL_DSV_DIMENSION::TEXTURE2DMS: return D3D12_DSV_DIMENSION_TEXTURE2DMS;
    default: return D3D12_DSV_DIMENSION_UNKNOWN;
    }
}

//==========================================================================
// デプスステンシルビュー
//==========================================================================
AstralLayerDirectX12::DX12DepthStencilView::~DX12DepthStencilView()
{
}

void AstralLayerDirectX12::DX12DepthStencilView::GetHandle(
    void** ppOut, 
    int Handle)
{
    m_pDSV.GetHandle(ppOut, Handle);
}

void AstralLayerDirectX12::DX12DepthStencilView::Release()
{
    delete this;
}

AstralLayer::ATLIResource* AstralLayerDirectX12::DX12DepthStencilView::GetResource(AstralLayer::ATLIFence* pFence)
{
    return nullptr;
}

bool AstralLayerDirectX12::DX12DepthStencilView::Create(
    ID3D12Device* pDevice, 
    ATL_DEPTH_STENCIL_VIEW_DESC& Desc)
{
	HRESULT hr = S_OK;

    m_pDSV.m_ArraySize = 1;

	//デスクリプターヒープの作成
	{
		D3D12_DESCRIPTOR_HEAP_DESC dhdesc{};
		dhdesc.NumDescriptors = 1;
		dhdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		dhdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		hr = pDevice->CreateDescriptorHeap(&dhdesc, IID_PPV_ARGS(&m_pDSV.m_pHeap));
		if (FAILED(hr))
			return false;
	}

    //デスクリプタヒープのリソース作成
	{
        //ヒーププロパティの設定
        D3D12_HEAP_PROPERTIES prop{};
        prop.Type = D3D12_HEAP_TYPE_DEFAULT;
        prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        prop.CreationNodeMask = 1;
        prop.VisibleNodeMask = 1;

        //リソースの設定
        D3D12_RESOURCE_DESC desc{};
        desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        desc.Alignment = 0;
        desc.Width = Desc.Width;
        desc.Height = Desc.Height;
        desc.DepthOrArraySize = 1;
        desc.MipLevels = 0;
        desc.Format = DXGI_FORMAT_D32_FLOAT;
        desc.SampleDesc = {1,0};
        desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
        desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

        //クリア値の設定
        D3D12_CLEAR_VALUE clearvalue{};
        clearvalue.Format = DXGI_FORMAT_D32_FLOAT;
        clearvalue.DepthStencil.Depth = 1.0f;
        clearvalue.DepthStencil.Stencil = 0;

        //リソース作成
        m_pDSV.m_pResource = new Microsoft::WRL::ComPtr<ID3D12Resource>[m_pDSV.m_ArraySize];
        hr = pDevice->CreateCommittedResource(
            &prop,
            D3D12_HEAP_FLAG_NONE,
            &desc,
            D3D12_RESOURCE_STATE_DEPTH_WRITE,
            &clearvalue,
            IID_PPV_ARGS(&m_pDSV.m_pResource[0])
        );
        if (FAILED(hr))
            return false;
    }

    {
        //深度ステンシルビューの設定
        D3D12_DEPTH_STENCIL_VIEW_DESC dsvdesc{};
        dsvdesc.Format = DXGI_FORMAT_D32_FLOAT;
        dsvdesc.ViewDimension = ConvDimension(Desc.Dimension);
        dsvdesc.Flags = D3D12_DSV_FLAG_NONE;

        //ヒープにセット
        pDevice->CreateDepthStencilView(
            m_pDSV.m_pResource[0].Get(),
            &dsvdesc,
            m_pDSV.m_pHeap.Get()->GetCPUDescriptorHandleForHeapStart()
        );
    }

    return true;
}

