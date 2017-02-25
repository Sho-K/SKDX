
struct VS_OUT {
	float4 position : SV_Position;
	float2 texCoord : TEXCOORD0;
};

cbuffer Matrices : register( b0 ) {
	matrix world;
	matrix view;
	matrix proj;
};

VS_OUT vs_main( float4 position : POSITION, float3 normal : NORMAL )
{
	VS_OUT output = (VS_OUT)0;
	output.position = position;
	output.position = mul( output.position, world );
	output.position = mul( output.position, view );
	output.position = mul( output.position, proj );

	output.texCoord = 0;

	return output;
}

float4 ps_main( VS_OUT input ) : SV_Target
{
	return 1.0f;
}
