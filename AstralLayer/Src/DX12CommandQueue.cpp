#include"../Include/ATL/AstralDirectX12Factory.h"
#include"../Include/AstralDebug.h"

//==========================================================================
// �R�}���h�L���[
//==========================================================================
AstralLayerDirectX12::DX12CommandQueue::~DX12CommandQueue()
{
}

void AstralLayerDirectX12::DX12CommandQueue::GetHandle(
    void** ppOut, 
    int Handle)
{
	Handle;
	*ppOut = m_pCommandQueue.Get();
}

bool AstralLayerDirectX12::DX12CommandQueue::ExecuteCommandLists(
    unsigned int NumCommandLists,
    AstralLayer::ATLICommandList* const* ppCommandLists)
{
    //�R�}���h���擾
    for (unsigned int i = 0; i < NumCommandLists; i++)
    {
        if(ppCommandLists[i] == nullptr)
            continue;

        //�R�}���h����
        ID3D12CommandList* command = nullptr;

        //�R�}���h�擾
        reinterpret_cast<AstralRHI::RHICommandList*>(ppCommandLists[i])->
            GetHandle(reinterpret_cast<void**>(&command), 0);

        //�R�}���h���s
        m_pCommandQueue->ExecuteCommandLists(1, &command);
    }
    return true;
}

void AstralLayerDirectX12::DX12CommandQueue::Release()
{
    m_pCommandQueue.Reset();
    delete this;
}

bool AstralLayerDirectX12::DX12CommandQueue::Create(
    ID3D12Device* pDevice)
{
    //�R�}���h�L���[�f�X�N����
    D3D12_COMMAND_QUEUE_DESC qdesc{};
    qdesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    qdesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    qdesc.NodeMask = 0;
    qdesc.Priority = 0;

    //�R�}���h�L���[�쐬
    if (FAILED(pDevice->CreateCommandQueue(&qdesc, IID_PPV_ARGS(&m_pCommandQueue))))
        return false;

    return true;
}
