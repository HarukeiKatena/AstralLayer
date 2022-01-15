#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11RTVResource::~DX11RTVResource()
{

}

unsigned int AstralLayerDirectX11::DX11RTVResource::SetSubResource(
	const void* pData, 
	unsigned int SetByteSize)
{
	pData;
	SetByteSize;
	return UINT_MAX;
}

bool AstralLayerDirectX11::DX11RTVResource::UpdateSubResource(
	unsigned int SubResourceID, 
	unsigned int MoveByte, 
	const void* pData, 
	unsigned int UpdateByteSize)
{
	SubResourceID;
	MoveByte;
	pData;
	UpdateByteSize;
	return true;
}

void AstralLayerDirectX11::DX11RTVResource::Release()
{
	delete this;
}

void AstralLayerDirectX11::DX11RTVResource::GetHandle(void** ppOut, int Handle)
{
	Handle;
	*ppOut = m_pBuffer.Get();
}

void AstralLayerDirectX11::DX11RTVResource::SetBuffer(ID3D11Resource* pBuffer)
{
	m_pBuffer = pBuffer;
}
