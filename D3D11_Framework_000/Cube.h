
#pragma once 


#include "RenderObject.h"
#include "Math.h"

#include <wrl/client.h>

struct ID3D11Buffer;

namespace SKDX {
namespace Graphics{
	namespace Geometries{
		class Cube : public SKDX::Graphics::RenderObject{
		public:
			static std::shared_ptr< Cube > Create( const std::shared_ptr< Graphics >& graphics, const Math::Vector3& size = Math::Vector3(1,1,1) );
			virtual ~Cube( );

			bool Initialize( const Math::Vector3& size );
			void Dispose( ) override;

			void Draw( ) override;
		private:
			Cube( const std::shared_ptr< Graphics >& graphics );
			Cube( Cube& ) = delete;
			Cube& operator =( Cube& ) = delete;

			void InitPositions( );
			void InitNormals( );
			void InitTexCoords( );

			Math::Vector3							size;				//	size of cube( x, y, z )
			std::unique_ptr< Math::Vector3[] >	positions;			//	position data array;
			std::unique_ptr< Math::Vector3[] >	normals;			//	normal data array
			std::unique_ptr< Math::Vector2[] >	texCoords;			//	texture coordinate data array

			Microsoft::WRL::ComPtr< ID3D11Buffer > vertexBuffer;
		};
	};
};
};

