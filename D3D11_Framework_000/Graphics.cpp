
#include "Graphics.h"
#include "Framework.h"

#pragma comment( lib, "d3d11.lib" )

using namespace SKDX::Graphics;

Graphics::Graphics( const std::weak_ptr< SKDX::Framework::Window >& outputWindow ) : outputWindow( outputWindow )
{
	Initialize( outputWindow );
}

Graphics::~Graphics( )
{
	Dispose( );
}

bool Graphics::Initialize( const std::weak_ptr< SKDX::Framework::Window >& outputWindow )
{
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
	};
	
	int deviceCreationFlags = 0;
#ifdef _DEBUG
	deviceCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	auto window = outputWindow.lock( );
	int width	= window->GetClientWidth( );
	int height	= window->GetClientHeight( );
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.BufferCount							= 1;
	sd.BufferDesc.Width						= width;
	sd.BufferDesc.Height					= height;
	sd.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator		= 60;
	sd.BufferDesc.RefreshRate.Denominator	= 1;
	sd.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SampleDesc.Count						= 1;
	sd.SampleDesc.Quality					= 0;
	sd.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed								= true;
	sd.OutputWindow							= window->GetHandle( );

	auto hr = S_OK;
	for( auto dt : driverTypes ){
		description.driverType = dt;
		hr = D3D11CreateDeviceAndSwapChain( nullptr, dt, nullptr, deviceCreationFlags, featureLevels, ARRAYSIZE(featureLevels),
											D3D11_SDK_VERSION, &sd, &swapChain, &device, &description.featureLevel, &immediateContext );
		if( SUCCEEDED(hr) ) break;
	}
	if( FAILED(hr) ) return false;
	description.swapChianDesc = sd;

	Microsoft::WRL::ComPtr< ID3D11Texture2D > resource;
	swapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), (void**)&resource );
	hr = device->CreateRenderTargetView( resource.Get(), nullptr, &backBuffer );
	if( FAILED(hr) ) return false;

	if( !CreateDepthStencilView(width, height) ) return false;

	immediateContext->OMSetRenderTargets( 1, backBuffer.GetAddressOf(), depthStencilView.Get() );

	D3D11_VIEWPORT vp;
	vp.Width		= (float)window->GetClientWidth( );
	vp.Height		= (float)window->GetClientHeight( );
	vp.TopLeftX		= 0.0f;
	vp.TopLeftY		= 0.0f;
	vp.MinDepth		= 0.0f;
	vp.MaxDepth		= 1.0f;
	immediateContext->RSSetViewports( 1, &vp );

	return true;
}


bool Graphics::CreateDepthStencilView( int width, int height )
{
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory( &td, sizeof(td) );
	td.Width                = width;
	td.Height               = height;
	td.MipLevels            = 1;
	td.ArraySize            = 1;
	td.Format               = DXGI_FORMAT_D16_UNORM;
	td.SampleDesc.Count     = 1;
	td.SampleDesc.Quality   = 0;
	td.Usage                = D3D11_USAGE_DEFAULT;
	td.BindFlags            = D3D11_BIND_DEPTH_STENCIL;

	Microsoft::WRL::ComPtr< ID3D11Texture2D > dsTex = nullptr;
	device->CreateTexture2D( &td, nullptr, &dsTex );

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory( &dsvDesc, sizeof(dsvDesc) );
	dsvDesc.Format				= DXGI_FORMAT_D16_UNORM;
	dsvDesc.ViewDimension		= D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice	= 0;
	auto hr = device->CreateDepthStencilView( dsTex.Get(), &dsvDesc, &depthStencilView );

	return SUCCEEDED( hr );
}


void Graphics::Dispose( )
{
	backBuffer			= nullptr;
	depthStencilView	= nullptr;

	device				= nullptr;
	immediateContext	= nullptr;
	swapChain			= nullptr;
}

void Graphics::Clear( float clearColor[4] )
{
	immediateContext->ClearRenderTargetView( backBuffer.Get(), clearColor );
}

void Graphics::Clear( float r, float g, float b, float a )
{
	float clearColor[] = { r, g, b, a };
	immediateContext->ClearRenderTargetView( backBuffer.Get(), clearColor );
}

void Graphics::Present( )
{
	swapChain->Present( 0, 0 );
}

