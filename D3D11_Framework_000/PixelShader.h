
#pragma once

#include <string>
#include <memory>
#include <wrl/client.h>
#include "Math.h"

struct ID3D11PixelShader;
struct ID3D11Buffer;
struct ID3D11SamplerState;

namespace SKDX {
	namespace Graphics {
		class Graphics;
	};

	class PixelShader {
	public:
		struct Materials {
		};

	public:
		static std::shared_ptr< PixelShader > LoadFromFile( const std::shared_ptr< Graphics::Graphics >& graphics, const wchar_t* filepath, const char* entryPoint="ps_main", const char* profile="ps_5_0" );
		virtual ~PixelShader( );

		virtual void Dispose( );

		virtual void Bind( );

	protected:
		PixelShader( const std::shared_ptr< Graphics::Graphics >& graphics );

		virtual bool Initialize( const wchar_t* filepath, const char* entryPoint, const char* profile );
		
		std::weak_ptr< Graphics::Graphics > graphics;

		Microsoft::WRL::ComPtr< ID3D11PixelShader >		shader;
		Microsoft::WRL::ComPtr< ID3D11Buffer >			constantBuffer;
		Microsoft::WRL::ComPtr< ID3D11SamplerState >	samplerState;
		std::wstring name;
	};
};
