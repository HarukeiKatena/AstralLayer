#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

//==========================================================================
// インデックスバッファー
//==========================================================================
AstralLayerDirectX12::DX12IndexBuffer::~DX12IndexBuffer()
{
    delete[] m_pView;
}

bool AstralLayerDirectX12::DX12IndexBuffer::CreateIndexBuffer(
    ID3D12Device* pDevice, 
    ATL_RESOURCE_DESC& Desc, 
    const void* pSrcData)
{
    //リソース作成
    if (this->CreateResource(pDevice, Desc, pSrcData) == false)
        return false;

    //ビュー情報セット
    m_pView = new D3D12_INDEX_BUFFER_VIEW[m_ObjectSize];
    for (unsigned int i = 0; i < m_ObjectSize; i++)
    {
        m_pView[i].BufferLocation = m_pResourceArray->GetGPUVirtualAddress();
        m_pView[i].SizeInBytes = m_StructureSize * m_Width;
        m_pView[i].Format = DXGI_FORMAT_R32_UINT;
    }
    return true;
}

void AstralLayerDirectX12::DX12IndexBuffer::GetHandle(
    void** ppOut,
    int Handle)
{
    switch (Handle)
    {
    case RESOURCE_DRAW:
        *ppOut = &m_pView[Handle];
        break;
    case RESOURCE_DATA:
        *ppOut = m_pResourceArray.Get();
        break;
    default:
        break;
    }
}
