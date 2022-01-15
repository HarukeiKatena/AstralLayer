#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11RenderTargetView::~DX11RenderTargetView()
{
	
}

void AstralLayerDirectX11::DX11RenderTargetView::GetHandle(
	void** ppOut, 
	int Handle)
{
	Handle;
	*ppOut = m_pRenderTarget.Get();
}

AstralLayer::ATLIResource* AstralLayerDirectX11::DX11RenderTargetView::GetResource(
	AstralLayer::ATLIFence* fence)
{
	fence;

	//DXのリソース取得
	ID3D11Resource* resource = nullptr;
	m_pRenderTarget->GetResource(&resource);

	//ATLのリソース
	DX11RTVResource* pOut = new DX11RTVResource();
	pOut->SetBuffer(resource);

	return pOut;
}

void AstralLayerDirectX11::DX11RenderTargetView::Release()
{
	delete this;
}

bool AstralLayerDirectX11::DX11RenderTargetView::Create(
	ID3D11Device* pDevice,
	IDXGISwapChain* pSwapChain,
	unsigned int ScreenWidth,
	unsigned int ScreenHeight)
{

	if (pSwapChain != nullptr)
	{
		ID3D11Texture2D* tex = nullptr;
		HRESULT hr = pSwapChain->GetBuffer(0, IID_PPV_ARGS(&tex));
		if (FAILED(hr))
			return false;

		hr = pDevice->CreateRenderTargetView(tex, nullptr, &m_pRenderTarget);
		tex->Release();
		if (FAILED(hr))
			return false;
	}
	else
	{
		//テクスチャ
		ID3D11Texture2D* tex = nullptr;
		D3D11_TEXTURE2D_DESC desc{};
		desc.Width = ScreenWidth;
		desc.Height = ScreenHeight;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc = { 1,0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		HRESULT hr = pDevice->CreateTexture2D(&desc, nullptr, &tex);
		if (FAILED(hr))
			return false;

		//RTV作成
		D3D11_RENDER_TARGET_VIEW_DESC rtvd{};
		rtvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		hr = pDevice->CreateRenderTargetView(tex, &rtvd, &m_pRenderTarget);
		if (FAILED(hr))
			return false;
	}


	return true;
}
