
#include "PixelShader.h"
#include "Graphics.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment( lib, "d3dcompiler.lib" )

using namespace SKDX;

std::shared_ptr< PixelShader > PixelShader::Create( const std::shared_ptr< Graphics::Graphics >& graphics, const wchar_t* filepath, const char* entryPoint, const char* profile )
{
	std::shared_ptr< PixelShader > ps( new PixelShader(graphics) );
	ps->Initialize( filepath, entryPoint, profile );
	return ps;
}

PixelShader::PixelShader( const std::shared_ptr< Graphics::Graphics >& graphics ) : graphics( graphics )
{
}

PixelShader::~PixelShader( )
{
	Dispose( );
}

bool PixelShader::Initialize( const wchar_t* filepath, const char* entryPoint, const char* profile )
{
	Dispose( );
	name = filepath;

	Microsoft::WRL::ComPtr< ID3DBlob > code;
	Microsoft::WRL::ComPtr< ID3DBlob > error;
	auto hr = D3DCompileFromFile( filepath, nullptr, nullptr, entryPoint, profile, 0, 0, &code, &error );
	if( FAILED(hr) ){
		auto errmsg = []( const char* msg ) { MessageBox( nullptr, msg, "Error", MB_OK | MB_ICONEXCLAMATION ); };

		if( error.Get() == nullptr ) {
			errmsg( "Failed to compile pixel shader" );
		}else{
			errmsg( (const char*)error->GetBufferPointer() );
		}
		return false;
	}
	auto device = graphics.lock( )->GetDevice( );
	device->CreatePixelShader( (const void*)code->GetBufferPointer(), code->GetBufferSize(), nullptr, &shader );

	D3D11_SAMPLER_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.Filter					= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU					= D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV					= D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW					= D3D11_TEXTURE_ADDRESS_WRAP;
	sd.ComparisonFunc			= D3D11_COMPARISON_NEVER;
	sd.MinLOD					= 0.0f;
	sd.MaxLOD					= D3D11_FLOAT32_MAX;
	device->CreateSamplerState( &sd, &samplerState );

	return true;
}

void PixelShader::Dispose( )
{
	name			= L"";

	shader			= nullptr;
	constantBuffer	= nullptr;
}

void PixelShader::Bind( )
{
	auto immediateContext = graphics.lock( )->GetContext( );

	immediateContext->PSSetShader( shader.Get(), nullptr, 0 );
	immediateContext->PSSetSamplers( 0, 1, samplerState.GetAddressOf() );
}
