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
    //rtv�擾
    ID3D12DescriptorHeap* heap = nullptr;
    reinterpret_cast<AstralRHI::RHIRenderTargetView*>(rtv)->
        GetHandle(reinterpret_cast<void**>(&heap), RTV_HEAP);

    //�f�o�C�X�擾
    ID3D12Device* device = nullptr;
    heap->GetDevice(IID_PPV_ARGS(&device));

    //rtv�n���h������
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

    //dsv�n���h������
    D3D12_CPU_DESCRIPTOR_HANDLE handle{};
    handle = heap->GetCPUDescriptorHandleForHeapStart();

    return handle;
}

AstralLayerDirectX12::DX12CommandList::~DX12CommandList()
{
    //�����[�X
    if (m_pAllocator != nullptr)
        m_pAllocator->Release();

    if (m_pCommandList != nullptr)
        m_pCommandList->Release();
}

bool AstralLayerDirectX12::DX12CommandList::Create(ID3D12Device* Device)
{
    //�A���P�[�^�[�쐬
    HRESULT hr = Device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&m_pAllocator)
    );
    if (FAILED(hr))
        return false;

    //�R�}���h���X�g�쐬
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
    //�p�C�v���C���ƃ��[�g�V�O�l�`���[�擾
    ID3D12PipelineState* pipeline = nullptr;
    ID3D12RootSignature* root = nullptr;
    if (pPipeLine != nullptr)//null�ł��ʉ߂���
    {
        //RHI�̃p�C�v���C���擾
        AstralRHI::RHIPipeLine* rhipp = reinterpret_cast<AstralRHI::RHIPipeLine*>(pPipeLine);

        //�p�C�v���C��
        rhipp->GetHandle(reinterpret_cast<void**>(&pipeline), PIPELINE_PIPELINE);

        //���[�g�V�O�l�`���[�擾
        rhipp->GetHandle(reinterpret_cast<void**>(&root), PIPELINE_ROOTSIGNATURE);
    }

    //�t�F���X
    unsigned int* back = nullptr;
    reinterpret_cast<AstralRHI::RHIFence*>(pFence)->
        GetHandle(reinterpret_cast<void**>(&back), FENCE_BACKBUFFER);
    m_BackBuffer = *back;

    //���Z�b�g
    if (FAILED(m_pAllocator->Reset()))
        return false;

    if (FAILED(m_pCommandList->Reset(m_pAllocator, pipeline)))
        return false;

    //���[�g�V�O�l�`���[�Z�b�g
    m_pCommandList->SetGraphicsRootSignature(root);

    return true;
}

void AstralLayerDirectX12::DX12CommandList::SetResource(
    unsigned int StartRootParametorIndex,
    AstralLayer::ATLIResource* pResource,
    unsigned int NumResourceIDs,
    unsigned int* ResourceIDs)
{
    //�萔�A�e�N�X�`���ȊO�͎󂯎��Ȃ�
    if (pResource->GetFlag() != ATL_RESOURCE_FLAG::CONSTANTBUFFER &&
        pResource->GetFlag() != ATL_RESOURCE_FLAG::TEXTURE2D)
        return;

    //�f�X�N���v�^�[�q�[�v�擾
    ID3D12DescriptorHeap* heap = nullptr;
    reinterpret_cast<AstralRHI::RHIResource*>(pResource)->
        GetHandle(reinterpret_cast<void**>(&heap), AstralLayerDirectX12::RESOURCE_DRAW);

    //�f�o�C�X�擾
    ID3D12Device* device = nullptr;
    heap->GetDevice(IID_PPV_ARGS(&device));

    //�n���h���擾
    for (unsigned int i = 0; i < NumResourceIDs; i++)
    {
        //���\�[�XID���Ȃ����0��
        unsigned int rid = 0;
        if (ResourceIDs != nullptr)
            rid = ResourceIDs[i];

        //�n���h���擾
        D3D12_GPU_DESCRIPTOR_HANDLE handle = heap->GetGPUDescriptorHandleForHeapStart();
        handle.ptr +=
            static_cast<unsigned long long>(rid) *
            static_cast<unsigned long long>(device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

        //���\�[�X�Z�b�g
        m_pCommandList->SetDescriptorHeaps(1, &heap);
        m_pCommandList->SetGraphicsRootDescriptorTable(StartRootParametorIndex + i, handle);
    }
    
    //�f�o�C�X���
    device->Release();
}

void AstralLayerDirectX12::DX12CommandList::SetViewports(
    unsigned int NumViewports, 
    ATL_VIEWPORT* pViewports)
{
    //�Z�b�g
    m_pCommandList->RSSetViewports(
        NumViewports, 
        reinterpret_cast<D3D12_VIEWPORT*>(pViewports));
}

void AstralLayerDirectX12::DX12CommandList::SetScissorRects(
    unsigned int NumRects, 
    ATL_RECT* pRects)
{
    //�Z�b�g
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
    //���_�o�b�t�@�[����
    if (pVertex->GetFlag() != ATL_RESOURCE_FLAG::VERTEXBUFFER)
        return;

    //�r���[���󂯎��
    D3D12_VERTEX_BUFFER_VIEW* view = nullptr;
    reinterpret_cast<AstralRHI::RHIResource*>(pVertex)->
        GetHandle(reinterpret_cast<void**>(&view), ResourceID);

    //�Z�b�g
    m_pCommandList->IASetVertexBuffers(0, 1, view);
}

void AstralLayerDirectX12::DX12CommandList::SetIndexBuffer(
    AstralLayer::ATLIResource* pIndexBuffer, unsigned int ResourceID)
{
    //�C���f�b�N�X�o�b�t�@�[����
    if (pIndexBuffer->GetFlag() != ATL_RESOURCE_FLAG::INDEXBUFFER)
        return;

    //�r���[���󂯎��
    D3D12_INDEX_BUFFER_VIEW* view = nullptr;
    reinterpret_cast<AstralRHI::RHIResource*>(pIndexBuffer)->
        GetHandle(reinterpret_cast<void**>(&view), ResourceID);

    //�Z�b�g
    m_pCommandList->IASetIndexBuffer(view);
}

void AstralLayerDirectX12::DX12CommandList::ResourceBarrier(ATL_RESOURCE_BARRIER& barrier)
{
    //�o���A�f�X�N����
    D3D12_RESOURCE_BARRIER rb{};
    rb.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    rb.Transition.StateBefore = ConvState(barrier.StateBefore);
    rb.Transition.StateAfter = ConvState(barrier.StateAfter);
    rb.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    //�o���A�Z�b�g
    if (barrier.Type == ATL_BARRIER_TYPE::RENDER_TARGET)
    {
        rb.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        reinterpret_cast<AstralRHI::RHIResource*>(barrier.pResource)->
            GetHandle(reinterpret_cast<void**>(&rb.Transition.pResource), RTVRESOURCE_RESOURCE);
    }

    //�o���A�Z�b�g
    m_pCommandList->ResourceBarrier(1, &rb);
}

void AstralLayerDirectX12::DX12CommandList::SetRenderTargets(
    AstralLayer::ATLIRenderTargetView* pRenderTargetView, 
    AstralLayer::ATLIDepthStencilView* pDepthStencilView)
{
    //rtv�n���h��
    D3D12_CPU_DESCRIPTOR_HANDLE rtv = GetRTVHandle(pRenderTargetView);
    
    //�f�v�X�X�e���V���r���[�̗L���ŏ�����ς���
    if (pDepthStencilView != nullptr)
    {
        //dsv�n���h��
        D3D12_CPU_DESCRIPTOR_HANDLE dsv = GetDSVHandle(pDepthStencilView);

        //RTV�Z�b�g
        m_pCommandList->OMSetRenderTargets(1, &rtv, FALSE, &dsv);
    }
    else
    {
        //RTV�Z�b�g(DSV��NULL)
        m_pCommandList->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
    }
}

void AstralLayerDirectX12::DX12CommandList::ClearRenderTargetView(
    AstralLayer::ATLIRenderTargetView* pRenderTargetView, 
    const float ColorRGBA[4])
{
    //rtv
    D3D12_CPU_DESCRIPTOR_HANDLE rtv = GetRTVHandle(pRenderTargetView);

    //RTV�Z�b�g
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

    //DSV�Z�b�g
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
    //�h���[�R�[��
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
    //�h���[�R�[��
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
