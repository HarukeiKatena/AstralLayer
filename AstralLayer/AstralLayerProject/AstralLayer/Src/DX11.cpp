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