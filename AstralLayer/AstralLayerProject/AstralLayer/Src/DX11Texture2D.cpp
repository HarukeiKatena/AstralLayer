#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"
#include"../Include/ATL/AstralDirectX.h"

AstralLayerDirectX11::DX11Texture2D::~DX11Texture2D()
{
	if (m_pTexture != nullptr)
		m_pTexture->Release();

	if (m_pSRV != nullptr)
		m_pSRV->Release();

	if (m_pImmidiateContext != nullptr)
		m_pImmidiateContext->Release();
}

unsigned int AstralLayerDirectX11::DX11Texture2D::SetSubResource(
	const void* pData, unsigned int SetByteSize)
{
	//�}�b�v
	D3D11_MAPPED_SUBRESOURCE map{};
	if(FAILED(m_pImmidiateContext->Map(m_pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &map)))
		return UINT_MAX;

	//�㏑��
	memcpy(map.pData, pData, SetByteSize);

	//�A���}�b�v
	m_pImmidiateContext->Unmap(m_pTexture, 0);

	return 0;
}

bool AstralLayerDirectX11::DX11Texture2D::UpdateSubResource(
	unsigned int SubResourceID, 
	unsigned int MoveByte, 
	const void* pData, 
	unsigned int UpdateByteSize)
{
	SubResourceID;
	MoveByte;
	UpdateByteSize;

	//�}�b�v
	D3D11_MAPPED_SUBRESOURCE map{};
	if (FAILED(m_pImmidiateContext->Map(m_pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &map)))
		return false;

	//�㏑��
	memcpy(map.pData, pData, m_ByteSize);

	//�A���}�b�v
	m_pImmidiateContext->Unmap(m_pTexture, 0);

	return true;
}

void AstralLayerDirectX11::DX11Texture2D::GetHandle(
	void** ppOut, 
	int Handle)
{
	Handle;
	*ppOut = m_pSRV;
}

void AstralLayerDirectX11::DX11Texture2D::Release()
{
	delete this;
}

bool AstralLayerDirectX11::DX11Texture2D::CreateTexture2D(
	ID3D11Device* pDevice, 
	ATL_RESOURCE_DESC& Desc, 
	const void* pSrcData)
{
	if (Desc.Type == ATL_RESOURCE_TYPE::UNKNOWN)
		return false;

	//�ϐ������A���h�Z�b�g
	m_ByteSize = Desc.ByteStructure * Desc.Width * Desc.Height;
	m_Type = Desc.Type;
	m_Flag = Desc.Flag;
	pDevice->GetImmediateContext(&m_pImmidiateContext);

	//�f�X�N����
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = Desc.Width;
	desc.Height = Desc.Height;
	desc.MipLevels = Desc.MipLevel;
	desc.ArraySize = 1;
	desc.Format = ConvDXGIFormat(Desc.Format);
	desc.SampleDesc = { Desc.SampleDesc.Count,Desc.SampleDesc.Quality };
	desc.Usage = ConvDX11Usage(Desc.Type);
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MiscFlags = 0;

	if (Desc.Type == ATL_RESOURCE_TYPE::DEFAULT)//�A�N�Z�X�t���O����
		desc.CPUAccessFlags = 0;
	else
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

	//�f�[�^�������݂��Ȃ��ꍇ
	if (pSrcData == nullptr)
	{
		//�쐬
		HRESULT hr = pDevice->CreateTexture2D(&desc, nullptr, &m_pTexture);
		if (FAILED(hr))
			return false;
	}
	else
	{
		//�f�[�^���
		D3D11_SUBRESOURCE_DATA data{};
		data.pSysMem = pSrcData;
		data.SysMemPitch = Desc.ByteStructure * Desc.Width;
		data.SysMemSlicePitch = data.SysMemPitch * Desc.Height;

		//�쐬
		HRESULT hr = pDevice->CreateTexture2D(&desc, &data, &m_pTexture);
		if (FAILED(hr))
			return false;
	}

	//�V�F�[�_�[���\�[�X�r���[�쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srvdesc{};
	srvdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvdesc.Format = desc.Format;
	srvdesc.Texture2D.MipLevels = desc.MipLevels;
	srvdesc.Texture2D.MostDetailedMip = 0;
	
	if (FAILED(pDevice->CreateShaderResourceView(m_pTexture, &srvdesc, &m_pSRV)))
	{
		this->~DX11Texture2D();
		return false;
	}
		

	return true;
}
