#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11Device::~DX11Device()
{
	//�f�o�C�X���
	if (m_pDevice != nullptr)
		m_pDevice->Release();
}

bool AstralLayerDirectX11::DX11Device::Create()
{
	//DX�f�o�C�X�쐬
	ID3D11Device* pDevice = nullptr;
	HRESULT hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&pDevice,
		nullptr,
		nullptr
	);
	ATLAssertMessage(SUCCEEDED(hr), "Device�̍쐬�Ɏ��s���܂���");
	if (FAILED(hr))
		return false;

	//�f�o�C�X��Device5�ɃL���X�g
	m_pDevice = reinterpret_cast<ID3D11Device5*>(pDevice);

	//�t���O�Z�b�g
	m_gi = ATL_GRAPHIC_INTERFACE::DirectX11;

	return true;
}

AstralLayer::ATLIResource* AstralLayerDirectX11::DX11Device::CreateResource(
	ATL_RESOURCE_DESC& Desc, 
	const void* pSrcData)
{
	//�G���[�`�F�b�N
	ATLAssert(Desc.Flag != ATL_RESOURCE_FLAG::UNKNOWN);

	//�쐬����
    if (Desc.Flag == ATL_RESOURCE_FLAG::CONSTANTBUFFER || 
		Desc.Flag == ATL_RESOURCE_FLAG::VERTEXBUFFER || 
		Desc.Flag == ATL_RESOURCE_FLAG::INDEXBUFFER)
    {
		//���\�[�X�쐬
		DX11Resource* pOut = new DX11Resource();
		if (pOut->CreateResource(m_pDevice, Desc, pSrcData) == false)
		{
			ATLAssertMessage(false, "Resource�̍쐬�Ɏ��s���܂���");
			delete pOut;
			pOut = nullptr;
		}
		return pOut;
    }
    else if (Desc.Flag == ATL_RESOURCE_FLAG::TEXTURE2D)
    {
		//�e�N�X�`��2D�쐬
		DX11Texture2D* pOut = new DX11Texture2D();
		if (pOut->CreateTexture2D(m_pDevice, Desc, pSrcData) == false)
		{
			ATLAssertMessage(false, "Resource�̍쐬�Ɏ��s���܂���");
			delete pOut;
			pOut = nullptr;
		}
		return pOut;
    }
	return nullptr;
}

AstralLayer::ATLIPipeLine* AstralLayerDirectX11::DX11Device::CreatePipeLine(
	ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc)
{
	//�p�C�v���C���쐬
	DX11PipeLine* pOut = new DX11PipeLine();
	if (pOut->Create(m_pDevice, Desc) == false)
	{
		ATLAssertMessage(false, "PipeLine�̍쐬�Ɏ��s���܂���");
		delete pOut;
		pOut = nullptr;
	}

	return pOut;
}

AstralLayer::ATLIDepthStencilView* AstralLayerDirectX11::DX11Device::CreateDepthStencilView(
	ATL_DEPTH_STENCIL_VIEW_DESC& Desc)
{
	//�f�v�X�X�e���V���r���[�쐬
	DX11DepthStencilView* pOut = new DX11DepthStencilView();
	if (pOut->Create(m_pDevice, Desc) == false)
	{
		ATLAssertMessage(false, "�f�v�X�X�e���V���r���[�̍쐬�Ɏ��s���܂���");
		delete pOut;
		pOut = nullptr;
	}
	return pOut;;
}

AstralLayer::ATLICommandList* AstralLayerDirectX11::DX11Device::CreateCommandList()
{
	//�R�}���h���X�g�쐬
	DX11CommandList* pOut = new DX11CommandList();
	if (pOut->Create(m_pDevice) == false) 
	{
		ATLAssertMessage(false, "CommandList�̍쐬�Ɏ��s���܂���");
		delete pOut;
		pOut = nullptr;
	}

	return pOut;
}

AstralLayer::ATLICommandQueue* AstralLayerDirectX11::DX11Device::CreateCommandQueue()
{
	//�R�}���h�L���[�쐬
	DX11CommandQueue* pOut = new DX11CommandQueue();
	if (pOut->Create(m_pDevice) == false)
	{
		ATLAssertMessage(false, "CommandQueue�̍쐬�Ɏ��s���܂���");
		delete pOut;
		pOut = nullptr;
	}
	return pOut;
}

AstralLayer::ATLISwapChain* AstralLayerDirectX11::DX11Device::CreateSwapChain(
	ATL_SWAPCHAIN_DESC& Desc, 
	AstralLayer::ATLICommandQueue* pCommandQueue)
{
	//�X���b�v�`�F�C���쐬
	DX11SwapChain* pOut = new DX11SwapChain();
	if (pOut->Create(m_pDevice, Desc, pCommandQueue) == false)
	{
		ATLAssertMessage(false, "SwapChain�̍쐬�Ɏ��s���܂���");
		delete pOut;
		pOut = nullptr;
	}
	return pOut;
}

AstralLayer::ATLIFence* AstralLayerDirectX11::DX11Device::CreateFence()
{
	//�t�F���X�̍쐬
	DX11Fence* pOut = new DX11Fence();
	if (pOut->Create(m_pDevice) == false)
	{
		ATLAssertMessage(false, "�t�F���X�̍쐬�Ɏ��s���܂���");
		delete pOut;
		pOut = nullptr;
	}
	return pOut;
}

AstralLayer::ATLIRenderTargetView* AstralLayerDirectX11::DX11Device::CreateRenderTargetView(
	AstralLayer::ATLISwapChain* SwapChain, 
	unsigned int ScreenWidth, 
	unsigned int ScreenHeight)
{
	//�X���b�v�`�F�C�����󂯎��@NULL�̏ꍇ�͎󂯎��Ȃ�
	IDXGISwapChain* swap = nullptr;
	if (SwapChain != nullptr)
		reinterpret_cast<AstralRHI::RHISwapChain*>(SwapChain)->
		GetHandle(reinterpret_cast<void**>(&swap), SWAPCHAIN_SWAPCHAIN);

	//�����_�[�^�[�Q�b�g�r���[�쐬
	DX11RenderTargetView* pOut = new DX11RenderTargetView();
	if (pOut->Create(m_pDevice, swap, ScreenWidth, ScreenHeight) == false)
	{
		ATLAssertMessage(false, "�����_�[�^�[�Q�b�g�r���[�̍쐬�Ɏ��s���܂���");
		delete pOut;
		pOut = nullptr;
	}
	return pOut;
}

void AstralLayerDirectX11::DX11Device::Release()
{
	delete this;
}

void AstralLayerDirectX11::DX11Device::GetHandle(
	void** Resource, 
	int Handle)
{
	Handle;
	*Resource = m_pDevice;
}
