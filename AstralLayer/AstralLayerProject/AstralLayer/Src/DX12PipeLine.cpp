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
	if (m_pPipeLine != nullptr)
		m_pPipeLine->Release();
}

void AstralLayerDirectX12::DX12PipeLine::GetHandle(
	void** ppOut, 
	int Handle)
{
	*ppOut = m_pPipeLine;
	Handle;
}

void AstralLayerDirectX12::DX12PipeLine::Release()
{
	delete this;
}

bool AstralLayerDirectX12::DX12PipeLine::Create(
	ID3D12Device* pDevice, 
	AstralLayer::ATLIRootSignature* pRootSignature, 
	ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc)
{
	//ルートシグネチャー準備
	ID3D12RootSignature* d3droot = nullptr;
	reinterpret_cast<AstralRHI::RHIRootSignature*>(pRootSignature)->
		GetHandle(reinterpret_cast<void**>(&d3droot), ROOTSIGNATURE_ROOTSIGNATURE);

	//ブレンドステート準備
	D3D12_BLEND_DESC blend{};
	{
		ATL_BLEND_DESC& atl = Desc.BlendState;
		blend.AlphaToCoverageEnable = atl.AlphaToCoverageEnable;
		blend.IndependentBlendEnable = atl.IndependentBlendEnable;
		for (int i = 0; i < 8; i++)
		{
			ATL_RENDER_TARGET_BLEND_DESC& rtv = atl.RenderTarget[i];
			blend.RenderTarget[i].BlendEnable = rtv.BlendEnable;
			blend.RenderTarget[i].LogicOpEnable = false;
			blend.RenderTarget[i].SrcBlend = ConvBlend(rtv.SrcBlend);
			blend.RenderTarget[i].DestBlend = ConvBlend(rtv.DestBlend);
			blend.RenderTarget[i].BlendOp = ConvBlendOP(rtv.BlendOp);
			blend.RenderTarget[i].SrcBlendAlpha = ConvBlend(rtv.SrcBlendAlpha);
			blend.RenderTarget[i].DestBlendAlpha = ConvBlend(rtv.DestBlendAlpha);
			blend.RenderTarget[i].BlendOpAlpha = ConvBlendOP(rtv.BlendOpAlpha);
			blend.RenderTarget[i].LogicOp = D3D12_LOGIC_OP_NOOP;
			blend.RenderTarget[i].RenderTargetWriteMask = static_cast<unsigned char>(rtv.RenderTargetWriteMask);
		}
	}

	//ラスタライザー準備
	D3D12_RASTERIZER_DESC rast{};
	{
		ATL_RASTERIZER_DESC& atl = Desc.RasterizerState;
		rast.FillMode = ConvFillMode(atl.FillMode);
		rast.CullMode = ConvCullMode(atl.CullMode);
		rast.FrontCounterClockwise = atl.FrontCounterClockwise;
		rast.DepthBias = atl.DepthBias;
		rast.DepthBiasClamp = atl.DepthBiasClamp;
		rast.SlopeScaledDepthBias = atl.SlopeScaledDepthBias;
		rast.DepthClipEnable = atl.DepthClipEnable;
		rast.MultisampleEnable = atl.MultisampleEnable;
		rast.AntialiasedLineEnable = atl.AntialiasedLineEnable;
		rast.ForcedSampleCount = 0;
		rast.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	}

	//デプスステンシルステート
	D3D12_DEPTH_STENCIL_DESC depth{};
	{
		ATL_DEPTH_STENCIL_DESC& atl = Desc.DepthStencilState;
		depth.DepthEnable = atl.DepthEnable;
		depth.DepthWriteMask = ConvWriteMask(atl.DepthWriteMask);
		depth.DepthFunc = ConvFunc(atl.DepthFunc);
		depth.StencilEnable = atl.StencilEnable;
		depth.StencilReadMask = atl.StencilReadMask;
		depth.StencilWriteMask = atl.StencilWriteMask;
		
		depth.FrontFace.StencilFailOp = ConvStencilOP(atl.FrontFace.StencilFailOp);
		depth.FrontFace.StencilDepthFailOp = ConvStencilOP(atl.FrontFace.StencilDepthFailOp);
		depth.FrontFace.StencilPassOp = ConvStencilOP(atl.FrontFace.StencilPassOp);
		depth.FrontFace.StencilFunc = ConvFunc(atl.FrontFace.StencilFunc);

		depth.BackFace.StencilFailOp = ConvStencilOP(atl.BackFace.StencilFailOp);
		depth.BackFace.StencilDepthFailOp = ConvStencilOP(atl.BackFace.StencilDepthFailOp);
		depth.BackFace.StencilPassOp = ConvStencilOP(atl.BackFace.StencilPassOp);
		depth.BackFace.StencilFunc = ConvFunc(atl.BackFace.StencilFunc);
	}

	//インプットレイアウト
	D3D12_INPUT_ELEMENT_DESC* element = new D3D12_INPUT_ELEMENT_DESC[Desc.InputLayout.NumElements];
	for (unsigned int i = 0; i < Desc.InputLayout.NumElements; i++)
	{
		const ATL_INPUT_ELEMENT_DESC& atl = Desc.InputLayout.pInputElementDescs[i];
		element[i].SemanticName = atl.SemanticsName;
		element[i].SemanticIndex = 0;
		element[i].Format = ConvDXGIFormat(atl.Format);
		element[i].InputSlot = 0;
		element[i].AlignedByteOffset = atl.AlignedByteOffset;
		element[i].InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		element[i].InstanceDataStepRate = 0;
	}

	//パイプラインデスク準備
	D3D12_GRAPHICS_PIPELINE_STATE_DESC desc{};
	desc.pRootSignature = d3droot;
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
	desc.SampleDesc = { Desc.Sample.Count,Desc.Sample.Quality };
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
