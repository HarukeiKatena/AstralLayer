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

bool AstralLayerDirectX11::DX11DepthStencilView::Create(
	ID3D11Device* pDevice, 
	ATL_DEPTH_STENCIL_VIEW_DESC& Desc)
{
	//���p�ł���MSAA���`�F�b�N
	DXGI_SAMPLE_DESC sample = GetMSAA(pDevice, Desc.SampleDesc.Count);
	sample.Quality = sample.Quality < Desc.SampleDesc.Quality ? sample.Quality : Desc.SampleDesc.Quality;

	//�e�N�X�`���f�X�N����
	D3D11_TEXTURE2D_DESC TextureDesc;
	TextureDesc.Width = Desc.Width;
	TextureDesc.Height = Desc.Height;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_D16_UNORM;
	TextureDesc.SampleDesc = sample;
	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	//�e�N�X�`���쐬
	ID3D11Texture2D* texture = nullptr;
	if (FAILED(pDevice->CreateTexture2D(&TextureDesc, nullptr, &texture)))
		return false;

	//�f�v�X�X�e���V���r���[�f�X�N����
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvdesc;
	dsvdesc.Format = TextureDesc.Format;
	dsvdesc.ViewDimension = ConvDimension(Desc.Dimension);
	dsvdesc.Flags = 0;
	dsvdesc.Texture2D.MipSlice = 0;

	//�f�v�X�X�e���V���r���[�쐬
	HRESULT hr = pDevice->CreateDepthStencilView(texture, &dsvdesc, &m_pView);
	texture->Release();//�e�N�X�`���͉�����Ă���
	if (FAILED(hr))
		return false;

	return true;
}