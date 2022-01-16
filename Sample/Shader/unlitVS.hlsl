
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;
	wvp = mul(WorldMatrix, ViewMatrix);
	wvp = mul(wvp, ProjectionMatrix);

	Out.Diffuse = In.Diffuse;
	Out.Position = mul(In.Position, wvp);
	Out.Normal = mul(In.Normal, WorldMatrix);
	Out.UV = In.UV;
}