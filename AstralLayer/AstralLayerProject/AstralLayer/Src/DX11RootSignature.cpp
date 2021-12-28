#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

D3D11_FILTER AstralLayerDirectX11::DX11RootSignature::ConvFilter(ATL_FILTER Filter)
{
	switch (Filter)
	{
	case ATL_FILTER::MIN_MAG_MIP_POINT:								return D3D11_FILTER_MIN_MAG_MIP_POINT;
	case ATL_FILTER::MIN_MAG_POINT_MIP_LINEAR:						return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	case ATL_FILTER::MIN_POINT_MAG_LINEAR_MIP_POINT:				return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
	case ATL_FILTER::MIN_POINT_MAG_MIP_LINEAR:						return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
	case ATL_FILTER::MIN_LINEAR_MAG_MIP_POINT:						return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
	case ATL_FILTER::MIN_LINEAR_MAG_POINT_MIP_LINEAR:				return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	case ATL_FILTER::MIN_MAG_LINEAR_MIP_POINT:						return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	case ATL_FILTER::MIN_MAG_MIP_LINEAR:							return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	case ATL_FILTER::ANISOTROPIC:									return D3D11_FILTER_ANISOTROPIC;
	case ATL_FILTER::COMPARISON_MIN_MAG_MIP_POINT:					return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
	case ATL_FILTER::COMPARISON_MIN_MAG_POINT_MIP_LINEAR:			return D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
	case ATL_FILTER::COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:		return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
	case ATL_FILTER::COMPARISON_MIN_POINT_MAG_MIP_LINEAR:			return D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
	case ATL_FILTER::COMPARISON_MIN_LINEAR_MAG_MIP_POINT:			return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
	case ATL_FILTER::COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:	return D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	case ATL_FILTER::COMPARISON_MIN_MAG_LINEAR_MIP_POINT:			return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	case ATL_FILTER::COMPARISON_MIN_MAG_MIP_LINEAR:					return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	case ATL_FILTER::COMPARISON_ANISOTROPIC:						return D3D11_FILTER_COMPARISON_ANISOTROPIC;
	default: return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	}
}

D3D11_TEXTURE_ADDRESS_MODE AstralLayerDirectX11::DX11RootSignature::ConvAddressMode(
	ATL_ADDRESS_MODE mode)
{
	switch (mode)
	{
	case ATL_ADDRESS_MODE::WRAP:		return D3D11_TEXTURE_ADDRESS_WRAP;
	case ATL_ADDRESS_MODE::MIRROR:		return D3D11_TEXTURE_ADDRESS_MIRROR;
	case ATL_ADDRESS_MODE::CLAMP:		return D3D11_TEXTURE_ADDRESS_CLAMP;
	case ATL_ADDRESS_MODE::BORDER:		return D3D11_TEXTURE_ADDRESS_BORDER;
	default: return D3D11_TEXTURE_ADDRESS_WRAP;
	}
}

D3D11_COMPARISON_FUNC AstralLayerDirectX11::DX11RootSignature::ConvComparisonFunc(
	ATL_COMPARISON_FUNC func)
{
	switch (func)
	{
	case ATL_COMPARISON_FUNC::NEVER:		return D3D11_COMPARISON_NEVER;
	case ATL_COMPARISON_FUNC::LESS:			return D3D11_COMPARISON_LESS;
	case ATL_COMPARISON_FUNC::EQUAL:		return D3D11_COMPARISON_EQUAL;
	case ATL_COMPARISON_FUNC::LESS_EQUAL:	return D3D11_COMPARISON_LESS_EQUAL;
	case ATL_COMPARISON_FUNC::GREATER:		return D3D11_COMPARISON_GREATER;
	case ATL_COMPARISON_FUNC::NOT_EQUAL:	return D3D11_COMPARISON_EQUAL;
	case ATL_COMPARISON_FUNC::GREATER_EQUAL:return D3D11_COMPARISON_GREATER_EQUAL;
	case ATL_COMPARISON_FUNC::ALWAYS:		return D3D11_COMPARISON_ALWAYS;
	default: return D3D11_COMPARISON_NEVER;
	}
}

void AstralLayerDirectX11::DX11RootSignature::ConvBorderColor(
	ATL_BORDER_COLOR border, 
	float* out_color)
{
	switch (border)
	{
	case ATL_BORDER_COLOR::TRANSPARENT_BLACK:
		out_color[0] = 0.0f;
		out_color[1] = 0.0f;
		out_color[2] = 0.0f;
		out_color[3] = 0.0f;
		break;
	case ATL_BORDER_COLOR::OPAQUE_BLACK:
		out_color[0] = 0.0f;
		out_color[1] = 0.0f;
		out_color[2] = 0.0f;
		out_color[3] = 1.0f;
		break;
	case ATL_BORDER_COLOR::OPAQUE_WHITE:
		out_color[0] = 1.0f;
		out_color[1] = 1.0f;
		out_color[2] = 1.0f;
		out_color[3] = 1.0f;
		break;
	default:
		out_color[0] = 0.0f;
		out_color[1] = 0.0f;
		out_color[2] = 0.0f;
		out_color[3] = 0.0f;
		break;
	}
}

AstralLayerDirectX11::DX11RootSignature::~DX11RootSignature()
{
	//パラメーター解放
	delete[] m_Parametor.pParameters;
	
	//サンプラーがNULLの場合終わる
	if (m_Sampler.pSampler == nullptr)
		return;

	//サンプラーステートを解放
	for (unsigned int i = 0; i < m_Sampler.NumSampler; i++)
	{
		if (m_Sampler.pSampler[i].pSamplerState != nullptr)
			m_Sampler.pSampler[i].pSamplerState->Release();
	}

	//サンプラー解放
	delete[] m_Sampler.pSampler;
}

void AstralLayerDirectX11::DX11RootSignature::GetHandle(
	void** ppResource, 
	int Handle)
{
	switch (Handle)
	{
	case ROOTSIGNATURE_PARAMETOR:
		*ppResource = &m_Parametor;
		break;
	case ROOTSIGNATURE_SAMPLER:
		*ppResource = &m_Sampler;
		break;
	default:
		break;
	}
}

void AstralLayerDirectX11::DX11RootSignature::Release()
{
	delete this;
}

bool AstralLayerDirectX11::DX11RootSignature::Create(
	ID3D11Device* pDevice, 
	ATL_ROOT_SIGNATURE_DESC& Desc)
{
	//テーブル
	m_Parametor.NumRootParametors = Desc.NumRootParameters;
	m_Parametor.pParameters = new ATL_ROOT_PARAMETER[Desc.NumRootParameters];
	for (unsigned int i = 0; i < Desc.NumRootParameters; i++)
	{
		m_Parametor.pParameters[i] = Desc.pRootParameters[i];
	}

	//サンプラー
	m_Sampler.NumSampler = Desc.NumSamplers;
	m_Sampler.pSampler = new DX11Sampler[Desc.NumSamplers];
	for (unsigned int i = 0; i < Desc.NumSamplers; i++)
	{
		D3D11_SAMPLER_DESC desc{};
		desc.Filter = ConvFilter(Desc.pSamplers[i].Filter);
		desc.AddressU = ConvAddressMode(Desc.pSamplers[i].AddressU);
		desc.AddressV = ConvAddressMode(Desc.pSamplers[i].AddressV);
		desc.AddressW = ConvAddressMode(Desc.pSamplers[i].AddressW);
		desc.MipLODBias = Desc.pSamplers[i].MipLODBias;
		desc.MaxAnisotropy = Desc.pSamplers[i].MaxAnisotropy;
		desc.ComparisonFunc = ConvComparisonFunc(Desc.pSamplers[i].ComparisionFunc);
		ConvBorderColor(Desc.pSamplers[i].BorderColor, desc.BorderColor);
		desc.MinLOD = Desc.pSamplers[i].MinLOD;
		desc.MaxLOD = Desc.pSamplers[i].MaxLOD;

		if (FAILED(pDevice->CreateSamplerState(&desc, &m_Sampler.pSampler[i].pSamplerState)))
		{
			this->~DX11RootSignature();
			return false;
		}

		//数値系を入れる
		m_Sampler.pSampler[i].SamplerRegister = Desc.pSamplers[i].ShaderRegister;
		m_Sampler.pSampler[i].SamplerVisibility = Desc.pSamplers[i].Visibility;
	}

	return true;
}
