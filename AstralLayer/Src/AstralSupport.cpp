#include"../Include/AstralSupport.h"

#include<stdio.h>
#include<cfloat>
#include"../Include/AstralDebug.h"

ATL_RESOURCE_DESC ATLSCreateConstantBufferResourceDesc(unsigned int ByteStructure, unsigned int Width, unsigned int ObjectNum, ATL_RESOURCE_TYPE Type)
{
	ATL_RESOURCE_DESC out{
		ByteStructure,
		Width,
		1,
		ObjectNum,
		1,
		ATL_FORMAT::UNKNOWN,
		{1,0},
		Type,
		ATL_RESOURCE_FLAG::CONSTANTBUFFER
	};
	return out;
}

ATL_RESOURCE_DESC ATLSCreateVertexBufferResourceDesc(unsigned int ByteStructure, unsigned int Width, unsigned int ObjectNum, ATL_RESOURCE_TYPE Type)
{
	ATL_RESOURCE_DESC out{
		ByteStructure,
		Width,
		1,
		ObjectNum,
		1,
		ATL_FORMAT::UNKNOWN,
		{1,0},
		Type,
		ATL_RESOURCE_FLAG::VERTEXBUFFER
	};
	return out;
}

ATL_RESOURCE_DESC ATLSCreateIndexBufferResourceDesc(unsigned int ByteStructure, unsigned int Width, unsigned int ObjectNum, ATL_RESOURCE_TYPE Type)
{
	ATL_RESOURCE_DESC out{
		ByteStructure,
		Width,
		1,
		ObjectNum,
		1,
		ATL_FORMAT::R32_UINT,
		{1,0},
		Type,
		ATL_RESOURCE_FLAG::INDEXBUFFER
	};
	return out;
}

ATL_RESOURCE_DESC ATLSCreateTexture2DBufferResourceDesc(
	unsigned int ByteStructure, 
	unsigned int Width, 
	unsigned int Height, 
	unsigned int MipLevel,
	ATL_FORMAT Format,
	ATL_SAMPLE_DESC SamplerDesc,
	ATL_RESOURCE_TYPE Type)
{
	ATL_RESOURCE_DESC out{
		ByteStructure,
		Width,
		Height,
		1,
		MipLevel,
		Format,
		SamplerDesc,
		Type,
		ATL_RESOURCE_FLAG::TEXTURE2D
	};
	return out;
}

ATL_SAMPLER_DESC ATLSCreateSamplerDesc(
	ATL_FILTER Filter, 
	ATL_ADDRESS_MODE AddressUVW, 
	unsigned int ShadeerRegister, 
	ATL_SHADER_VISIBILITY Visibility)
{
	ATL_SAMPLER_DESC out{
		Filter,
		AddressUVW,
		AddressUVW,
		AddressUVW,
		0.0,
		0,
		ATL_COMPARISON_FUNC::NEVER,
		ATL_BORDER_COLOR::OPAQUE_BLACK,
		0.0f,
		FLT_MAX,
		ShadeerRegister,
		Visibility
	};
	return out;
}

ATL_BLEND_DESC ATLSCreateBlendDesc()
{
	ATL_BLEND_DESC out;
	out.AlphaToCoverageEnable = false;
	out.IndependentBlendEnable = false;
	out.RenderTarget[0].BlendEnable = false;
	out.RenderTarget[0].SrcBlend = ATL_BLEND::ONE;
	out.RenderTarget[0].DestBlend = ATL_BLEND::ZERO;
	out.RenderTarget[0].BlendOp = ATL_BLEND_OP::ADD;
	out.RenderTarget[0].SrcBlendAlpha = ATL_BLEND::ZERO;
	out.RenderTarget[0].DestBlendAlpha = ATL_BLEND::ZERO;
	out.RenderTarget[0].BlendOpAlpha = ATL_BLEND_OP::ADD;
	out.RenderTarget[0].RenderTargetWriteMask = ATL_COLOR_WRITE_ENABLE::ALL;
	return out;
}

ATL_RASTERIZER_DESC ATLSCreateRasterizerDesc(ATL_FILL_MODE FillMode, ATL_CULL_MODE CullMode)
{
	ATL_RASTERIZER_DESC out{
		FillMode,
		CullMode,
		false,
		ATL_DEFAULT_DEPTH_BIAS,
		ATL_DEFAULT_DEPTH_BIAS_CLAMP,
		ATL_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
		true,
		false,
		false
	};

	return out;
}

ATL_GRAPHICS_PIPELINE_STATE_DESC ATLSCreatePipeLineStateDesc(ATL_SHADER_BYTECODE VS, ATL_SHADER_BYTECODE PS, ATL_BLEND_DESC BlendState, ATL_RASTERIZER_DESC RasterizerState, bool DepthEnable, bool StencilEnable, ATL_INPUT_LAYOUT_DESC InputLayout, unsigned int SampleCount, unsigned int SampleQuality)
{
	ATL_GRAPHICS_PIPELINE_STATE_DESC out;
	out.VS = VS;
	out.PS = PS;
	out.BlendState = BlendState;
	out.RasterizerState = RasterizerState;
	{
		out.DepthStencilState.DepthEnable = DepthEnable;
		out.DepthStencilState.DepthWriteMask = ATL_DEPTH_WRITE_MASK::ALL;
		out.DepthStencilState.DepthFunc = ATL_COMPARISON_FUNC::LESS;

		out.DepthStencilState.StencilEnable = StencilEnable;
		out.DepthStencilState.StencilReadMask = ATL_DEFAULT_STENCIL_READ_MASK;
		out.DepthStencilState.StencilWriteMask = ATL_DEFAULT_STENCIL_WRITE_MASK;

		out.DepthStencilState.FrontFace.StencilFailOp = ATL_STENCIL_OP::KEEP;
		out.DepthStencilState.FrontFace.StencilDepthFailOp = ATL_STENCIL_OP::KEEP;
		out.DepthStencilState.FrontFace.StencilPassOp = ATL_STENCIL_OP::INCR;
		out.DepthStencilState.FrontFace.StencilFunc = ATL_COMPARISON_FUNC::EQUAL;

		out.DepthStencilState.BackFace.StencilFailOp = ATL_STENCIL_OP::KEEP;
		out.DepthStencilState.BackFace.StencilDepthFailOp = ATL_STENCIL_OP::KEEP;
		out.DepthStencilState.BackFace.StencilPassOp = ATL_STENCIL_OP::INCR;
		out.DepthStencilState.BackFace.StencilFunc = ATL_COMPARISON_FUNC::EQUAL;
	}
	out.InputLayout = InputLayout;
	out.Sample.Count = SampleCount;
	out.Sample.Quality = SampleQuality;
	return out;
}

ATL_VIEWPORT ATLSCreateViewport(float ScreenWidth, float ScreenHeight)
{
	ATL_VIEWPORT out = {
		0.0f,
		0.0f,
		ScreenWidth,
		ScreenHeight,
		0.0f,
		1.0f
	};
	return out;
}

ATL_RECT ATLSCreateRect(unsigned int ScreenWidth, unsigned int ScreenHeight)
{
	ATL_RECT out = {
		0,
		0,
		ScreenWidth,
		ScreenHeight
	};
	return out;
}


ATLSShaderBinary::~ATLSShaderBinary()
{
	DeleteBuffer();
}

bool ATLSShaderBinary::LoadShaderBinary(const char* FilePath)
{
	FILE* fp = nullptr;

	fopen_s(&fp, FilePath, "rb");
	ATLAssertMessage(fp != nullptr, "シェーダーファイルの読み込みに失敗しました");
	if (fp == nullptr)
		return false;

	while (fgetc(fp) != EOF)
	{
		if (ferror(fp) != 0)
		{
			ATLAssertMessage(false, "シェーダーファイルの読み込みに失敗しました");
			fclose(fp);
			return false;
		}
		++m_Size;
	}

	fseek(fp, 0, SEEK_SET);
	m_Buffer = new unsigned char[m_Size];
	fread(m_Buffer, m_Size, 1, fp);
	fclose(fp);

	return true;
}

void ATLSShaderBinary::DeleteBuffer()
{
	if (m_Buffer != nullptr)
		delete[] m_Buffer;

	m_Size = 0;
}
