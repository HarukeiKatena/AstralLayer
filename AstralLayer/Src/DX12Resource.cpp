#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

const unsigned long AstralLayerDirectX12::DX12Resource::CalcAlignment(unsigned long size)
{
    return size + DECREMENT_ALIGNMENT & NOT_DECREMENT_ALIGNMENT;
}


AstralLayerDirectX12::DX12Resource::~DX12Resource()
{
    //更新、読み込みの場合アンマップ
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

    //書き込み
    memcpy(
        &m_pSubResource[(CalcAlignment(m_StructureSize) * m_UseIndex)], 
        pData, 
        SetByteSize == 0 ? m_StructureSize : SetByteSize);

    //インデックス保管
    unsigned int rindex = m_UseIndex;

    //次のインデックスに移動　最大値の場合はループ
    m_UseIndex = (m_UseIndex + 1) % m_ObjectSize;

    return rindex;
}

bool AstralLayerDirectX12::DX12Resource::UpdateSubResource(
    unsigned int SubResourceID, 
    unsigned int MoveByte, 
    const void* pData,
    unsigned int UpdateByteSize)
{
    //アライメント
    unsigned int alignment = CalcAlignment(m_StructureSize);

    //エラー
    assert(SubResourceID < m_ObjectSize);
    assert(MoveByte < alignment* m_Width);
    assert(m_pSubResource != nullptr);

    //書き込み
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
    //エラーチェック
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

    //変数セット
    m_StructureSize = Desc.ByteStructure;
    m_Width = Desc.Width;
    m_ObjectSize = Desc.NumObject;
    m_Type = Desc.Type;
    m_Flag = Desc.Flag;

    //タイプがUPLOADの場合ダブルバッファにする
    if (m_Type == ATL_RESOURCE_TYPE::UPLOAD)
        m_ObjectSize *= 2;

    //プロパティ準備
    D3D12_HEAP_PROPERTIES prop{};
    prop.Type = D3D12_HEAP_TYPE_UPLOAD;
    prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    prop.CreationNodeMask = 1;
    prop.VisibleNodeMask = 1;

    //リソースデスク準備
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

    //幅を事前に計算しておく
    rdesc.Width =
        static_cast<unsigned long long>(m_StructureSize)*
        static_cast<unsigned long long>(m_Width)*
        static_cast<unsigned long long>(m_ObjectSize);

    if (Desc.Flag == ATL_RESOURCE_FLAG::CONSTANTBUFFER)
    {
        //定数バッファーはアライメントする
        rdesc.Width = CalcAlignment(static_cast<unsigned long>(rdesc.Width));
    }

    //リソース作成
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

    //マップ
    m_pResourceArray->Map(0, nullptr, reinterpret_cast<void**>(&m_pSubResource));

    //データ更新
    if (pSrcData != nullptr)
    {
        for (unsigned int o = 0; o < m_ObjectSize; o++)
        {
            //すべてのオブジェクトを初期状態に書き込む
            this->UpdateSubResource(o, 0, pSrcData, Desc.ByteStructure * Desc.Width * Desc.Height);
        }
    }

    //タイプがUPLOADではない場合はUnmapしてSubResourceにNULLを入れる
    if (m_Type != ATL_RESOURCE_TYPE::UPLOAD)
    {
        m_pResourceArray->Unmap(0, nullptr);
        m_pSubResource = nullptr;
    }

    return true;
}