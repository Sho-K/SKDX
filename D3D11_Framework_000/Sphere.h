
#pragma once

#include "RenderObject.h"
#include <wrl/client.h>

struct ID3D11Buffer;

namespace SKDX {
	namespace Graphics {
		class Graphics;
		namespace Geometries {
			class Sphere : public SKDX::Graphics::RenderObject {
			public:
				~Sphere( );
				static std::shared_ptr< Sphere > Create( const std::shared_ptr< Graphics >& graphics, float radius );

				void Draw( ) override;
				
			private:
				Sphere( std::shared_ptr< Graphics >& graphics );
				Sphere( Sphere& ) = delete;
				Sphere& operator =( Sphere& ) = delete;

				void InitPositions( );
				void InitNormals( );
				void InitTexCoords( );

				std::unique_ptr< Math::Vector3 > positions;
				std::unique_ptr< Math::Vector3 > normals;
				std::unique_ptr< Math::Vector2 > texCoords;
				Microsoft::WRL::ComPtr< ID3D11Buffer > vertexBuffer;
			};
		};
	};
};

