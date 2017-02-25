
#pragma once 


#include "RenderObject.h"
#include "Math.h"

namespace SKDX {
namespace Graphics{
	namespace Geometries{
		class Cube : SKDX::Graphics::RenderObject{
		public:
			static std::shared_ptr< Cube > Create( const Math::Vector3& size = Math::Vector3(1,1,1) );
			virtual ~Cube( );

			bool Initialize( const Math::Vector3& size );
			void Dispose( ) override;

		private:
			Cube( const std::shared_ptr< Graphics >& graphics );
			Cube( Cube& ) = delete;
			Cube& operator =( Cube& ) = delete;

			std::shared_ptr< Math::Vector3 > verteces;
			std::shared_ptr< Math::Vector3 > normals;
			std::shared_ptr< Math::Vector2 > texCoord;
		};
	};
};
};

