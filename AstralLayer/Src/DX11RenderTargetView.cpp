#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11RenderTargetView::~DX11RenderTargetView()
{
	delete m_pResource;
}

void AstralLayerDirectX11::DX11RenderTargetView::GetHandle(
	void** ppOut, 
	int Handle)
{
	Handle;
	switch (Handle)
	{
	case RTV_RTV:
		*ppOut = m_pRenderTarget.Get();
		break;
	case RTV_RESOURCE:
		*ppOut = m_pResource->m_pResource.Get();
		break;
	default:
		break;
	}
}

AstralLayer::ATLIResource* AstralLayerDirectX11::DX11RenderTargetView::GetResource(
	AstralLayer::ATLIFence* fence)
{
	fence;

	return m_pResource;
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
	//リソース作成
	m_pResource = new DX11SRVResource();

	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex = nullptr;

	if (pSwapChain != nullptr)
	{
		//スワップチェインからバッファを取得
		HRESULT hr = pSwapChain->GetBuffer(0, IID_PPV_ARGS(&tex));
		if (FAILED(hr))
			return false;

		//ＲＴＶ作成
		hr = pDevice->CreateRenderTargetView(tex.Get(), nullptr, &m_pRenderTarget);
		if (FAILED(hr))
			return false;
	}
	else
	{
		//テクスチャ
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
		hr = pDevice->CreateRenderTargetView(tex.Get(), &rtvd, &m_pRenderTarget);
		if (FAILED(hr))
			return false;

		//ＳＲＶ作成
		D3D11_SHADER_RESOURCE_VIEW_DESC rtv{};
		rtv.Format = DXGI_FORMAT_R32_FLOAT;
		rtv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		rtv.Texture2D.MipLevels = 1;
		hr = pDevice->CreateShaderResourceView(tex.Get(), &rtv, &m_pResource->m_pResource);
		if (FAILED(hr))
			return false;
	}


	return true;
}
