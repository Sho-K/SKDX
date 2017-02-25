
#include "VertexShader.h"
#include "Graphics.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment( lib, "d3dcompiler.lib" )


using namespace SKDX;

std::shared_ptr< VertexShader > VertexShader::LoadFromFile( const std::shared_ptr< SKDX::Graphics::Graphics >& graphics, const wchar_t* filepath, const char* entryPoint, const char* profile )
{
	std::shared_ptr< VertexShader > vs( new VertexShader(graphics) );
	vs->Initialize( filepath, entryPoint, profile );
	return vs;
}

VertexShader::VertexShader( const std::shared_ptr< Graphics::Graphics >& graphics ) : graphics( graphics )
{
}

VertexShader::~VertexShader( )
{
	Dispose( );
}

bool VertexShader::Initialize( const wchar_t* filepath, const char* entryPoint, const char* profile )
{
	Dispose( );

	name = filepath;
	Microsoft::WRL::ComPtr< ID3DBlob > code = nullptr;
	Microsoft::WRL::ComPtr< ID3DBlob > error = nullptr;
	auto hr = D3DCompileFromFile( filepath, nullptr, nullptr, entryPoint, profile, 0, 0, &code, &error );
	if( FAILED(hr) ){
		auto errmsg = []( const char* msg ) { MessageBox( nullptr, msg, "Error", MB_OK | MB_ICONEXCLAMATION ); };
		if( error.Get() == nullptr ){
			errmsg( "failed to compile vertex shader" );
		}else{
			errmsg( (const char*)error->GetBufferPointer() );
		}
		return false;
	}
	auto device = graphics.lock( )->GetDevice( );
	device->CreateVertexShader( (const void*)code->GetBufferPointer(), code->GetBufferSize(), nullptr, &shader );

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,	0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	device->CreateInputLayout( layout, ARRAYSIZE(layout), (const void*)code->GetBufferPointer(), code->GetBufferSize(), &inputLayout );


	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage		= D3D11_USAGE_DEFAULT;
	bd.ByteWidth	= sizeof( Matrices );
	bd.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;
	device->CreateBuffer( &bd, nullptr, &constantBuffer );

	return true;
}

void VertexShader::Dispose( )
{
	name			= L"";

	shader			= nullptr;
	inputLayout		= nullptr;
	constantBuffer	= nullptr;
}

void VertexShader::Bind( )
{
	auto g = graphics.lock( );
	auto immediateContext = graphics.lock( )->GetContext( );

	immediateContext->VSSetShader( shader.Get(), nullptr, 0 );
	immediateContext->IASetInputLayout( inputLayout.Get() );
	immediateContext->UpdateSubresource( constantBuffer.Get(), 0, nullptr, &matrices, 0, 0 );
	immediateContext->VSSetConstantBuffers( 0, 1, constantBuffer.GetAddressOf() );
}