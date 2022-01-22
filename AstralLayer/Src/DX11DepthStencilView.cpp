#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

D3D11_DSV_DIMENSION AstralLayerDirectX11::DX11DepthStencilView::ConvDimension(ATL_DSV_DIMENSION Dimension)
{
	switch (Dimension)
	{
	case ATL_DSV_DIMENSION::TEXTURE1D: return D3D11_DSV_DIMENSION_TEXTURE1D;
	case ATL_DSV_DIMENSION::TEXTURE2D: return D3D11_DSV_DIMENSION_TEXTURE2D;
	case ATL_DSV_DIMENSION::TEXTURE2DMS: return D3D11_DSV_DIMENSION_TEXTURE2DMS;
	default: return D3D11_DSV_DIMENSION_UNKNOWN;
	}
}

AstralLayerDirectX11::DX11DepthStencilView::~DX11DepthStencilView()
{
	delete m_pResource;
}

void AstralLayerDirectX11::DX11DepthStencilView::GetHandle(
	void** ppOut, 
	int Handle)
{
	Handle;
	*ppOut = m_pView.Get();
}

void AstralLayerDirectX11::DX11DepthStencilView::Release()
{
	delete this;
}

AstralLayer::ATLIResource* AstralLayerDirectX11::DX11DepthStencilView::GetResource(
	AstralLayer::ATLIFence* pFence)
{
	return nullptr;
}

bool AstralLayerDirectX11::DX11DepthStencilView::Create(
	ID3D11Device* pDevice, 
	ATL_DEPTH_STENCIL_VIEW_DESC& Desc)
{
	//利用できるMSAAをチェック
	DXGI_SAMPLE_DESC sample = GetMSAA(pDevice, Desc.SampleDesc.Count);
	sample.Quality = sample.Quality < Desc.SampleDesc.Quality ? sample.Quality : Desc.SampleDesc.Quality;

	//テクスチャデスク準備
	D3D11_TEXTURE2D_DESC TextureDesc;
	TextureDesc.Width = Desc.Width;
	TextureDesc.Height = Desc.Height;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	TextureDesc.SampleDesc = sample;
	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	//テクスチャ作成
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture = nullptr;
	if (FAILED(pDevice->CreateTexture2D(&TextureDesc, nullptr, &texture)))
		return false;

	//デプスステンシルビューデスク準備
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvdesc;
	dsvdesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvdesc.ViewDimension = ConvDimension(Desc.Dimension);
	dsvdesc.Flags = 0;
	dsvdesc.Texture2D.MipSlice = 0;

	//デプスステンシルビュー作成
	HRESULT hr = pDevice->CreateDepthStencilView(texture.Get(), &dsvdesc, &m_pView);
	if (FAILED(hr))
		return false;

	D3D11_SHADER_RESOURCE_VIEW_DESC  SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R32_FLOAT;//ピクセルフォーマットは32BitFLOAT型
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	m_pResource = new DX11SRVResource();
	hr = pDevice->CreateShaderResourceView(texture.Get(), &SRVDesc, &m_pResource->m_pResource);
	if (FAILED(hr))
		return false;

	return true;
}