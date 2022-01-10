#include"../Include/ATL/AstralDirectX12Factory.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX12::DX12ConstantBuffer::~DX12ConstantBuffer()
{
	if (m_pHeap != nullptr)
		m_pHeap->Release();
}

bool AstralLayerDirectX12::DX12ConstantBuffer::CreateConstantBuffer(
    ID3D12Device* Device, 
    ATL_RESOURCE_DESC& Desc, 
    const void* pSrcData)
{
    //リソース作成
	if (this->CreateResource(Device, Desc, pSrcData) == false)
		return false;

    //ヒープデスク準備
    D3D12_DESCRIPTOR_HEAP_DESC desc{};
    desc.NumDescriptors = m_ObjectSize;
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    desc.NodeMask = 0;

    //ヒープ作成
    HRESULT hr = Device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pHeap));
    if (FAILED(hr))
        return false;

    for (unsigned long long i = 0; i < m_ObjectSize; i++)
    {
        //ビューデスク
        D3D12_CONSTANT_BUFFER_VIEW_DESC cbv{};
        cbv.SizeInBytes = CalcAlignment(m_StructureSize) * m_Width;
        cbv.BufferLocation = m_pResourceArray->GetGPUVirtualAddress() + static_cast<unsigned long long>(cbv.SizeInBytes) * i;
        
        //ハンドル
        D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pHeap->GetCPUDescriptorHandleForHeapStart();
        handle.ptr += 
            i * static_cast<unsigned long long>(Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

        //作成
        Device->CreateConstantBufferView(&cbv, handle);
    }

	return true;
}

void AstralLayerDirectX12::DX12ConstantBuffer::GetHandle(
    void** ppOut, 
    int Handle)
{
    switch (Handle)
    {
    case RESOURCE_DRAW:
        *ppOut = m_pHeap;
        break;
    case RESOURCE_DATA:
        *ppOut = m_pResourceArray;
        break;
    default:
        break;
    }
}
