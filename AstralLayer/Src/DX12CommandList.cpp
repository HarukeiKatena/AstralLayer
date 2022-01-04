#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

D3D12_RESOURCE_STATES AstralLayerDirectX12::DX12CommandList::ConvState(
    ATL_RESOURCE_STATE state)
{
    switch (state)
    {
    case ATL_RESOURCE_STATE::PRESENT:       return D3D12_RESOURCE_STATE_PRESENT;
    case ATL_RESOURCE_STATE::RENDER_TARGET: return D3D12_RESOURCE_STATE_RENDER_TARGET;
    default: return D3D12_RESOURCE_STATE_PRESENT;
    }
}

D3D12_PRIMITIVE_TOPOLOGY AstralLayerDirectX12::DX12CommandList::ConvTopology(
    ATL_PRIMITIVE_TOPOLOGY t)
{
    switch (t)
    {
    case ATL_PRIMITIVE_TOPOLOGY::POINTLIST:     return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
    case ATL_PRIMITIVE_TOPOLOGY::LINELIST:      return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
    case ATL_PRIMITIVE_TOPOLOGY::LINESTRIP:     return D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
    case ATL_PRIMITIVE_TOPOLOGY::TRIANGLELIST:  return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    case ATL_PRIMITIVE_TOPOLOGY::TRIANGLESTRIP: return D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    default: return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
    }
}

D3D12_CPU_DESCRIPTOR_HANDLE AstralLayerDirectX12::DX12CommandList::GetRTVHandle(
    AstralLayer::ATLIRenderTargetView* rtv)
{
    //rtv取得
    ID3D12DescriptorHeap* heap = nullptr;
    reinterpret_cast<AstralRHI::RHIRenderTargetView*>(rtv)->
        GetHandle(reinterpret_cast<void**>(&heap), RTV_HEAP);

    //デバイス取得
    ID3D12Device* device = nullptr;
    heap->GetDevice(IID_PPV_ARGS(&device));

    //rtvハンドル準備
    D3D12_CPU_DESCRIPTOR_HANDLE handle{};
    handle = heap->GetCPUDescriptorHandleForHeapStart();
    handle.ptr +=
        static_cast<unsigned long long>(m_BackBuffer) *
        static_cast<unsigned long long>(device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));

    device->Release();
    return handle;
}

D3D12_CPU_DESCRIPTOR_HANDLE AstralLayerDirectX12::DX12CommandList::GetDSVHandle(
    AstralLayer::ATLIDepthStencilView* dsv)
{
    //dsv
    ID3D12DescriptorHeap* heap = nullptr;
    reinterpret_cast<AstralRHI::RHIDepthStencilView*>(dsv)->
        GetHandle(reinterpret_cast<void**>(&heap), DSV_HEAP);

    //dsvハンドル準備
    D3D12_CPU_DESCRIPTOR_HANDLE handle{};
    handle = heap->GetCPUDescriptorHandleForHeapStart();

    return handle;
}

AstralLayerDirectX12::DX12CommandList::~DX12CommandList()
{
    //リリース
    if (m_pAllocator != nullptr)
        m_pAllocator->Release();

    if (m_pCommandList != nullptr)
        m_pCommandList->Release();
}

bool AstralLayerDirectX12::DX12CommandList::Create(ID3D12Device* Device)
{
    //アロケーター作成
    HRESULT hr = Device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&m_pAllocator)
    );
    if (FAILED(hr))
        return false;

    //コマンドリスト作成
    hr = Device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        m_pAllocator,
        nullptr,
        IID_PPV_ARGS(&m_pCommandList)
    );
    if (FAILED(hr))
    {
        this->~DX12CommandList();
        return false;
    }

    m_pCommandList->Close();

    return true;
}

bool AstralLayerDirectX12::DX12CommandList::Reset(
    AstralLayer::ATLIPipeLine* pPipeLine, 
    AstralLayer::ATLIFence* pFence)
{
    //パイプラインとルートシグネチャー取得
    ID3D12PipelineState* pipeline = nullptr;
    ID3D12RootSignature* root = nullptr;
    if (pPipeLine != nullptr)//nullでも通過する
    {
        //RHIのパイプライン取得
        AstralRHI::RHIPipeLine* rhipp = reinterpret_cast<AstralRHI::RHIPipeLine*>(pPipeLine);

        //パイプライン
        rhipp->GetHandle(reinterpret_cast<void**>(&pipeline), PIPELINE_PIPELINE);

        //ルートシグネチャー取得
        rhipp->GetHandle(reinterpret_cast<void**>(&root), PIPELINE_ROOTSIGNATURE);
    }

    //フェンス
    unsigned int* back = nullptr;
    reinterpret_cast<AstralRHI::RHIFence*>(pFence)->
        GetHandle(reinterpret_cast<void**>(&back), FENCE_BACKBUFFER);
    m_BackBuffer = *back;

    //リセット
    if (FAILED(m_pAllocator->Reset()))
        return false;

    if (FAILED(m_pCommandList->Reset(m_pAllocator, pipeline)))
        return false;

    //ルートシグネチャーセット
    m_pCommandList->SetGraphicsRootSignature(root);

    return true;
}

void AstralLayerDirectX12::DX12CommandList::SetResource(
    unsigned int StartRootParametorIndex,
    AstralLayer::ATLIResource* pResource,
    unsigned int NumResourceIDs,
    unsigned int* ResourceIDs)
{
    //定数、テクスチャ以外は受け取らない
    if (pResource->GetFlag() != ATL_RESOURCE_FLAG::CONSTANTBUFFER &&
        pResource->GetFlag() != ATL_RESOURCE_FLAG::TEXTURE2D)
        return;

    //デスクリプターヒープ取得
    ID3D12DescriptorHeap* heap = nullptr;
    reinterpret_cast<AstralRHI::RHIResource*>(pResource)->
        GetHandle(reinterpret_cast<void**>(&heap), AstralLayerDirectX12::RESOURCE_DRAW);

    //デバイス取得
    ID3D12Device* device = nullptr;
    heap->GetDevice(IID_PPV_ARGS(&device));

    //ハンドル取得
    for (unsigned int i = 0; i < NumResourceIDs; i++)
    {
        //リソースIDがなければ0で
        unsigned int rid = 0;
        if (ResourceIDs != nullptr)
            rid = ResourceIDs[i];

        //ハンドル取得
        D3D12_GPU_DESCRIPTOR_HANDLE handle = heap->GetGPUDescriptorHandleForHeapStart();
        handle.ptr +=
            static_cast<unsigned long long>(rid) *
            static_cast<unsigned long long>(device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

        //リソースセット
        m_pCommandList->SetDescriptorHeaps(1, &heap);
        m_pCommandList->SetGraphicsRootDescriptorTable(StartRootParametorIndex + i, handle);
    }
    
    //デバイス解放
    device->Release();
}

void AstralLayerDirectX12::DX12CommandList::SetViewports(
    unsigned int NumViewports, 
    ATL_VIEWPORT* pViewports)
{
    //セット
    m_pCommandList->RSSetViewports(
        NumViewports, 
        reinterpret_cast<D3D12_VIEWPORT*>(pViewports));
}

void AstralLayerDirectX12::DX12CommandList::SetScissorRects(
    unsigned int NumRects, 
    ATL_RECT* pRects)
{
    //セット
    m_pCommandList->RSSetScissorRects(
        NumRects, 
        reinterpret_cast<D3D12_RECT*>(pRects));
}

void AstralLayerDirectX12::DX12CommandList::SetPrimitiveTopology(
    ATL_PRIMITIVE_TOPOLOGY Topology)
{
    m_pCommandList->IASetPrimitiveTopology(ConvTopology(Topology));
}

void AstralLayerDirectX12::DX12CommandList::SetVertexBuffer(
    AstralLayer::ATLIResource* pVertex, 
    unsigned int ResourceID)
{
    //頂点バッファーだけ
    if (pVertex->GetFlag() != ATL_RESOURCE_FLAG::VERTEXBUFFER)
        return;

    //ビューを受け取る
    D3D12_VERTEX_BUFFER_VIEW* view = nullptr;
    reinterpret_cast<AstralRHI::RHIResource*>(pVertex)->
        GetHandle(reinterpret_cast<void**>(&view), ResourceID);

    //セット
    m_pCommandList->IASetVertexBuffers(0, 1, view);
}

void AstralLayerDirectX12::DX12CommandList::SetIndexBuffer(
    AstralLayer::ATLIResource* pIndexBuffer, unsigned int ResourceID)
{
    //インデックスバッファーだけ
    if (pIndexBuffer->GetFlag() != ATL_RESOURCE_FLAG::INDEXBUFFER)
        return;

    //ビューを受け取る
    D3D12_INDEX_BUFFER_VIEW* view = nullptr;
    reinterpret_cast<AstralRHI::RHIResource*>(pIndexBuffer)->
        GetHandle(reinterpret_cast<void**>(&view), ResourceID);

    //セット
    m_pCommandList->IASetIndexBuffer(view);
}

void AstralLayerDirectX12::DX12CommandList::ResourceBarrier(ATL_RESOURCE_BARRIER& barrier)
{
    //バリアデスク準備
    D3D12_RESOURCE_BARRIER rb{};
    rb.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    rb.Transition.StateBefore = ConvState(barrier.StateBefore);
    rb.Transition.StateAfter = ConvState(barrier.StateAfter);
    rb.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    //バリアセット
    if (barrier.Type == ATL_BARRIER_TYPE::RENDER_TARGET)
    {
        rb.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        reinterpret_cast<AstralRHI::RHIResource*>(barrier.pResource)->
            GetHandle(reinterpret_cast<void**>(&rb.Transition.pResource), RTVRESOURCE_RESOURCE);
    }

    //バリアセット
    m_pCommandList->ResourceBarrier(1, &rb);
}

void AstralLayerDirectX12::DX12CommandList::SetRenderTargets(
    AstralLayer::ATLIRenderTargetView* pRenderTargetView, 
    AstralLayer::ATLIDepthStencilView* pDepthStencilView)
{
    //rtvハンドル
    D3D12_CPU_DESCRIPTOR_HANDLE rtv = GetRTVHandle(pRenderTargetView);
    
    //デプスステンシルビューの有無で処理を変える
    if (pDepthStencilView != nullptr)
    {
        //dsvハンドル
        D3D12_CPU_DESCRIPTOR_HANDLE dsv = GetDSVHandle(pDepthStencilView);

        //RTVセット
        m_pCommandList->OMSetRenderTargets(1, &rtv, FALSE, &dsv);
    }
    else
    {
        //RTVセット(DSVはNULL)
        m_pCommandList->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
    }
}

void AstralLayerDirectX12::DX12CommandList::ClearRenderTargetView(
    AstralLayer::ATLIRenderTargetView* pRenderTargetView, 
    const float ColorRGBA[4])
{
    //rtv
    D3D12_CPU_DESCRIPTOR_HANDLE rtv = GetRTVHandle(pRenderTargetView);

    //RTVセット
    m_pCommandList->ClearRenderTargetView(rtv, ColorRGBA, 0, nullptr);
}

void AstralLayerDirectX12::DX12CommandList::ClearDepthStencilView(
    AstralLayer::ATLIDepthStencilView* DepthStencilView, 
    ATL_CLEAR_FLAG ClearFlags,
    float Depth, 
    unsigned char Stencil)
{
    //dsv
    D3D12_CPU_DESCRIPTOR_HANDLE dsv = GetDSVHandle(DepthStencilView);

    //DSVセット
    m_pCommandList->ClearDepthStencilView(
        dsv,
        static_cast<D3D12_CLEAR_FLAGS>(ClearFlags), 
        Depth, 
        Stencil, 
        0, nullptr);
}

void AstralLayerDirectX12::DX12CommandList::DrawInstanced(
    unsigned int VertexCountParInstance, 
    unsigned int InstanceCount, 
    unsigned int StartVertexLocation, 
    unsigned int StartInstanceLocation)
{
    //ドローコール
    m_pCommandList->DrawInstanced(
        VertexCountParInstance,
        InstanceCount,
        StartVertexLocation,
        StartInstanceLocation
    );
}

void AstralLayerDirectX12::DX12CommandList::DrawIndexedInstanced(
    unsigned int IndexCountParInstance, 
    unsigned int InstanceCount, 
    unsigned int StartIndexLocation, 
    unsigned int BaceVertexLocation, 
    unsigned int StartInstanceLocation)
{
    //ドローコール
    m_pCommandList->DrawIndexedInstanced(
        IndexCountParInstance,
        InstanceCount,
        StartIndexLocation,
        BaceVertexLocation,
        StartInstanceLocation
    );
}

bool AstralLayerDirectX12::DX12CommandList::Close()
{
    return FAILED(m_pCommandList->Close());
}

void AstralLayerDirectX12::DX12CommandList::Release()
{
    delete this;
}

void AstralLayerDirectX12::DX12CommandList::GetHandle(
    void** ppOut, 
    int Handle)
{
    switch (Handle)
    {
    case COMMANDLIST_COMMAND:
        *ppOut = m_pCommandList;
        break;
    case COMMANDLIST_ALLOCATOR:
        *ppOut = m_pAllocator;
    default:
        break;
    }
}
