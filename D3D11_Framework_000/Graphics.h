
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

		const std::weak_ptr< Framework::Window >& GetOutputWindow( ) const { return outputWindow; }
		const Description& GetDescription( ) const { return description; }
	private:
		Graphics( Graphics& ) = delete;
		Graphics& operator =( Graphics& ) = delete;
		std::weak_ptr< Framework::Window > outputWindow;

		Microsoft::WRL::ComPtr< ID3D11Device >				device;
		Microsoft::WRL::ComPtr< ID3D11DeviceContext >		immediateContext;
		Microsoft::WRL::ComPtr< IDXGISwapChain >				swapChain;
		Microsoft::WRL::ComPtr< ID3D11RenderTargetView>		backBuffer;

		Description description;

	};

	interface IDrawable {
		virtual void Draw( ) = 0;
	};

	class RenderObject abstract : IDrawable {
	public:
		const std::shared_ptr< SKDX::Transform > GetTransform( ) const; 
		virtual void Draw( ) = 0;
	protected:
		std::shared_ptr< SKDX::Transform > transform;
	private:
	};
};
};
