
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;
	wvp = mul(WorldMatrix, ViewMatrix);
	wvp = mul(wvp, ProjectionMatrix);

	Out.Diffuse = In.Diffuse;
	Out.Position = mul(float4(In.Position, 1.0f), wvp);
	Out.Normal = mul(float4(In.Normal, 0.0f), WorldMatrix);
	Out.UV = In.UV;
}