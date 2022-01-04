#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"
#include "../Include/ATL/AstralDirectX.h"

//==========================================================================
// DX12�p�T�|�[�g
//==========================================================================
D3D12_HEAP_TYPE ConvType(ATL_RESOURCE_TYPE type)
{
    switch (type)
    {
    case ATL_RESOURCE_TYPE::DEFAULT: return D3D12_HEAP_TYPE_DEFAULT;
    case ATL_RESOURCE_TYPE::UPLOAD: return D3D12_HEAP_TYPE_UPLOAD;
    case ATL_RESOURCE_TYPE::READBACK: return D3D12_HEAP_TYPE_READBACK;
    default: return D3D12_HEAP_TYPE_DEFAULT;
    }
}

D3D12_HEAP_PROPERTIES CreateHeapProp(D3D12_HEAP_TYPE Type)
{
    D3D12_HEAP_PROPERTIES prop;
    prop.Type = Type;
    prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    prop.CreationNodeMask = 1;
    prop.VisibleNodeMask = 1;
    return prop;
}



void AstralLayerDirectX12::DX12Device::GetHandle(
    void** ppOut, 
    int Handle)
{
    Handle;
    *ppOut = m_pDevice;
}

//==========================================================================
// �f�o�C�X
//==========================================================================
AstralLayerDirectX12::DX12Device::~DX12Device()
{
    if (m_pDevice != nullptr)
        m_pDevice->Release();
}

AstralLayer::ATLIResource* AstralLayerDirectX12::DX12Device::CreateResource(
    ATL_RESOURCE_DESC& Desc,
    const void* pSrcData)
{
    //�G���[�`�F�b�N
    assert(Desc.Flag != ATL_RESOURCE_FLAG::UNKNOWN);

    //�쐬����
    if (Desc.Flag == ATL_RESOURCE_FLAG::CONSTANTBUFFER)//�萔�o�b�t�@
    {
        DX12ConstantBuffer* pR = new DX12ConstantBuffer();
        if (pR->CreateConstantBuffer(
            m_pDevice,
            Desc,
            pSrcData) == false)
        {
            ATLAssertMessage(false, "Resource�̍쐬�Ɏ��s���܂���");
            delete pR;
            pR = nullptr;
        }
        return pR;
    }
    else if (Desc.Flag == ATL_RESOURCE_FLAG::VERTEXBUFFER)//���_�o�b�t�@
    {
        DX12VertexBuffer* pVB = new DX12VertexBuffer();
        if (pVB->CreateVertexBuffer(
            m_pDevice,
            Desc,
            pSrcData) == false)
        {
            ATLAssertMessage(false, "Resource�̍쐬�Ɏ��s���܂���");
            delete pVB;
            pVB = nullptr;
        }
        return pVB;
    }
    else if (Desc.Flag == ATL_RESOURCE_FLAG::INDEXBUFFER)//�C���f�b�N�X�o�b�t�@
    {
        DX12IndexBuffer* pIB = new DX12IndexBuffer();
        if (pIB->CreateIndexBuffer(
            m_pDevice,
            Desc,
            pSrcData) == false)
        {
            ATLAssertMessage(false, "Resource�̍쐬�Ɏ��s���܂���");
            delete pIB;
            pIB = nullptr;
        }
        return pIB;
    }
    else if (Desc.Flag == ATL_RESOURCE_FLAG::TEXTURE2D)//�e�N�X�`��
    {
        DX12Texture2D* pTex = new DX12Texture2D();
        if (pTex->CreateTexture(
            m_pDevice,
            Desc,
            pSrcData) == false)
        {
            ATLAssertMessage(false, "Resource�̍쐬�Ɏ��s���܂���");
            delete pTex;
            pTex = nullptr;
        }
        return pTex;
    }
    else
    {
        return nullptr;
    }
}

AstralLayer::ATLIPipeLine* AstralLayerDirectX12::DX12Device::CreatePipeLine(
    ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc)
{
    //�p�C�v���C���쐬
    DX12PipeLine* pOut = new DX12PipeLine();
    if (pOut->Create(m_pDevice, Desc) == false)
    {
        ATLAssertMessage(false, "PipeLine�̍쐬�Ɏ��s���܂���");
        delete pOut;
        pOut = nullptr;
    }
    return pOut;
}

AstralLayer::ATLIDepthStencilView* AstralLayerDirectX12::DX12Device::CreateDepthStencilView(
    ATL_DEPTH_STENCIL_VIEW_DESC& Desc)
{
    //�f�v�X�X�e���V���r���[�쐬
    DX12DepthStencilView* pOut = new DX12DepthStencilView();
    if (pOut->Create(m_pDevice, Desc) == false)
    {
        ATLAssertMessage(false, "DepthStencilView�̍쐬�Ɏ��s���܂���");
        delete pOut;
        pOut = nullptr;
    }

    return pOut;
}

AstralLayer::ATLICommandList* AstralLayerDirectX12::DX12Device::CreateCommandList()
{
    //�R�}���h���X�g�쐬
    DX12CommandList* pOut = new DX12CommandList();
    if (pOut->Create(m_pDevice) == false)
    {
        ATLAssertMessage(false, "CommandList�̍쐬�Ɏ��s���܂���");
        delete pOut;
        pOut = nullptr;
    }

    return pOut;
}

AstralLayer::ATLICommandQueue* AstralLayerDirectX12::DX12Device::CreateCommandQueue()
{   
    //�R�}���h�L���[�쐬
    DX12CommandQueue* pOut = new DX12CommandQueue();
    if (pOut->Create(m_pDevice) == false)
    {
        ATLAssertMessage(false, "CommandQueue�̍쐬�Ɏ��s���܂���");
        delete pOut;
        pOut = nullptr;
    }
    return pOut;
}

AstralLayer::ATLISwapChain* AstralLayerDirectX12::DX12Device::CreateSwapChain(
    ATL_SWAPCHAIN_DESC& Desc, 
    AstralLayer::ATLICommandQueue* pCommandQueue)
{
    //�X���b�v�`�F�C���쐬
    DX12SwapChain* pOut = new DX12SwapChain();
    if (pOut->Create(m_pDevice, Desc, pCommandQueue) == false)
    {
        ATLAssertMessage(false, "SwapChain�̍쐬�Ɏ��s���܂���");
        delete pOut;
        pOut = nullptr;
    }

    return pOut;
}

AstralLayer::ATLIFence* AstralLayerDirectX12::DX12Device::CreateFence()
{
    //�t�F���X�쐬
    DX12Fence* pOut = new DX12Fence();
    if (pOut->Create(m_pDevice) == false)
    {
        ATLAssertMessage(false, "�t�F���X�̍쐬�Ɏ��s���܂���");
        delete pOut;
        pOut = nullptr;
    }
    return pOut;
}

AstralLayer::ATLIRenderTargetView* AstralLayerDirectX12::DX12Device::CreateRenderTargetView(
    AstralLayer::ATLISwapChain* SwapChain,
    unsigned int ScreenWidth,
    unsigned int ScreenHeight)
{
    //�X���b�v�`�F�C���擾�@NULL�Ȃ�擾���Ȃ�
    IDXGISwapChain3* swap = nullptr;
    if (SwapChain != nullptr)
        reinterpret_cast<AstralRHI::RHISwapChain*>(SwapChain)->GetHandle(reinterpret_cast<void**>(&swap), 0);

    //�����_�[�^�[�Q�b�g�r���[�쐬
    DX12RenderTargetView* pOut = new DX12RenderTargetView();
    if (pOut->Create(m_pDevice, swap, ScreenWidth, ScreenHeight) == false)
    {
        ATLAssertMessage(false, "�����_�[�^�[�Q�b�g�r���[�̍쐬�Ɏ��s���܂���");
        delete pOut;
        pOut = nullptr;
    }

    return pOut;
}

void AstralLayerDirectX12::DX12Device::Release()
{
    delete this;
}

bool AstralLayerDirectX12::DX12Device::Create(IDXGIFactory1* pFactory)
{
    pFactory;//�g��Ȃ�

    //�f�o�C�X�쐬
    HRESULT hr = D3D12CreateDevice(
        nullptr,
        D3D_FEATURE_LEVEL_11_0,
        IID_PPV_ARGS(&m_pDevice)
    );
    ATLAssertMessage(SUCCEEDED(hr), "Device�̍쐬�Ɏ��s���܂���");
    if (FAILED(hr))
        return false;

    m_gi = ATL_GRAPHIC_INTERFACE::DirectX12;

    return true;
}
