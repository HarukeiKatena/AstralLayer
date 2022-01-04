#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

D3D11_USAGE AstralLayerDirectX11::ConvDX11Usage(ATL_RESOURCE_TYPE type)
{
	switch (type)
	{
	case ATL_RESOURCE_TYPE::DEFAULT: return D3D11_USAGE_DEFAULT;
	case ATL_RESOURCE_TYPE::UPLOAD: return D3D11_USAGE_DYNAMIC;
	case ATL_RESOURCE_TYPE::READBACK: return D3D11_USAGE_STAGING;
	default: return D3D11_USAGE_DEFAULT;
	}
}

DXGI_SAMPLE_DESC AstralLayerDirectX11::GetMSAA(
	ID3D11Device* pDevice, 
	unsigned int Count)
{
	DXGI_SAMPLE_DESC msaa{};
	for (unsigned int i = 0; i < Count; i++)
	{
		unsigned int Quality = 0;
		HRESULT hr = pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, i, &Quality);
		if (SUCCEEDED(hr))
		{
			if (0 < Quality) {
				msaa.Count = i;
				msaa.Quality = Quality - 1;
			}
		}
	}

	return msaa;
}
