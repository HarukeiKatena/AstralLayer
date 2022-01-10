#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

//==========================================================================
// スワップチェイン
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
	//エラーチェック
	ATLAssert(pDevice != nullptr);
	ATLAssert(Desc.hWnd != NULL);
	ATLAssert(pCommandQueue != nullptr);
	if (pDevice == nullptr ||
		Desc.hWnd == NULL ||
		pCommandQueue == nullptr)
		return false;


	//コマンドキューを受け取る
	ID3D12CommandQueue* pCQ = nullptr;
	reinterpret_cast<AstralRHI::RHICommandQueue*>(pCommandQueue)->
		GetHandle(reinterpret_cast<void**>(&pCQ), 0);
	if (pCQ == nullptr)//NULLチェック
		return false;

	//デスク作成
	DXGI_SWAP_CHAIN_DESC1 desc{};
	desc.BufferCount = 2;
	desc.Width = Desc.Width;
	desc.Height = Desc.Height;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Stereo = false;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Scaling = DXGI_SCALING_STRETCH;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	desc.Flags = 0;
	
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC full{};
	full.RefreshRate.Denominator = 60;
	full.RefreshRate.Numerator = 0;
	full.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	full.Windowed = Desc.Windowed;

	//ファクトリー
	IDXGIFactory4* pFactory = nullptr;
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory));
	if (FAILED(hr))
		return false;

	//スワップチェイン
	IDXGISwapChain1* pCreate = nullptr;

	hr = pFactory->CreateSwapChainForHwnd(
		pCQ,
		Desc.hWnd,
		&desc,
		&full,
		nullptr,
		&pCreate
	);
	pFactory->Release();
	if (FAILED(hr))
		return false;

	//スワップチェインセット
	m_pSwapChain = reinterpret_cast<IDXGISwapChain3*>(pCreate);

	return true;
}

void AstralLayerDirectX12::DX12SwapChain::Present(unsigned int SyncInterval)
{
	//描画
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
