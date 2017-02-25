
float4 vs_main( float4 position : POSITION ) : SV_Position
{
	return position;
}

float4 ps_main( float2 texCoord : TEXCOORD0 ) : SV_Target
{
	return 1.0f;
}
