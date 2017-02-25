
struct VS_OUT {
	float4 position : SV_Position;
	float3 normal	: NORMAL;
	float2 texCoord : TEXCOORD0;
};

VS_OUT vs_main( float4 position : POSITION )
{
	VS_OUT output = (VS_OUT)0;
	output.position = position;
	output.normal = 0;
	output.texCoord = 0;

	return output;
}

float4 ps_main( float2 texCoord : TEXCOORD0 ) : SV_Target
{
	return 1.0f;
}
