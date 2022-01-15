#include"../Include/ATL/AstralDirectX12Factory.h"
#include"../Include/AstralDebug.h"

//==========================================================================
// コマンドキュー
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
    //コマンドを取得
    for (unsigned int i = 0; i < NumCommandLists; i++)
    {
        if(ppCommandLists[i] == nullptr)
            continue;

        //コマンド準備
        ID3D12CommandList* command = nullptr;

        //コマンド取得
        reinterpret_cast<AstralRHI::RHICommandList*>(ppCommandLists[i])->
            GetHandle(reinterpret_cast<void**>(&command), 0);

        //コマンド実行
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
    //コマンドキューデスク準備
    D3D12_COMMAND_QUEUE_DESC qdesc{};
    qdesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    qdesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    qdesc.NodeMask = 0;
    qdesc.Priority = 0;

    //コマンドキュー作成
    if (FAILED(pDevice->CreateCommandQueue(&qdesc, IID_PPV_ARGS(&m_pCommandQueue))))
        return false;

    return true;
}
