#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11SwapChain::~DX11SwapChain()
{
	if (m_pSwapChain != nullptr)
		m_pSwapChain->Release();
}

bool AstralLayerDirectX11::DX11SwapChain::Create(
	ID3D11Device* pDevice, ATL_SWAPCHAIN_DESC& Desc, AstralLayer::ATLICommandQueue* pCommandQueue)
{
	pCommandQueue;

	//エラーチェック
	ATLAssert(pDevice != nullptr);
	ATLAssert(Desc.hWnd != NULL);
	if (pDevice == nullptr ||
		Desc.hWnd == NULL)
		return false;

	//利用できるMSAAをチェック
	DXGI_SAMPLE_DESC sample = GetMSAA(pDevice, Desc.Sample.Count);
	sample.Quality = sample.Quality < Desc.Sample.Quality ? sample.Quality : Desc.Sample.Quality;

	//デスク作成
	DXGI_SWAP_CHAIN_DESC desc{};
	desc.BufferCount = 1;
	desc.BufferDesc.Width = Desc.Width;
	desc.BufferDesc.Height = Desc.Height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = Desc.hWnd;
	desc.SampleDesc = sample;
	desc.Windowed = Desc.Windowed;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = 0;

	//ファクトリー
	IDXGIFactory4* pFactory = nullptr;
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory));
	ATLAssertMessage(SUCCEEDED(hr), "SwapChainの作成に失敗しました");
	if (FAILED(hr))
		return false;
	
	//スワップチェイン
	IDXGISwapChain* pCreate = nullptr;
	hr = pFactory->CreateSwapChain(
		pDevice,
		&desc,
		&pCreate
	);
	pFactory->Release();
	ATLAssertMessage(SUCCEEDED(hr), "SwapChainの作成に失敗しました");
	if (FAILED(hr))
		return false;

	//スワップチェインをセット
	m_pSwapChain = reinterpret_cast<IDXGISwapChain3*>(pCreate);

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
	*ppResource = m_pSwapChain;
}
