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

AstralLayerDirectX11::DX11PipeLine::~DX11PipeLine()
{
	//たくさん解放
	if (m_State.InputLayout != nullptr)
		m_State.InputLayout->Release();
	if (m_State.VertexShader != nullptr)
		m_State.VertexShader->Release();
	if (m_State.PixelShader != nullptr)
		m_State.PixelShader->Release();
	if (m_State.BlendState != nullptr)
		m_State.BlendState->Release();
	if (m_State.Rasterizer != nullptr)
		m_State.Rasterizer->Release();
	if (m_State.DepthStencil != nullptr)
		m_State.DepthStencil->Release();
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

bool AstralLayerDirectX11::DX11PipeLine::Create(ID3D11Device* pDevice, AstralLayer::ATLIRootSignature* pRootSignature, ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc)
{
	pRootSignature;//使わない

	HRESULT hr = S_OK;

	//頂点シェーダーがある場合
	if (Desc.VS.BytecodeLength > 0)
	{
		//頂点シェーダー
		hr = pDevice->CreateVertexShader(
			Desc.VS.pShaderBytecode, 
			Desc.VS.BytecodeLength, 
			nullptr, 
			&m_State.VertexShader);
		if (FAILED(hr))
			return false;

		//インプットレイアウト準備
		D3D11_INPUT_ELEMENT_DESC* element = new D3D11_INPUT_ELEMENT_DESC[Desc.InputLayout.NumElements];
		for (unsigned int i = 0; i < Desc.InputLayout.NumElements; i++)
		{
			const ATL_INPUT_ELEMENT_DESC& atl = Desc.InputLayout.pInputElementDescs[i];
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
			Desc.InputLayout.NumElements,
			Desc.VS.pShaderBytecode,
			Desc.VS.BytecodeLength,
			&m_State.InputLayout);
		delete[] element;
		if (FAILED(hr))
		{
			this->~DX11PipeLine();
			return false;
		}
	}

	//ピクセルシェーダーがある場合
	if (Desc.PS.BytecodeLength > 0)
	{
		hr = pDevice->CreatePixelShader(Desc.PS.pShaderBytecode, Desc.PS.BytecodeLength, nullptr, &m_State.PixelShader);
		if (FAILED(hr))
		{
			this->~DX11PipeLine();
			return false;
		}
	}

	//ブレンドステート
	D3D11_BLEND_DESC BlendState{};
	BlendState.AlphaToCoverageEnable = Desc.BlendState.AlphaToCoverageEnable;
	BlendState.IndependentBlendEnable = Desc.BlendState.IndependentBlendEnable;
	for (unsigned int i = 0; i < 8; i++)
	{
		BlendState.RenderTarget[i].BlendEnable =	Desc.BlendState.RenderTarget[i].BlendEnable;
		BlendState.RenderTarget[i].SrcBlend =		CalcBlend(Desc.BlendState.RenderTarget[i].SrcBlend);
		BlendState.RenderTarget[i].DestBlend =		CalcBlend(Desc.BlendState.RenderTarget[i].DestBlend);
		BlendState.RenderTarget[i].BlendOp =		CalcBlendOp(Desc.BlendState.RenderTarget[i].BlendOp);
		BlendState.RenderTarget[i].SrcBlendAlpha =	CalcBlend(Desc.BlendState.RenderTarget[i].SrcBlendAlpha);
		BlendState.RenderTarget[i].DestBlendAlpha = CalcBlend(Desc.BlendState.RenderTarget[i].DestBlendAlpha);
		BlendState.RenderTarget[i].BlendOpAlpha =	CalcBlendOp(Desc.BlendState.RenderTarget[i].BlendOpAlpha);
		BlendState.RenderTarget[i].RenderTargetWriteMask = static_cast<unsigned char>(Desc.BlendState.RenderTarget[i].RenderTargetWriteMask);
	}
	hr = pDevice->CreateBlendState(&BlendState, &m_State.BlendState);
	if (FAILED(hr))
	{
		this->~DX11PipeLine();
		return false;
	}

	//ラスタライザーデスク
	D3D11_RASTERIZER_DESC Rasterizer{};
	Rasterizer.FillMode =				CalcFill(Desc.RasterizerState.FillMode);
	Rasterizer.CullMode =				CalcCull(Desc.RasterizerState.CullMode);
	Rasterizer.FrontCounterClockwise =	Desc.RasterizerState.FrontCounterClockwise;
	Rasterizer.DepthBias =				Desc.RasterizerState.DepthBias;
	Rasterizer.DepthBiasClamp =			Desc.RasterizerState.DepthBiasClamp;
	Rasterizer.SlopeScaledDepthBias =	Desc.RasterizerState.SlopeScaledDepthBias;
	Rasterizer.DepthClipEnable =		Desc.RasterizerState.DepthClipEnable;
	Rasterizer.ScissorEnable=			false;
	Rasterizer.MultisampleEnable =		Desc.RasterizerState.MultisampleEnable;
	Rasterizer.AntialiasedLineEnable =	Desc.RasterizerState.AntialiasedLineEnable;

	hr = pDevice->CreateRasterizerState(&Rasterizer, &m_State.Rasterizer);
	if (FAILED(hr))
	{
		this->~DX11PipeLine();
		return false;
	}


	//デプスステンシルデスク
	D3D11_DEPTH_STENCIL_DESC DepthStencil{};
	DepthStencil.DepthEnable =		Desc.DepthStencilState.DepthEnable;
	DepthStencil.DepthWriteMask =	CalcWriteMask(Desc.DepthStencilState.DepthWriteMask);
	DepthStencil.DepthFunc =		CalcFunc(Desc.DepthStencilState.DepthFunc);
	DepthStencil.StencilEnable =	Desc.DepthStencilState.StencilEnable;
	DepthStencil.StencilReadMask =	Desc.DepthStencilState.StencilReadMask;
	DepthStencil.StencilWriteMask = Desc.DepthStencilState.StencilWriteMask;

	DepthStencil.FrontFace.StencilFailOp =		CalcStencilOp(Desc.DepthStencilState.FrontFace.StencilFailOp);
	DepthStencil.FrontFace.StencilDepthFailOp = CalcStencilOp(Desc.DepthStencilState.FrontFace.StencilDepthFailOp);
	DepthStencil.FrontFace.StencilPassOp =		CalcStencilOp(Desc.DepthStencilState.FrontFace.StencilPassOp);
	DepthStencil.FrontFace.StencilFunc =		CalcFunc(Desc.DepthStencilState.FrontFace.StencilFunc);

	DepthStencil.BackFace.StencilFailOp =		CalcStencilOp(Desc.DepthStencilState.FrontFace.StencilFailOp);
	DepthStencil.BackFace.StencilDepthFailOp =	CalcStencilOp(Desc.DepthStencilState.FrontFace.StencilDepthFailOp);
	DepthStencil.BackFace.StencilPassOp =		CalcStencilOp(Desc.DepthStencilState.FrontFace.StencilPassOp);
	DepthStencil.BackFace.StencilFunc =			CalcFunc(Desc.DepthStencilState.FrontFace.StencilFunc);
	hr = pDevice->CreateDepthStencilState(&DepthStencil, &m_State.DepthStencil);
	if (FAILED(hr))
	{
		this->~DX11PipeLine();
		return false;
	}

	return true;
}
