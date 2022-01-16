cbuffer WorldBuffer : register(b0)
{
	matrix WorldMatrix;
}
cbuffer ViewBuffer : register(b1)
{
	matrix ViewMatrix;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix ProjectionMatrix;
}

struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 UV   		: TEXCOORD0;
};


struct PS_IN
{
	float4 Position		: SV_POSITION;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 UV   		: TEXCOORD0;
};