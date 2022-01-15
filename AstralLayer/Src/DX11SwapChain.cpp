#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11SwapChain::~DX11SwapChain()
{

}

bool AstralLayerDirectX11::DX11SwapChain::Create(
	ID3D11Device* pDevice, ATL_SWAPCHAIN_DESC& Desc, AstralLayer::ATLICommandQueue* pCommandQueue)
{
	pCommandQueue;

	//�G���[�`�F�b�N
	ATLAssert(pDevice != nullptr);
	ATLAssert(Desc.hWnd != NULL);
	if (pDevice == nullptr ||
		Desc.hWnd == NULL)
		return false;

	//���p�ł���MSAA���`�F�b�N
	DXGI_SAMPLE_DESC sample = GetMSAA(pDevice, Desc.Sample.Count);
	sample.Quality = sample.Quality < Desc.Sample.Quality ? sample.Quality : Desc.Sample.Quality;

	//�f�X�N�쐬
	DXGI_SWAP_CHAIN_DESC1 desc{};
	desc.BufferCount = 2;
	desc.Width = Desc.Width;
	desc.Height = Desc.Height;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Stereo = false;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SampleDesc = sample;
	desc.Scaling = DXGI_SCALING_STRETCH;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.Flags = 0;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC full{};
	full.RefreshRate.Denominator = 1;
	full.RefreshRate.Numerator = 60;
	full.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	full.Windowed = Desc.Windowed;

	//�t�@�N�g���[
	IDXGIFactory4* pFactory = nullptr;
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory));
	ATLAssertMessage(SUCCEEDED(hr), "SwapChain�̍쐬�Ɏ��s���܂���");
	if (FAILED(hr))
		return false;
	
	//�X���b�v�`�F�C��
	IDXGISwapChain1* pCreate = nullptr;
	hr = pFactory->CreateSwapChainForHwnd(
		pDevice,
		Desc.hWnd,
		&desc,
		&full,
		nullptr,
		&pCreate
	);
	pFactory->Release();
	ATLAssertMessage(SUCCEEDED(hr), "SwapChain�̍쐬�Ɏ��s���܂���");
	if (FAILED(hr))
		return false;

	//�X���b�v�`�F�C�����Z�b�g
	pCreate->QueryInterface(IID_PPV_ARGS(&m_pSwapChain));

	pCreate->Release();

	return true;
}

void AstralLayerDirectX11::DX11SwapChain::Present(unsigned int SyncInterval)
{
	m_pSwapChain->Present(SyncInterval, 0);
}

void AstralLayerDirectX11::DX11SwapChain::Release()
{
	delete this;
}

void AstralLayerDirectX11::DX11SwapChain::GetHandle(
	void** ppResource, 
	int Handle)
{
	Handle;
	*ppResource = m_pSwapChain.Get();
}
