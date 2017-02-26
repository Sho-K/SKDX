
#pragma once

#include <d3d11.h>
#include <memory>
#include <wrl/client.h>


namespace SKDX{

	class Transform;

	namespace Framework{
		class Window;
	};


namespace Graphics{

	class Graphics {
	public:
		struct Description {
			D3D_DRIVER_TYPE		driverType;
			D3D_FEATURE_LEVEL		featureLevel;
			DXGI_SWAP_CHAIN_DESC	swapChianDesc;
		};

	public:
		Graphics( const std::weak_ptr< Framework::Window >& outputWindow );
		~Graphics( );

		void Clear( float clearColor[4] );
		void Clear( float r, float g, float b, float a );
		void Present( );

		bool Initialize( const std::weak_ptr< Framework::Window >& outputWindow  );
		void Dispose( );

		void SetVertexShader( const Microsoft::WRL::ComPtr< ID3D11VertexShader >& shader );

		const std::weak_ptr< Framework::Window >& GetOutputWindow( ) const { return outputWindow; }
		const Description& GetDescription( ) const { return description; }

		Microsoft::WRL::ComPtr< ID3D11Device > GetDevice( ) const { return device; }
		Microsoft::WRL::ComPtr< ID3D11DeviceContext > GetContext( ) const { return immediateContext; }
	private:
		Graphics( Graphics& ) = delete;
		Graphics& operator =( Graphics& ) = delete;
		std::weak_ptr< Framework::Window > outputWindow;

		bool CreateDepthStencilView( int width, int height );

		Microsoft::WRL::ComPtr< ID3D11Device >				device;
		Microsoft::WRL::ComPtr< ID3D11DeviceContext >		immediateContext;
		Microsoft::WRL::ComPtr< IDXGISwapChain >				swapChain;
		Microsoft::WRL::ComPtr< ID3D11RenderTargetView>		backBuffer;
		Microsoft::WRL::ComPtr< ID3D11DepthStencilView >	depthStencilView;
		Microsoft::WRL::ComPtr< ID3D11RasterizerState >		rasterizerState;

		Description description;

	};
};
};
