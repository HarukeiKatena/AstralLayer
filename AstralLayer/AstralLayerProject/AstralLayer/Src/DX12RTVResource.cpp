#include"../Include/ATL/AstralDirectX12Factory.h"
#include"../Include/AstralDebug.h"

void AstralLayerDirectX12::DX12RTVResource::SetResource(
    ID3D12Resource* pResource, 
    ID3D12DescriptorHeap* pHeap)
{
    m_pResource = pResource;
    m_pHeap = pHeap;
}

unsigned int AstralLayerDirectX12::DX12RTVResource::SetSubResource(
    const void* pData, unsigned int SetByteSize)
{
    //èëÇ´çûÇ›Ç≈Ç´Ç»Ç¢
    pData;
    SetByteSize;
    return UINT_MAX;
}

bool AstralLayerDirectX12::DX12RTVResource::UpdateSubResource(
    unsigned int SubResourceID, unsigned int MoveByte, const void* pData, unsigned int UpdateByteSize)
{
    //èëÇ´çûÇ›Ç≈Ç´Ç»Ç¢
    SubResourceID;
    MoveByte;
    pData;
    UpdateByteSize;
    return false;
}

void AstralLayerDirectX12::DX12RTVResource::GetHandle(
    void** ppOut, 
    int Handle)
{
    switch (Handle)
    {
    case RTVRESOURCE_HEAP:
        *ppOut = m_pHeap;
        break;
    case RTVRESOURCE_RESOURCE:
        *ppOut = m_pResource;
    default:
        break;
    }
}

void AstralLayerDirectX12::DX12RTVResource::Release()
{
    delete this;
}
