#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

//==========================================================================
// �X���b�v�`�F�C��
//==========================================================================
AstralLayerDirectX12::DX12SwapChain::~DX12SwapChain()
{
	if (m_pSwapChain != nullptr)
		m_pSwapChain->Release();
}

bool AstralLayerDirectX12::DX12SwapChain::Create(
	ID3D12Device* pDevice, 
	ATL_SWAPCHAIN_DESC& Desc, 
	AstralLayer::ATLICommandQueue* pCommandQueue)
{
	//�G���[�`�F�b�N
	ATLAssert(pDevice != nullptr);
	ATLAssert(Desc.hWnd != NULL);
	ATLAssert(pCommandQueue != nullptr);
	if (pDevice == nullptr ||
		Desc.hWnd == NULL ||
		pCommandQueue == nullptr)
		return false;


	//�R�}���h�L���[���󂯎��
	ID3D12CommandQueue* pCQ = nullptr;
	reinterpret_cast<AstralRHI::RHICommandQueue*>(pCommandQueue)->
		GetHandle(reinterpret_cast<void**>(&pCQ), 0);
	if (pCQ == nullptr)//NULL�`�F�b�N
		return false;

	//�f�X�N�쐬
	DXGI_SWAP_CHAIN_DESC desc{};
	desc.BufferCount = 2;
	desc.BufferDesc.Width = Desc.Width;
	desc.BufferDesc.Height = Desc.Height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = Desc.hWnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = Desc.Windowed;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	

	//�t�@�N�g���[
	IDXGIFactory4* pFactory = nullptr;
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory));
	if (FAILED(hr))
		return false;

	//�X���b�v�`�F�C��
	IDXGISwapChain* pCreate = nullptr;
	hr = pFactory->CreateSwapChain(
		pCQ,
		&desc,
		&pCreate
	);
	pFactory->Release();
	if (FAILED(hr))
		return false;

	//�X���b�v�`�F�C���Z�b�g
	m_pSwapChain = reinterpret_cast<IDXGISwapChain3*>(pCreate);

	return true;
}

void AstralLayerDirectX12::DX12SwapChain::Present(unsigned int SyncInterval)
{
	//�`��
	m_pSwapChain->Present(SyncInterval, 0);
}

void AstralLayerDirectX12::DX12SwapChain::Release()
{
	delete this;
}

void AstralLayerDirectX12::DX12SwapChain::GetHandle(
	void** ppOut, 
	int Handle)
{
	Handle;
	*ppOut = m_pSwapChain;
}
