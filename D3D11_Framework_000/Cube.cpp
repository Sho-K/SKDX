
#include "Cube.h"
#include "Graphics.h"


using namespace SKDX::Graphics::Geometries;

Cube::Cube( const std::shared_ptr< Graphics >& graphics ) : RenderObject( graphics )
{
}

bool Cube::Initialize( const Math::Vector3& size )
{
	Dispose( );

	vertices = std::shared_ptr< Math::Vector3 >( new Math::Vector3[8], []( Math::Vector3* ){ delete[] p; } );
}
