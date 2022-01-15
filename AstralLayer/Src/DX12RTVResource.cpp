#include"../Include/ATL/AstralDirectX12Factory.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX12::DX12RTVResource::~DX12RTVResource()
{
    for (unsigned int i = 0; i < m_ArraySize; i++)
    {
        m_pRenderTargets[i].Reset();
    }

    m_pHeap.Reset();

    delete[] m_pRenderTargets;
}

unsigned int AstralLayerDirectX12::DX12RTVResource::SetSubResource(
    const void* pData, unsigned int SetByteSize)
{
    //‘‚«ž‚Ý‚Å‚«‚È‚¢
    pData;
    SetByteSize;
    return UINT_MAX;
}

bool AstralLayerDirectX12::DX12RTVResource::UpdateSubResource(
    unsigned int SubResourceID, unsigned int MoveByte, const void* pData, unsigned int UpdateByteSize)
{
    //‘‚«ž‚Ý‚Å‚«‚È‚¢
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
    m_pParentRTV->GetHandle(ppOut, Handle);
}

void AstralLayerDirectX12::DX12RTVResource::Release()
{
    delete this;
}
