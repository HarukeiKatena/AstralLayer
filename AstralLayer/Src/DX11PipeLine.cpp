#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"
#include"../Include/ATL/AstralDirectX.h"

D3D11_BLEND AstralLayerDirectX11::DX11PipeLine::CalcBlend(ATL_BLEND blend)
{
	switch (blend)
	{
	case ATL_BLEND::ZERO:			return D3D11_BLEND_ZERO;
	case ATL_BLEND::ONE:			return D3D11_BLEND_ONE;
	case ATL_BLEND::SRC_COLOR:		return D3D11_BLEND_SRC_COLOR;
	case ATL_BLEND::INV_SRC_COLOR:	return D3D11_BLEND_INV_SRC_COLOR;
	case ATL_BLEND::SRC_ALPHA:		return D3D11_BLEND_SRC_ALPHA;
	case ATL_BLEND::INV_SRC_ALPHA:	return D3D11_BLEND_INV_SRC_ALPHA;
	case ATL_BLEND::DEST_ALPHA:		return D3D11_BLEND_DEST_ALPHA;
	case ATL_BLEND::INV_DEST_ALPHA: return D3D11_BLEND_INV_DEST_ALPHA;
	case ATL_BLEND::DEST_COLOR:		return D3D11_BLEND_DEST_COLOR;
	case ATL_BLEND::INV_DEST_COLOR: return D3D11_BLEND_INV_DEST_COLOR;
	case ATL_BLEND::SRC_ALPHA_SAT:	return D3D11_BLEND_SRC_ALPHA_SAT;
	case ATL_BLEND::SRC1_COLOR:		return D3D11_BLEND_SRC1_COLOR;
	case ATL_BLEND::INV_SRC1_COLOR: return D3D11_BLEND_INV_SRC1_COLOR;
	case ATL_BLEND::SRC1_ALPHA:		return D3D11_BLEND_SRC1_ALPHA;
	case ATL_BLEND::INV_SRC1_ALPHA: return D3D11_BLEND_INV_SRC1_ALPHA;
	default:						return D3D11_BLEND_ZERO;
	}
}

D3D11_BLEND_OP AstralLayerDirectX11::DX11PipeLine::CalcBlendOp(ATL_BLEND_OP op)
{
	switch (op)
	{
	case ATL_BLEND_OP::ADD:			return D3D11_BLEND_OP_ADD;
	case ATL_BLEND_OP::SUBTRACT:	return D3D11_BLEND_OP_SUBTRACT;
	case ATL_BLEND_OP::REV_SUBTRACT: return D3D11_BLEND_OP_REV_SUBTRACT;
	case ATL_BLEND_OP::MIN:			return D3D11_BLEND_OP_MIN;
	case ATL_BLEND_OP::MAX:			return D3D11_BLEND_OP_MAX;
	default:						return D3D11_BLEND_OP_ADD;
	}
}

D3D11_FILL_MODE AstralLayerDirectX11::DX11PipeLine::CalcFill(ATL_FILL_MODE fill)
{
	switch (fill)
	{
	case ATL_FILL_MODE::WIREFRAME:	return D3D11_FILL_WIREFRAME;
	case ATL_FILL_MODE::SOLID:		return D3D11_FILL_SOLID;
	default:						return D3D11_FILL_SOLID;
	}
}

D3D11_CULL_MODE AstralLayerDirectX11::DX11PipeLine::CalcCull(ATL_CULL_MODE cull)
{
	switch (cull)
	{
	case ATL_CULL_MODE::NONE: return D3D11_CULL_NONE;
	case ATL_CULL_MODE::FRONT: return D3D11_CULL_FRONT;
	case ATL_CULL_MODE::BACK: return D3D11_CULL_BACK;
	default: return D3D11_CULL_BACK;
	}
}

D3D11_DEPTH_WRITE_MASK AstralLayerDirectX11::DX11PipeLine::CalcWriteMask(ATL_DEPTH_WRITE_MASK mask)
{
	switch (mask)
	{
	case ATL_DEPTH_WRITE_MASK::ZERO: return D3D11_DEPTH_WRITE_MASK_ZERO;
	case ATL_DEPTH_WRITE_MASK::ALL: return D3D11_DEPTH_WRITE_MASK_ALL;
	default: return D3D11_DEPTH_WRITE_MASK_ZERO;
	}
}

D3D11_COMPARISON_FUNC AstralLayerDirectX11::DX11PipeLine::CalcFunc(ATL_COMPARISON_FUNC func)
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

D3D11_STENCIL_OP AstralLayerDirectX11::DX11PipeLine::CalcStencilOp(ATL_STENCIL_OP op)
{
	switch (op)
	{
	case ATL_STENCIL_OP::KEEP: return D3D11_STENCIL_OP_KEEP;
	case ATL_STENCIL_OP::ZERO: return D3D11_STENCIL_OP_ZERO;
	case ATL_STENCIL_OP::INCR_SAT:return D3D11_STENCIL_OP_INCR_SAT;
	case ATL_STENCIL_OP::DECR_SAT:return D3D11_STENCIL_OP_DECR_SAT;
	case ATL_STENCIL_OP::INVERT: return D3D11_STENCIL_OP_INVERT;
	case ATL_STENCIL_OP::INCR: return D3D11_STENCIL_OP_INCR;
	case ATL_STENCIL_OP::DECR: return D3D11_STENCIL_OP_DECR;
	default: return D3D11_STENCIL_OP_KEEP;
	}
}

D3D11_FILTER AstralLayerDirectX11::DX11PipeLine::ConvFilter(ATL_FILTER Filter)
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

D3D11_TEXTURE_ADDRESS_MODE AstralLayerDirectX11::DX11PipeLine::ConvAddressMode(ATL_ADDRESS_MODE mode)
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

D3D11_COMPARISON_FUNC AstralLayerDirectX11::DX11PipeLine::ConvComparisonFunc(ATL_COMPARISON_FUNC func)
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

void AstralLayerDirectX11::DX11PipeLine::ConvBorderColor(ATL_BORDER_COLOR border, float* out_color)
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

bool AstralLayerDirectX11::DX11PipeLine::CreateVertexShader(
	ID3D11Device* pDevice, 
	ATL_SHADER_BYTECODE& vs,
	ATL_INPUT_LAYOUT_DESC& input)
{
	//頂点シェーダー
	HRESULT hr = pDevice->CreateVertexShader(
		vs.pShaderBytecode,
		vs.BytecodeLength,
		nullptr,
		&m_State.VertexShader);
	if (FAILED(hr))
		return false;

	//インプットレイアウト準備
	D3D11_INPUT_ELEMENT_DESC* element = new D3D11_INPUT_ELEMENT_DESC[input.NumElements];
	for (unsigned int i = 0; i < input.NumElements; i++)
	{
		const ATL_INPUT_ELEMENT_DESC& atl = input.pInputElementDescs[i];
		element[i].SemanticName = atl.SemanticsName;
		element[i].SemanticIndex = 0;
		element[i].Format = ConvDXGIFormat(atl.Format);
		element[i].InputSlot = 0;
		element[i].AlignedByteOffset = atl.AlignedByteOffset;
		element[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		element[i].InstanceDataStepRate = 0;
	}

	//インプットレイアウト作成
	hr = pDevice->CreateInputLayout(
		element,
		input.NumElements,
		vs.pShaderBytecode,
		vs.BytecodeLength,
		m_State.InputLayout.GetAddressOf());
	delete[] element;
	if (FAILED(hr))
	{
		this->~DX11PipeLine();
		return false;
	}

	return true;
}

bool AstralLayerDirectX11::DX11PipeLine::CreatePixelShader(ID3D11Device* pDevice, ATL_SHADER_BYTECODE& ps)
{
	HRESULT hr = pDevice->CreatePixelShader(ps.pShaderBytecode, ps.BytecodeLength, nullptr, m_State.PixelShader.GetAddressOf());
	if (FAILED(hr))
	{
		this->~DX11PipeLine();
		return false;
	}
	return true;
}

bool AstralLayerDirectX11::DX11PipeLine::CreateBlendState(ID3D11Device* pDevice, ATL_BLEND_DESC& blend)
{
	D3D11_BLEND_DESC BlendState{};
	BlendState.AlphaToCoverageEnable = blend.AlphaToCoverageEnable;
	BlendState.IndependentBlendEnable = blend.IndependentBlendEnable;
	for (unsigned int i = 0; i < 8; i++)
	{
		BlendState.RenderTarget[i].BlendEnable = blend.RenderTarget[i].BlendEnable;
		BlendState.RenderTarget[i].SrcBlend = CalcBlend(blend.RenderTarget[i].SrcBlend);
		BlendState.RenderTarget[i].DestBlend = CalcBlend(blend.RenderTarget[i].DestBlend);
		BlendState.RenderTarget[i].BlendOp = CalcBlendOp(blend.RenderTarget[i].BlendOp);
		BlendState.RenderTarget[i].SrcBlendAlpha = CalcBlend(blend.RenderTarget[i].SrcBlendAlpha);
		BlendState.RenderTarget[i].DestBlendAlpha = CalcBlend(blend.RenderTarget[i].DestBlendAlpha);
		BlendState.RenderTarget[i].BlendOpAlpha = CalcBlendOp(blend.RenderTarget[i].BlendOpAlpha);
		BlendState.RenderTarget[i].RenderTargetWriteMask = static_cast<unsigned char>(blend.RenderTarget[i].RenderTargetWriteMask);
	}
	HRESULT hr = pDevice->CreateBlendState(&BlendState, m_State.BlendState.GetAddressOf());
	if (FAILED(hr))
	{
		this->~DX11PipeLine();
		return false;
	}
	return true;
}

bool AstralLayerDirectX11::DX11PipeLine::CreateRasterizer(ID3D11Device* pDevice, ATL_RASTERIZER_DESC& rasterizer)
{
	D3D11_RASTERIZER_DESC Rasterizer{};
	Rasterizer.FillMode = CalcFill(rasterizer.FillMode);
	Rasterizer.CullMode = CalcCull(rasterizer.CullMode);
	Rasterizer.FrontCounterClockwise = rasterizer.FrontCounterClockwise;
	Rasterizer.DepthBias = rasterizer.DepthBias;
	Rasterizer.DepthBiasClamp = rasterizer.DepthBiasClamp;
	Rasterizer.SlopeScaledDepthBias = rasterizer.SlopeScaledDepthBias;
	Rasterizer.DepthClipEnable = rasterizer.DepthClipEnable;
	Rasterizer.ScissorEnable = false;
	Rasterizer.MultisampleEnable = rasterizer.MultisampleEnable;
	Rasterizer.AntialiasedLineEnable = rasterizer.AntialiasedLineEnable;

	HRESULT hr = pDevice->CreateRasterizerState(&Rasterizer, m_State.Rasterizer.GetAddressOf());
	if (FAILED(hr))
	{
		this->~DX11PipeLine();
		return false;
	}
	return true;
}

bool AstralLayerDirectX11::DX11PipeLine::CreateDepthStencilDesc(
	ID3D11Device* pDevice, ATL_DEPTH_STENCIL_DESC ds)
{
	D3D11_DEPTH_STENCIL_DESC DepthStencil{};
	DepthStencil.DepthEnable = ds.DepthEnable;
	DepthStencil.DepthWriteMask = CalcWriteMask(ds.DepthWriteMask);
	DepthStencil.DepthFunc = CalcFunc(ds.DepthFunc);
	DepthStencil.StencilEnable = ds.StencilEnable;
	DepthStencil.StencilReadMask = ds.StencilReadMask;
	DepthStencil.StencilWriteMask = ds.StencilWriteMask;

	DepthStencil.FrontFace.StencilFailOp = CalcStencilOp(ds.FrontFace.StencilFailOp);
	DepthStencil.FrontFace.StencilDepthFailOp = CalcStencilOp(ds.FrontFace.StencilDepthFailOp);
	DepthStencil.FrontFace.StencilPassOp = CalcStencilOp(ds.FrontFace.StencilPassOp);
	DepthStencil.FrontFace.StencilFunc = CalcFunc(ds.FrontFace.StencilFunc);

	DepthStencil.BackFace.StencilFailOp = CalcStencilOp(ds.FrontFace.StencilFailOp);
	DepthStencil.BackFace.StencilDepthFailOp = CalcStencilOp(ds.FrontFace.StencilDepthFailOp);
	DepthStencil.BackFace.StencilPassOp = CalcStencilOp(ds.FrontFace.StencilPassOp);
	DepthStencil.BackFace.StencilFunc = CalcFunc(ds.FrontFace.StencilFunc);
	HRESULT hr = pDevice->CreateDepthStencilState(&DepthStencil, m_State.DepthStencil.GetAddressOf());
	if (FAILED(hr))
	{
		this->~DX11PipeLine();
		return false;
	}

	return true;
}

bool AstralLayerDirectX11::DX11PipeLine::CreateRootSignature(
	ATL_ROOT_PARAMETER* root, 
	unsigned int num)
{
	m_State.Parametor.NumRootParametors = num;
	m_State.Parametor.pParameters = new ATL_ROOT_PARAMETER[num];
	for (unsigned int i = 0; i < num; i++)
	{
		m_State.Parametor.pParameters[i] = root[i];
	}

	return true;
}

bool AstralLayerDirectX11::DX11PipeLine::CreateSampler(ID3D11Device* pDevice, ATL_SAMPLER_DESC* sampler, unsigned int num)
{
	m_State.Sampler.NumSampler = num;
	m_State.Sampler.pSampler = new DX11Sampler[num];
	for (unsigned int i = 0; i < num; i++)
	{
		D3D11_SAMPLER_DESC desc{};
		desc.Filter = ConvFilter(sampler[i].Filter);
		desc.AddressU = ConvAddressMode(sampler[i].AddressU);
		desc.AddressV = ConvAddressMode(sampler[i].AddressV);
		desc.AddressW = ConvAddressMode(sampler[i].AddressW);
		desc.MipLODBias = sampler[i].MipLODBias;
		desc.MaxAnisotropy = sampler[i].MaxAnisotropy;
		desc.ComparisonFunc = ConvComparisonFunc(sampler[i].ComparisionFunc);
		ConvBorderColor(sampler[i].BorderColor, desc.BorderColor);
		desc.MinLOD = sampler[i].MinLOD;
		desc.MaxLOD = sampler[i].MaxLOD;

		if (FAILED(pDevice->CreateSamplerState(&desc, &m_State.Sampler.pSampler[i].pSamplerState)))
		{
			this->~DX11PipeLine();
			return false;
		}

		//数値系を入れる
		m_State.Sampler.pSampler[i].SamplerRegister = sampler[i].ShaderRegister;
		m_State.Sampler.pSampler[i].SamplerVisibility = sampler[i].Visibility;
	}

	return true;
}

AstralLayerDirectX11::DX11PipeLine::~DX11PipeLine()
{
	//パラメーター解放
	delete[] m_State.Parametor.pParameters;

	//サンプラー解放
	delete[] m_State.Sampler.pSampler;
}

void AstralLayerDirectX11::DX11PipeLine::GetHandle(
	void** ppResource, 
	int Handle)
{
	Handle;
	*ppResource = &m_State;
}

void AstralLayerDirectX11::DX11PipeLine::Release()
{
	delete this;
}

bool AstralLayerDirectX11::DX11PipeLine::Create(
	ID3D11Device* pDevice, 
	ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc)
{
	//頂点シェーダーがある場合
	if (Desc.VS.BytecodeLength > 0)
	{
		if(CreateVertexShader(pDevice,Desc.VS,Desc.InputLayout) == false)
			return false;
	}

	//ピクセルシェーダーがある場合
	if (Desc.PS.BytecodeLength > 0)
	{
		if(CreatePixelShader(pDevice, Desc.PS) == false)
			return false;
	}

	//ブレンドステート
	if(CreateBlendState(pDevice,Desc.BlendState) == false)
		return false;

	//ラスタライザーデスク
	if(CreateRasterizer(pDevice,Desc.RasterizerState) == false)
		return false;


	//デプスステンシルデスク
	if(CreateDepthStencilDesc(pDevice,Desc.DepthStencilState) == false)
		return false;

	//ルートシグネチャー作成
	if(CreateRootSignature(Desc.RootSignature.pRootParameters,Desc.RootSignature.NumRootParameters) == false)
		return false;

	//サンプラー
	if(CreateSampler(pDevice,Desc.RootSignature.pSamplers,Desc.RootSignature.NumSamplers) == false)
		return false;

	return true;
}
