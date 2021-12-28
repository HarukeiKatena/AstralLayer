#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

//==========================================================================
// ���_�V�F�[�_
//==========================================================================
AstralLayerDirectX12::DX12VertexBuffer::~DX12VertexBuffer()
{
    delete[] m_pView;
}

bool AstralLayerDirectX12::DX12VertexBuffer::CreateVertexBuffer(
    ID3D12Device* Device, 
    ATL_RESOURCE_DESC& Desc, 
    const void* pSrcData)
{
    //���\�[�X�쐬
    if (this->CreateResource(Device, Desc, pSrcData) == false)
        return false;

    //�r���[���Z�b�g
    m_pView = new D3D12_VERTEX_BUFFER_VIEW[m_ObjectSize];
    for (unsigned int i = 0; i < m_ObjectSize; i++)
    {
        m_pView[i].BufferLocation = m_pResourceArray[i].GetGPUVirtualAddress();
        m_pView[i].SizeInBytes = m_StructureSize * m_Width;
        m_pView[i].StrideInBytes = m_StructureSize;
    }

    return true;
}

void AstralLayerDirectX12::DX12VertexBuffer::GetHandle(
    void** ppOut,
    int Handle)
{    
    switch (Handle)
    {
    case RESOURCE_DRAW:
        *ppOut = &m_pView[Handle];
        break;
    case RESOURCE_DATA:
        *ppOut = &m_pResourceArray;
        break;
    default:
        break;
    }
}
