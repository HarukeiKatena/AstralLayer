#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11SRVResource::~DX11SRVResource()
{

}

unsigned int AstralLayerDirectX11::DX11SRVResource::SetSubResource(
	const void* pData, 
	unsigned int SetByteSize)
{
	pData;
	SetByteSize;
	return UINT_MAX;
}

bool AstralLayerDirectX11::DX11SRVResource::UpdateSubResource(
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

void AstralLayerDirectX11::DX11SRVResource::Release()
{
	delete this;
}

void AstralLayerDirectX11::DX11SRVResource::GetHandle(void** ppOut, int Handle)
{
	Handle;
	*ppOut = m_pResource.Get();
}
