
struct VS_OUT {
	float4 position : SV_Position;
	float4 color	: COLOR0;
	float2 texCoord : TEXCOORD0;
};

cbuffer Matrices : register( b0 ) {
	matrix world;
	matrix view;
	matrix proj;
};

VS_OUT vs_main( float4 position : POSITION, float3 normal : NORMAL, float2 texCoord : TEXCOORD0 )
{
	VS_OUT output = (VS_OUT)0;
	output.position = position;
	output.position = mul( output.position, world );
	output.position = mul( output.position, view );
	output.position = mul( output.position, proj );

	float3 lightDir = normalize( float3(0.5f, -0.5f, 1.0f) );
	float3 N = mul( float4(normal,0.0f), world ).xyz;
	output.color	= max( 0.0f, dot(N, -lightDir) );

	output.texCoord = 0;

	return output;
}

float4 ps_main( VS_OUT input ) : SV_Target
{
	return input.color;
}
