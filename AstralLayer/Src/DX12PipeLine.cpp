#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"
#include "../Include/ATL/AstralDirectX.h"

D3D12_FILL_MODE AstralLayerDirectX12::DX12PipeLine::ConvFillMode(ATL_FILL_MODE mode)
{
	switch (mode)
	{
	case ATL_FILL_MODE::WIREFRAME: return D3D12_FILL_MODE_WIREFRAME;
	case ATL_FILL_MODE::SOLID: return D3D12_FILL_MODE_SOLID;
	default: return D3D12_FILL_MODE_SOLID;
	}
}

D3D12_CULL_MODE AstralLayerDirectX12::DX12PipeLine::ConvCullMode(ATL_CULL_MODE mode)
{
	switch (mode)
	{
	case ATL_CULL_MODE::NONE: return D3D12_CULL_MODE_NONE;
	case ATL_CULL_MODE::FRONT: return D3D12_CULL_MODE_FRONT;
	case ATL_CULL_MODE::BACK: return D3D12_CULL_MODE_BACK;
	default: return D3D12_CULL_MODE_NONE;
	}
}

D3D12_BLEND AstralLayerDirectX12::DX12PipeLine::ConvBlend(ATL_BLEND blend)
{
	switch (blend)
	{
	case ATL_BLEND::ZERO: return D3D12_BLEND_ZERO;
	case ATL_BLEND::ONE: return D3D12_BLEND_ONE;
	case ATL_BLEND::SRC_COLOR: return D3D12_BLEND_SRC_COLOR;
	case ATL_BLEND::INV_SRC_COLOR: return D3D12_BLEND_INV_SRC_COLOR;
	case ATL_BLEND::SRC_ALPHA: return D3D12_BLEND_SRC_ALPHA;
	case ATL_BLEND::INV_SRC_ALPHA: return D3D12_BLEND_INV_SRC_ALPHA;
	case ATL_BLEND::DEST_ALPHA: return D3D12_BLEND_DEST_ALPHA;
	case ATL_BLEND::INV_DEST_ALPHA: return D3D12_BLEND_INV_DEST_ALPHA;
	case ATL_BLEND::DEST_COLOR: return D3D12_BLEND_DEST_COLOR;
	case ATL_BLEND::INV_DEST_COLOR: return D3D12_BLEND_INV_DEST_COLOR;
	case ATL_BLEND::SRC_ALPHA_SAT: return D3D12_BLEND_SRC_ALPHA_SAT;
	case ATL_BLEND::SRC1_COLOR: return D3D12_BLEND_SRC1_COLOR;
	case ATL_BLEND::INV_SRC1_COLOR: return D3D12_BLEND_INV_SRC1_COLOR;
	case ATL_BLEND::SRC1_ALPHA: return D3D12_BLEND_SRC1_ALPHA;
	case ATL_BLEND::INV_SRC1_ALPHA: return D3D12_BLEND_INV_SRC1_ALPHA;
	default: return D3D12_BLEND_ZERO;
	}
}

D3D12_DEPTH_WRITE_MASK AstralLayerDirectX12::DX12PipeLine::ConvWriteMask(ATL_DEPTH_WRITE_MASK mask)
{
	switch (mask)
	{
	case ATL_DEPTH_WRITE_MASK::ZERO: return D3D12_DEPTH_WRITE_MASK_ZERO;
	case ATL_DEPTH_WRITE_MASK::ALL: return D3D12_DEPTH_WRITE_MASK_ALL;
	default: return D3D12_DEPTH_WRITE_MASK_ALL;
	}
}

D3D12_COMPARISON_FUNC AstralLayerDirectX12::DX12PipeLine::ConvFunc(ATL_COMPARISON_FUNC func)
{
	switch (func)
	{
	case ATL_COMPARISON_FUNC::NEVER: return D3D12_COMPARISON_FUNC_NEVER;
	case ATL_COMPARISON_FUNC::LESS: return D3D12_COMPARISON_FUNC_LESS;
	case ATL_COMPARISON_FUNC::EQUAL: return D3D12_COMPARISON_FUNC_EQUAL;
	case ATL_COMPARISON_FUNC::LESS_EQUAL: return D3D12_COMPARISON_FUNC_LESS_EQUAL;
	case ATL_COMPARISON_FUNC::GREATER: return D3D12_COMPARISON_FUNC_GREATER;
	case ATL_COMPARISON_FUNC::NOT_EQUAL: return D3D12_COMPARISON_FUNC_NOT_EQUAL;
	case ATL_COMPARISON_FUNC::GREATER_EQUAL: return D3D12_COMPARISON_FUNC_GREATER_EQUAL;
	case ATL_COMPARISON_FUNC::ALWAYS: return D3D12_COMPARISON_FUNC_ALWAYS;
	default: return D3D12_COMPARISON_FUNC_LESS;
	}
}

D3D12_STENCIL_OP AstralLayerDirectX12::DX12PipeLine::ConvStencilOP(ATL_STENCIL_OP op)
{
	switch (op)
	{
	case ATL_STENCIL_OP::KEEP: return D3D12_STENCIL_OP_KEEP;
	case ATL_STENCIL_OP::ZERO: return D3D12_STENCIL_OP_ZERO;
	case ATL_STENCIL_OP::INCR_SAT: return D3D12_STENCIL_OP_INCR_SAT;
	case ATL_STENCIL_OP::DECR_SAT: return D3D12_STENCIL_OP_DECR_SAT;
	case ATL_STENCIL_OP::INVERT: return D3D12_STENCIL_OP_INVERT;
	case ATL_STENCIL_OP::INCR: return D3D12_STENCIL_OP_INCR;
	case ATL_STENCIL_OP::DECR: return D3D12_STENCIL_OP_DECR;
	default: return D3D12_STENCIL_OP_KEEP;
	}
}

D3D12_DESCRIPTOR_RANGE_TYPE AstralLayerDirectX12::DX12PipeLine::ConvRangeType(ATL_DESCRIPTOR_TYPE type)
{
	switch (type)
	{
	case ATL_DESCRIPTOR_TYPE::CBV: return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	case ATL_DESCRIPTOR_TYPE::SRV: return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	case ATL_DESCRIPTOR_TYPE::UAV: return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	default: return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	}
}

D3D12_SHADER_VISIBILITY AstralLayerDirectX12::DX12PipeLine::ConvVisibility(ATL_SHADER_VISIBILITY visibility)
{
	switch (visibility)
	{
	case ATL_SHADER_VISIBILITY::ALL:		return D3D12_SHADER_VISIBILITY_ALL;
	case ATL_SHADER_VISIBILITY::VERTEX:		return D3D12_SHADER_VISIBILITY_VERTEX;
	case ATL_SHADER_VISIBILITY::PIXEL:		return D3D12_SHADER_VISIBILITY_PIXEL;
	default: return D3D12_SHADER_VISIBILITY_ALL;
	}
}

D3D12_FILTER AstralLayerDirectX12::DX12PipeLine::ConvFilter(ATL_FILTER Filter)
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

D3D12_TEXTURE_ADDRESS_MODE AstralLayerDirectX12::DX12PipeLine::ConvAddressMode(ATL_ADDRESS_MODE mode)
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

D3D12_COMPARISON_FUNC AstralLayerDirectX12::DX12PipeLine::ConvComparisonFunc(ATL_COMPARISON_FUNC func)
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

D3D12_STATIC_BORDER_COLOR AstralLayerDirectX12::DX12PipeLine::ConvBorderColor(ATL_BORDER_COLOR color)
{
	switch (color)
	{
	case ATL_BORDER_COLOR::TRANSPARENT_BLACK:  return D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	case ATL_BORDER_COLOR::OPAQUE_BLACK: return D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
	case ATL_BORDER_COLOR::OPAQUE_WHITE: return D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
	default: return D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	}
}

D3D12_BLEND_DESC AstralLayerDirectX12::DX12PipeLine::CreateBlendDesc(ATL_BLEND_DESC& blend)
{
	//ブレンドデスク作成
	D3D12_BLEND_DESC out{};
	out.AlphaToCoverageEnable = blend.AlphaToCoverageEnable;
	out.IndependentBlendEnable = blend.IndependentBlendEnable;
	for (int i = 0; i < 8; i++)
	{
		ATL_RENDER_TARGET_BLEND_DESC& rtv = blend.RenderTarget[i];
		out.RenderTarget[i].BlendEnable = rtv.BlendEnable;
		out.RenderTarget[i].LogicOpEnable = false;
		out.RenderTarget[i].SrcBlend = ConvBlend(rtv.SrcBlend);
		out.RenderTarget[i].DestBlend = ConvBlend(rtv.DestBlend);
		out.RenderTarget[i].BlendOp = ConvBlendOP(rtv.BlendOp);
		out.RenderTarget[i].SrcBlendAlpha = ConvBlend(rtv.SrcBlendAlpha);
		out.RenderTarget[i].DestBlendAlpha = ConvBlend(rtv.DestBlendAlpha);
		out.RenderTarget[i].BlendOpAlpha = ConvBlendOP(rtv.BlendOpAlpha);
		out.RenderTarget[i].LogicOp = D3D12_LOGIC_OP_NOOP;
		out.RenderTarget[i].RenderTargetWriteMask = static_cast<unsigned char>(rtv.RenderTargetWriteMask);
	}

	return out;
}

D3D12_RASTERIZER_DESC AstralLayerDirectX12::DX12PipeLine::CreateRasterizerDesc(ATL_RASTERIZER_DESC& rast)
{
	//ラスタライザー作成
	D3D12_RASTERIZER_DESC out{};
	out.FillMode = ConvFillMode(rast.FillMode);
	out.CullMode = ConvCullMode(rast.CullMode);
	out.FrontCounterClockwise = rast.FrontCounterClockwise;
	out.DepthBias = rast.DepthBias;
	out.DepthBiasClamp = rast.DepthBiasClamp;
	out.SlopeScaledDepthBias = rast.SlopeScaledDepthBias;
	out.DepthClipEnable = rast.DepthClipEnable;
	out.MultisampleEnable = rast.MultisampleEnable;
	out.AntialiasedLineEnable = rast.AntialiasedLineEnable;
	out.ForcedSampleCount = 0;
	out.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	return out;
}

D3D12_DEPTH_STENCIL_DESC AstralLayerDirectX12::DX12PipeLine::CreateDepthStencilDesc(ATL_DEPTH_STENCIL_DESC& depth)
{
	//デプスステンシル作成
	D3D12_DEPTH_STENCIL_DESC out{};
	out.DepthEnable = depth.DepthEnable;
	out.DepthWriteMask = ConvWriteMask(depth.DepthWriteMask);
	out.DepthFunc = ConvFunc(depth.DepthFunc);
	out.StencilEnable = depth.StencilEnable;
	out.StencilReadMask = depth.StencilReadMask;
	out.StencilWriteMask = depth.StencilWriteMask;

	out.FrontFace.StencilFailOp = ConvStencilOP(depth.FrontFace.StencilFailOp);
	out.FrontFace.StencilDepthFailOp = ConvStencilOP(depth.FrontFace.StencilDepthFailOp);
	out.FrontFace.StencilPassOp = ConvStencilOP(depth.FrontFace.StencilPassOp);
	out.FrontFace.StencilFunc = ConvFunc(depth.FrontFace.StencilFunc);

	out.BackFace.StencilFailOp = ConvStencilOP(depth.BackFace.StencilFailOp);
	out.BackFace.StencilDepthFailOp = ConvStencilOP(depth.BackFace.StencilDepthFailOp);
	out.BackFace.StencilPassOp = ConvStencilOP(depth.BackFace.StencilPassOp);
	out.BackFace.StencilFunc = ConvFunc(depth.BackFace.StencilFunc);

	return out;
}

D3D12_INPUT_ELEMENT_DESC* AstralLayerDirectX12::DX12PipeLine::CreateInputLayout(ATL_INPUT_LAYOUT_DESC& input)
{
	D3D12_INPUT_ELEMENT_DESC* element = new D3D12_INPUT_ELEMENT_DESC[input.NumElements];
	for (unsigned int i = 0; i < input.NumElements; i++)
	{
		const ATL_INPUT_ELEMENT_DESC& atl = input.pInputElementDescs[i];
		element[i].SemanticName = atl.SemanticsName;
		element[i].SemanticIndex = 0;
		element[i].Format = ConvDXGIFormat(atl.Format);
		element[i].InputSlot = 0;
		element[i].AlignedByteOffset = atl.AlignedByteOffset;
		element[i].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		element[i].InstanceDataStepRate = 0;
	}

	return element;
}

void AstralLayerDirectX12::DX12PipeLine::CreateRangeParametor(
	ATL_ROOT_PARAMETER* parametor, 
	unsigned int num, 
	D3D12_DESCRIPTOR_RANGE** range, 
	D3D12_ROOT_PARAMETER** root)
{
	//変数準備

	D3D12_DESCRIPTOR_RANGE* outrange = new D3D12_DESCRIPTOR_RANGE[num];
	D3D12_ROOT_PARAMETER* outroot = new D3D12_ROOT_PARAMETER[num];

	//レンジとルートパラメーターセット
	for (unsigned int rp = 0; rp < num; rp++)
	{
		//レンジ
		outrange[rp].RangeType = ConvRangeType(parametor[rp].Type);
		outrange[rp].NumDescriptors = 1;
		outrange[rp].BaseShaderRegister = parametor[rp].ShaderRegister;
		outrange[rp].RegisterSpace = 0;
		outrange[rp].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		outroot[rp].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		outroot[rp].DescriptorTable.NumDescriptorRanges = 1;
		outroot[rp].DescriptorTable.pDescriptorRanges = &outrange[rp];
		outroot[rp].ShaderVisibility = ConvVisibility(parametor[rp].ShaderVisibirity);
	}

	*range = outrange;
	*root = outroot;
}

D3D12_STATIC_SAMPLER_DESC* AstralLayerDirectX12::DX12PipeLine::CreateSampler(ATL_SAMPLER_DESC* sampler, unsigned int num)
{
	D3D12_STATIC_SAMPLER_DESC* out = new D3D12_STATIC_SAMPLER_DESC[num];
	for (unsigned int s = 0; s < num; s++)
	{
		ATL_SAMPLER_DESC* desc = &sampler[s];
		out[s].Filter = ConvFilter(desc->Filter);
		out[s].AddressU = ConvAddressMode(desc->AddressU);
		out[s].AddressV = ConvAddressMode(desc->AddressV);
		out[s].AddressW = ConvAddressMode(desc->AddressW);
		out[s].MipLODBias = desc->MipLODBias;
		out[s].MaxAnisotropy = desc->MaxAnisotropy;
		out[s].ComparisonFunc = ConvComparisonFunc(desc->ComparisionFunc);
		out[s].BorderColor = ConvBorderColor(desc->BorderColor);
		out[s].MinLOD = desc->MinLOD;
		out[s].MaxLOD = desc->MaxLOD;
		out[s].ShaderRegister = desc->ShaderRegister;
		out[s].RegisterSpace = 0;
		out[s].ShaderVisibility = ConvVisibility(desc->Visibility);
	}

	return out;
}

bool AstralLayerDirectX12::DX12PipeLine::CreateRootSignature(
	ID3D12Device* pDevice, 
	ATL_ROOT_SIGNATURE_DESC& root)
{
	//パラメーターとレンジ作成
	D3D12_DESCRIPTOR_RANGE* range = nullptr;
	D3D12_ROOT_PARAMETER* param = nullptr;
	CreateRangeParametor(
		root.pRootParameters,
		root.NumRootParameters,
		&range,
		&param
	);

	//サンプラー
	D3D12_STATIC_SAMPLER_DESC* sampler = nullptr;
	if (root.NumSamplers > 0)
	{
		sampler = CreateSampler(root.pSamplers,root.NumSamplers);
	}

	//ルートシグネチャーデスク
	D3D12_ROOT_SIGNATURE_DESC desc{};
	desc.NumParameters = root.NumRootParameters;
	desc.pParameters = param;
	desc.NumStaticSamplers = root.NumSamplers;
	desc.pStaticSamplers = sampler;
	desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//ルートパラメーターをシリアライズ化する
	ID3DBlob* pBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1, &pBlob, nullptr);
	delete[] range;
	delete[] param;
	delete[] sampler;
	if (FAILED(hr))
		return false;

	//ルートシグネチャー作成
	pDevice->CreateRootSignature(
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

D3D12_BLEND_OP AstralLayerDirectX12::DX12PipeLine::ConvBlendOP(ATL_BLEND_OP blend)
{
	switch (blend)
	{
	case ATL_BLEND_OP::ADD: return D3D12_BLEND_OP_ADD;
	case ATL_BLEND_OP::SUBTRACT: return D3D12_BLEND_OP_SUBTRACT;
	case ATL_BLEND_OP::REV_SUBTRACT: return D3D12_BLEND_OP_REV_SUBTRACT;
	case ATL_BLEND_OP::MIN: return D3D12_BLEND_OP_MIN;
	case ATL_BLEND_OP::MAX: return D3D12_BLEND_OP_MAX;
	default: return D3D12_BLEND_OP_ADD;
	}
}

AstralLayerDirectX12::DX12PipeLine::~DX12PipeLine()
{

}

void AstralLayerDirectX12::DX12PipeLine::GetHandle(
	void** ppOut, 
	int Handle)
{
	switch (Handle)
	{
	case 0:
		*ppOut = m_pPipeLine.Get();
		break;
	case 1:
		*ppOut = m_pRootSignature.Get();
		break;
	default:
		break;
	}
}

void AstralLayerDirectX12::DX12PipeLine::Release()
{
	delete this;
}

bool AstralLayerDirectX12::DX12PipeLine::Create(
	ID3D12Device* pDevice, 
	ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc)
{
	//ルートシグネチャー準備
	if(CreateRootSignature(pDevice, Desc.RootSignature) == false)
		return false;

	//ブレンドステート準備
	D3D12_BLEND_DESC blend = CreateBlendDesc(Desc.BlendState);

	//ラスタライザー準備
	D3D12_RASTERIZER_DESC rast = CreateRasterizerDesc(Desc.RasterizerState);

	//デプスステンシルステート
	D3D12_DEPTH_STENCIL_DESC depth = CreateDepthStencilDesc(Desc.DepthStencilState);

	//インプットレイアウト
	D3D12_INPUT_ELEMENT_DESC* element = CreateInputLayout(Desc.InputLayout);

	//利用可能なMSAAの値を取得＆指定された数値より小さい場合使用可能な方を優先する
	DXGI_SAMPLE_DESC sample = GetMSAA(pDevice,Desc.Sample.Count);
	sample.Quality = sample.Quality < Desc.Sample.Quality ? sample.Quality : Desc.Sample.Quality;

	//パイプラインデスク準備
	D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};
	desc.pRootSignature = m_pRootSignature.Get();
	if (Desc.VS.BytecodeLength != 0)
		desc.VS = { Desc.VS.pShaderBytecode,Desc.VS.BytecodeLength };
	if (Desc.PS.BytecodeLength != 0)
		desc.PS = { Desc.PS.pShaderBytecode,Desc.PS.BytecodeLength };
	desc.DS = { nullptr,0 };
	desc.HS = { nullptr,0 };
	desc.GS = { nullptr,0 };
	memset(&desc.StreamOutput, 0, sizeof(desc.StreamOutput));
	desc.BlendState = blend;
	desc.SampleMask = UINT_MAX;
	desc.RasterizerState = rast;
	desc.DepthStencilState = depth;
	desc.InputLayout = { element,Desc.InputLayout.NumElements };
	desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
	desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	desc.NumRenderTargets = 1;
	desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	desc.SampleDesc = sample;
	desc.NodeMask = 0;
	desc.CachedPSO = { nullptr,0 };
	desc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;

	//パイプライン作成
	HRESULT hr = pDevice->CreateGraphicsPipelineState(
		&desc,
		IID_PPV_ARGS(&m_pPipeLine)
	);
	delete[] element;
	if (FAILED(hr))
		return false;

	return true;
}
