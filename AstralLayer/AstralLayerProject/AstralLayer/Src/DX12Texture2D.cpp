#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"
#include "../Include/ATL/AstralDirectX.h"


constexpr unsigned int AstralLayerDirectX12::DX12Texture2D::CallRowPitch()
{
    return m_FormatSize * m_Width;
}

constexpr unsigned int AstralLayerDirectX12::DX12Texture2D::CallDepthPitch()
{
    return m_FormatSize * m_Width * m_Height;
}

AstralLayerDirectX12::DX12Texture2D::~DX12Texture2D()
{
	if (m_pTexture != nullptr)
		m_pTexture->Release();
}

unsigned int AstralLayerDirectX12::DX12Texture2D::SetSubResource(
	const void* pData, 
	unsigned int SetByteSize)
{
    SetByteSize;//使わない

    if (m_Type != ATL_RESOURCE_TYPE::UPLOAD)
        return UINT_MAX;
    
    //テクスチャ書き込み
    D3D12_BOX box = { 0,0,0,m_Width,m_Height,1 };
    m_pTexture->WriteToSubresource(0, &box, pData, CallRowPitch(), CallDepthPitch());

    
	return 0;
}

bool AstralLayerDirectX12::DX12Texture2D::UpdateSubResource(
	unsigned int SubResourceID, 
	unsigned int MoveByte, 
	const void* pData, 
	unsigned int UpdateByteSize)
{
    SubResourceID;//使わない
    UpdateByteSize;
    MoveByte;

    if (m_Type != ATL_RESOURCE_TYPE::UPLOAD)
        return false;

    //テクスチャ書き込み
    D3D12_BOX box = { 0,0,0,m_Width,m_Height,1 };
    m_pTexture->WriteToSubresource(0, &box, pData, CallRowPitch(), CallDepthPitch());
	return true;
}

void AstralLayerDirectX12::DX12Texture2D::Release()
{
    delete this;
}

void AstralLayerDirectX12::DX12Texture2D::GetHandle(
    void** ppOut, 
    int Handle)
{
    switch (Handle)
    {
    case TEXTURE2D_HEAP:
        *ppOut = m_pHeap;
        break;
    case TEXTURE2D_TEXTURE:
        *ppOut = m_pTexture;
        break;
    default:
        break;
    }
}

bool AstralLayerDirectX12::DX12Texture2D::CreateTexture(
    ID3D12Device* Device, 
    ATL_RESOURCE_DESC& Desc,
    const void* pSrcData)
{
    //エラーチェック
    ATLAssert(Device != nullptr);
    ATLAssert(Desc.ByteStructure > 0);
    ATLAssert(Desc.Width > 0);
    ATLAssert(Desc.Height > 0);
    ATLAssert(Desc.NumObject == 1);
    ATLAssert(Desc.Type != ATL_RESOURCE_TYPE::UNKNOWN);
    ATLAssert(Desc.Type != ATL_RESOURCE_TYPE::READBACK);
    ATLAssert(Desc.Format != ATL_FORMAT::UNKNOWN);
    if (Device == nullptr ||
        Desc.ByteStructure <= 0 ||
        Desc.Width <= 0 ||
        Desc.Height <= 0 ||
        Desc.NumObject != 1 ||
        Desc.Type == ATL_RESOURCE_TYPE::UNKNOWN ||
        Desc.Type == ATL_RESOURCE_TYPE::READBACK || 
        Desc.Format == ATL_FORMAT::UNKNOWN)
        return false;

    //変数セット
    m_Format = ConvDXGIFormat(Desc.Format);
    m_Width = Desc.Width;
    m_Height = Desc.Height;
    m_FormatSize = Desc.ByteStructure;
    m_Type = Desc.Type;
    m_Flag = ATL_RESOURCE_FLAG::CONSTANTBUFFER;

    //リソースに必要な設定を準備
    D3D12_HEAP_PROPERTIES prop{};
    prop.Type = D3D12_HEAP_TYPE_CUSTOM;
    prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
    prop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
    prop.CreationNodeMask = 0;
    prop.VisibleNodeMask = 0;

    D3D12_RESOURCE_DESC rdesc{};
    rdesc.Alignment = 0;
    rdesc.DepthOrArraySize = 1;
    rdesc.MipLevels = 1;
    rdesc.Format = m_Format;
    rdesc.SampleDesc.Count = 1;
    rdesc.SampleDesc.Quality = 0;
    rdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    rdesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    rdesc.Width = Desc.Width;
    rdesc.Height = Desc.Height;
    rdesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

    //リソース作成
    HRESULT hr = Device->CreateCommittedResource(
        &prop,
        D3D12_HEAP_FLAG_NONE,
        &rdesc,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
        nullptr,
        IID_PPV_ARGS(&m_pTexture)
    );
    if (FAILED(hr))
        return false;

    //データ更新
    if (pSrcData != nullptr)
    {
        D3D12_BOX box = { 0,0,0,m_Width,m_Height,1 };
        m_pTexture->WriteToSubresource(0, &box, pSrcData, CallRowPitch(), CallDepthPitch());
    }

    //ヒープデスク準備
    D3D12_DESCRIPTOR_HEAP_DESC hdesc{};
    hdesc.NumDescriptors = 1;
    hdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    hdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    hdesc.NodeMask = 0;

    //ヒープ作成
    hr = Device->CreateDescriptorHeap(&hdesc, IID_PPV_ARGS(&m_pHeap));
    if (FAILED(hr))
        return false;


    //シェーダーリソースビューの設定
    D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc{};
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvdesc.Format = m_Format;
    srvdesc.Texture2D.MipLevels = 1;
    srvdesc.Texture2D.MostDetailedMip = 0;
    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pHeap->GetCPUDescriptorHandleForHeapStart();
    Device->CreateShaderResourceView(m_pTexture, &srvdesc, handle);

    return true;
}

