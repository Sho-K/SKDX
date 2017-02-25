
#pragma once

#include <string>
#include <wrl/client.h>
#include <memory>

#include "Math.h"

struct ID3D11VertexShader;
struct ID3D11InputLayout;
struct ID3D11Buffer;

namespace SKDX{
	namespace Graphics {
		class Graphics;
	};

	class VertexShader {
	public:
		struct Vertex {
			Math::Vector3 position;
			Math::Vector3 normal;
			Math::Vector2 texCoords;
		};

		struct Matrices {
			Math::Matrix4x4 world;
			Math::Matrix4x4 view;
			Math::Matrix4x4 projection;
		};

	public:
		static std::shared_ptr< VertexShader > Create( const std::shared_ptr< Graphics::Graphics >& graphics, const wchar_t* filepath, const char* entryPoint="vs_main", const char* profile="vs_5_0" );
		virtual ~VertexShader( );
		
		virtual bool Initialize( const wchar_t* filepath, const char* entryPoint, const char* profile );
		virtual void Dispose( );

		virtual void Bind( );
		void SetMatrices( const Matrices& matrices ) { this->matrices = matrices; }

	protected:
		VertexShader( const std::shared_ptr< Graphics::Graphics >& graphics );

		std::weak_ptr< Graphics::Graphics > graphics;

		Microsoft::WRL::ComPtr< ID3D11VertexShader >	shader;
		Microsoft::WRL::ComPtr< ID3D11InputLayout >		inputLayout;
		Microsoft::WRL::ComPtr< ID3D11Buffer >			constantBuffer;
		
		std::wstring name;

	private:
		VertexShader( VertexShader& ) = delete;
		VertexShader& operator =( VertexShader& ) = delete;

		Matrices matrices;
	};
};
