#include"../Include/ATL/AstralDirectX12Factory.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX12::DX12SIMPLEResource::~DX12SIMPLEResource()
{
    for (unsigned int i = 0; i < m_ArraySize; i++)
    {
        m_pResource[i].Reset();
    }

    m_pHeap.Reset();

    delete[] m_pResource;
}

unsigned int AstralLayerDirectX12::DX12SIMPLEResource::SetSubResource(
    const void* pData, unsigned int SetByteSize)
{
    //‘‚«ž‚Ý‚Å‚«‚È‚¢
    pData;
    SetByteSize;
    return UINT_MAX;
}

bool AstralLayerDirectX12::DX12SIMPLEResource::UpdateSubResource(
    unsigned int SubResourceID, unsigned int MoveByte, const void* pData, unsigned int UpdateByteSize)
{
    //‘‚«ž‚Ý‚Å‚«‚È‚¢
    SubResourceID;
    MoveByte;
    pData;
    UpdateByteSize;
    return false;
}

void AstralLayerDirectX12::DX12SIMPLEResource::GetHandle(
    void** ppOut, 
    int Handle)
{
    if (Handle == RTV_HEAP)
    {
        *ppOut = m_pHeap.Get();
    }
    else if (Handle >= RTV_RESOURCE)
    {
        *ppOut = m_pResource[(Handle - 1) % m_ArraySize].Get();
    }
}

void AstralLayerDirectX12::DX12SIMPLEResource::Release()
{
    delete this;
}
