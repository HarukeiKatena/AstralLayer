#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

const unsigned long AstralLayerDirectX12::DX12Resource::CalcAlignment(unsigned long size)
{
    return size + DECREMENT_ALIGNMENT & NOT_DECREMENT_ALIGNMENT;
}


AstralLayerDirectX12::DX12Resource::~DX12Resource()
{
    //�X�V�A�ǂݍ��݂̏ꍇ�A���}�b�v
    if (m_Type == ATL_RESOURCE_TYPE::UPLOAD || m_Type == ATL_RESOURCE_TYPE::READBACK)
    {
        if (m_pResourceArray != nullptr)
            m_pResourceArray->Unmap(0, nullptr);
    }

    m_pResourceArray->Release();
}

unsigned int AstralLayerDirectX12::DX12Resource::SetSubResource(
    const void* pData, 
    unsigned int SetByteSize)
{
    assert(SetByteSize <= m_StructureSize* m_Width);
    assert(m_pSubResource != nullptr);

    //��������
    memcpy(
        &m_pSubResource[(CalcAlignment(m_StructureSize) * m_UseIndex)], 
        pData, 
        SetByteSize == 0 ? m_StructureSize : SetByteSize);

    //�C���f�b�N�X�ۊ�
    unsigned int rindex = m_UseIndex;

    //���̃C���f�b�N�X�Ɉړ��@�ő�l�̏ꍇ�̓��[�v
    m_UseIndex = (m_UseIndex + 1) % m_ObjectSize;

    return rindex;
}

bool AstralLayerDirectX12::DX12Resource::UpdateSubResource(
    unsigned int SubResourceID, 
    unsigned int MoveByte, 
    const void* pData,
    unsigned int UpdateByteSize)
{
    //�A���C�����g
    unsigned int alignment = CalcAlignment(m_StructureSize);

    //�G���[
    assert(SubResourceID < m_ObjectSize);
    assert(MoveByte < alignment* m_Width);
    assert(m_pSubResource != nullptr);

    //��������
    memcpy(
        &m_pSubResource[(alignment * SubResourceID) + MoveByte], 
        pData, 
        UpdateByteSize == 0 ? m_StructureSize : UpdateByteSize);

    return true;
}

void AstralLayerDirectX12::DX12Resource::Release()
{
    delete this;
}

bool AstralLayerDirectX12::DX12Resource::CreateResource(
    ID3D12Device* pDevice,
    ATL_RESOURCE_DESC& Desc,
    const void* pSrcData)
{
    //�G���[�`�F�b�N
    ATLAssert(Desc.ByteStructure > 0);
    ATLAssert(Desc.Width > 0);
    ATLAssert(Desc.Height > 0);
    ATLAssert(Desc.NumObject > 0);
    ATLAssert(Desc.Type != ATL_RESOURCE_TYPE::UNKNOWN);
    if (Desc.ByteStructure <= 0 ||
        Desc.Width <= 0 ||
        Desc.Height <= 0 ||
        Desc.NumObject <= 0 ||
        Desc.Type == ATL_RESOURCE_TYPE::UNKNOWN)
        return false;

    //�ϐ��Z�b�g
    m_StructureSize = Desc.ByteStructure;
    m_Width = Desc.Width;
    m_ObjectSize = Desc.NumObject;
    m_Type = Desc.Type;
    m_Flag = Desc.Flag;

    //�^�C�v��UPLOAD�̏ꍇ�_�u���o�b�t�@�ɂ���
    if (m_Type == ATL_RESOURCE_TYPE::UPLOAD)
        m_ObjectSize *= 2;

    //�v���p�e�B����
    D3D12_HEAP_PROPERTIES prop{};
    prop.Type = D3D12_HEAP_TYPE_UPLOAD;
    prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    prop.CreationNodeMask = 1;
    prop.VisibleNodeMask = 1;

    //���\�[�X�f�X�N����
    D3D12_RESOURCE_DESC rdesc{};
    rdesc.Alignment = 0;
    rdesc.DepthOrArraySize = 1;
    rdesc.MipLevels = 1;
    rdesc.Format = DXGI_FORMAT_UNKNOWN;
    rdesc.SampleDesc.Count = 1;
    rdesc.SampleDesc.Quality = 0;
    rdesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    rdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    rdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    rdesc.Height = 1;

    //�������O�Ɍv�Z���Ă���
    rdesc.Width =
        static_cast<unsigned long long>(m_StructureSize)*
        static_cast<unsigned long long>(m_Width)*
        static_cast<unsigned long long>(m_ObjectSize);

    if (Desc.Flag == ATL_RESOURCE_FLAG::CONSTANTBUFFER)
    {
        //�萔�o�b�t�@�[�̓A���C�����g����
        rdesc.Width = CalcAlignment(static_cast<unsigned long>(rdesc.Width));
    }

    //���\�[�X�쐬
    HRESULT hr = pDevice->CreateCommittedResource(
        &prop,
        D3D12_HEAP_FLAG_NONE,
        &rdesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_pResourceArray)
    );
    if (FAILED(hr))
        return false;

    //�}�b�v
    m_pResourceArray->Map(0, nullptr, reinterpret_cast<void**>(&m_pSubResource));

    //�f�[�^�X�V
    if (pSrcData != nullptr)
    {
        for (unsigned int o = 0; o < m_ObjectSize; o++)
        {
            //���ׂẴI�u�W�F�N�g��������Ԃɏ�������
            this->UpdateSubResource(o, 0, pSrcData, Desc.ByteStructure * Desc.Width * Desc.Height);
        }
    }

    //�^�C�v��UPLOAD�ł͂Ȃ��ꍇ��Unmap����SubResource��NULL������
    if (m_Type != ATL_RESOURCE_TYPE::UPLOAD)
    {
        m_pResourceArray->Unmap(0, nullptr);
        m_pSubResource = nullptr;
    }

    return true;
}