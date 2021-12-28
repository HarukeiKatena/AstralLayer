#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

#include<string>

D3D12_DESCRIPTOR_RANGE_TYPE AstralLayerDirectX12::DX12RootSignature::ConvRangeType(ATL_DESCRIPTOR_TYPE type)
{
	switch (type)
	{
	case ATL_DESCRIPTOR_TYPE::CBV: return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	case ATL_DESCRIPTOR_TYPE::SRV: return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	case ATL_DESCRIPTOR_TYPE::UAV: return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	default: return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	}
}

D3D12_SHADER_VISIBILITY AstralLayerDirectX12::DX12RootSignature::ConvVisibility(ATL_SHADER_VISIBILITY visibility)
{
	switch (visibility)
	{
	case ATL_SHADER_VISIBILITY::ALL:		return D3D12_SHADER_VISIBILITY_ALL;
	case ATL_SHADER_VISIBILITY::VERTEX:		return D3D12_SHADER_VISIBILITY_VERTEX;
	case ATL_SHADER_VISIBILITY::PIXEL:		return D3D12_SHADER_VISIBILITY_PIXEL;
	default: return D3D12_SHADER_VISIBILITY_ALL;
	}
}

D3D12_FILTER AstralLayerDirectX12::DX12RootSignature::ConvFilter(ATL_FILTER Filter)
{
	switch (Filter)
	{
	case ATL_FILTER::MIN_MAG_MIP_POINT:								return D3D12_FILTER_MIN_MAG_MIP_POINT;
	case ATL_FILTER::MIN_MAG_POINT_MIP_LINEAR:						return D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	case ATL_FILTER::MIN_POINT_MAG_LINEAR_MIP_POINT:				return D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
	case ATL_FILTER::MIN_POINT_MAG_MIP_LINEAR:						return D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR;
	case ATL_FILTER::MIN_LINEAR_MAG_MIP_POINT:						return D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT;
	case ATL_FILTER::MIN_LINEAR_MAG_POINT_MIP_LINEAR:				return D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	case ATL_FILTER::MIN_MAG_LINEAR_MIP_POINT:						return D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	case ATL_FILTER::MIN_MAG_MIP_LINEAR:							return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	case ATL_FILTER::ANISOTROPIC:									return D3D12_FILTER_ANISOTROPIC;
	case ATL_FILTER::COMPARISON_MIN_MAG_MIP_POINT:					return D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
	case ATL_FILTER::COMPARISON_MIN_MAG_POINT_MIP_LINEAR:			return D3D12_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
	case ATL_FILTER::COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT:		return D3D12_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
	case ATL_FILTER::COMPARISON_MIN_POINT_MAG_MIP_LINEAR:			return D3D12_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
	case ATL_FILTER::COMPARISON_MIN_LINEAR_MAG_MIP_POINT:			return D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
	case ATL_FILTER::COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR:	return D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	case ATL_FILTER::COMPARISON_MIN_MAG_LINEAR_MIP_POINT:			return D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	case ATL_FILTER::COMPARISON_MIN_MAG_MIP_LINEAR:					return D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	case ATL_FILTER::COMPARISON_ANISOTROPIC:						return D3D12_FILTER_COMPARISON_ANISOTROPIC;
	default: return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	}
}

D3D12_TEXTURE_ADDRESS_MODE AstralLayerDirectX12::DX12RootSignature::ConvAddressMode(ATL_ADDRESS_MODE mode)
{
	switch (mode)
	{
	case ATL_ADDRESS_MODE::WRAP:		return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	case ATL_ADDRESS_MODE::MIRROR:		return D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
	case ATL_ADDRESS_MODE::CLAMP:		return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	case ATL_ADDRESS_MODE::BORDER:		return D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	default: return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	}
}

D3D12_COMPARISON_FUNC AstralLayerDirectX12::DX12RootSignature::ConvComparisonFunc(ATL_COMPARISON_FUNC func)
{
	switch (func)
	{
	case ATL_COMPARISON_FUNC::NEVER:		return D3D12_COMPARISON_FUNC_NEVER;
	case ATL_COMPARISON_FUNC::LESS:			return D3D12_COMPARISON_FUNC_LESS;
	case ATL_COMPARISON_FUNC::EQUAL:		return D3D12_COMPARISON_FUNC_EQUAL;
	case ATL_COMPARISON_FUNC::LESS_EQUAL:	return D3D12_COMPARISON_FUNC_LESS_EQUAL;
	case ATL_COMPARISON_FUNC::GREATER:		return D3D12_COMPARISON_FUNC_GREATER;
	case ATL_COMPARISON_FUNC::NOT_EQUAL:	return D3D12_COMPARISON_FUNC_EQUAL;
	case ATL_COMPARISON_FUNC::GREATER_EQUAL: return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
	case ATL_COMPARISON_FUNC::ALWAYS:		return D3D12_COMPARISON_FUNC_ALWAYS;
	default: return D3D12_COMPARISON_FUNC_NEVER;
	}
}

D3D12_STATIC_BORDER_COLOR AstralLayerDirectX12::DX12RootSignature::ConvBorderColor(ATL_BORDER_COLOR color)
{
	switch (color)
	{
	case ATL_BORDER_COLOR::TRANSPARENT_BLACK:  return D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	case ATL_BORDER_COLOR::OPAQUE_BLACK: return D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
	case ATL_BORDER_COLOR::OPAQUE_WHITE: return D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
	default: return D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	}
}

AstralLayerDirectX12::DX12RootSignature::~DX12RootSignature()
{
	if (m_pRootSignature != nullptr)
		m_pRootSignature->Release();
}

void AstralLayerDirectX12::DX12RootSignature::GetHandle(
	void** ppOut, 
	int Handle)
{
	switch (Handle)
	{
	case ROOTSIGNATURE_ROOTSIGNATURE:
		*ppOut = m_pRootSignature;
		break;
	case ROOTSIGNATURE_NUMPARAMETOR:
		*ppOut = &m_NumParametor;
		break;
	}
}

void AstralLayerDirectX12::DX12RootSignature::Release()
{
	delete this;
}

bool AstralLayerDirectX12::DX12RootSignature::Create(ID3D12Device* pDevice, ATL_ROOT_SIGNATURE_DESC& Desc)
{
	//変数セット
	m_NumParametor = Desc.NumRootParameters;

	//変数準備
	D3D12_DESCRIPTOR_RANGE* range = new D3D12_DESCRIPTOR_RANGE[Desc.NumRootParameters];
	D3D12_ROOT_PARAMETER* root = new D3D12_ROOT_PARAMETER[Desc.NumRootParameters];

	//レンジとルートパラメーターセット
	for (unsigned int rp = 0; rp < Desc.NumRootParameters; rp++)
	{
		//レンジ
		range[rp].RangeType = ConvRangeType(Desc.pRootParameters[rp].Type);
		range[rp].NumDescriptors = 1;
		range[rp].BaseShaderRegister = Desc.pRootParameters[rp].BaceShaderRegister;
		range[rp].RegisterSpace = 0;
		range[rp].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		root[rp].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		root[rp].DescriptorTable.NumDescriptorRanges = 1;
		root[rp].DescriptorTable.pDescriptorRanges = &range[rp];
		root[rp].ShaderVisibility = ConvVisibility(Desc.pRootParameters[rp].ShaderVisibirity);
	}

	//サンプラー
	D3D12_STATIC_SAMPLER_DESC* Samplar = nullptr;
	if (Desc.NumSamplers != 0)
	{
		Samplar = new D3D12_STATIC_SAMPLER_DESC[Desc.NumSamplers];
		for (unsigned int s = 0; s < Desc.NumSamplers; s++)
		{
			ATL_SAMPLER_DESC* desc = &Desc.pSamplers[s];
			Samplar[s].Filter = ConvFilter(desc->Filter);
			Samplar[s].AddressU = ConvAddressMode(desc->AddressU);
			Samplar[s].AddressV = ConvAddressMode(desc->AddressV);
			Samplar[s].AddressW = ConvAddressMode(desc->AddressW);
			Samplar[s].MipLODBias = desc->MipLODBias;
			Samplar[s].MaxAnisotropy = desc->MaxAnisotropy;
			Samplar[s].ComparisonFunc = ConvComparisonFunc(desc->ComparisionFunc);
			Samplar[s].BorderColor = ConvBorderColor(desc->BorderColor);
			Samplar[s].MinLOD = desc->MinLOD;
			Samplar[s].MaxLOD = desc->MaxLOD;
			Samplar[s].ShaderRegister = desc->ShaderRegister;
			Samplar[s].RegisterSpace = 0;
			Samplar[s].ShaderVisibility = ConvVisibility(desc->Visibility);
		}
	}
	//デスク
	D3D12_ROOT_SIGNATURE_DESC desc{};
	desc.NumParameters = m_NumParametor;
	desc.pParameters = root;
	desc.NumStaticSamplers = Desc.NumSamplers;
	desc.pStaticSamplers = Samplar;
	desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//ルートパラメーターをシリアライズ化する
	ID3DBlob* pBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1, &pBlob, nullptr);
	delete[] range;
	delete[] root;
	if (FAILED(hr))
		return false;

	//ルートシグネチャー作成
	hr = pDevice->CreateRootSignature(
		0,
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		IID_PPV_ARGS(&m_pRootSignature)
	);
	pBlob->Release();
	if (FAILED(hr))
		return false;

	return true;
}

