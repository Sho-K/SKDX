
#include "RenderObject.h"
#include "Transform.h"

using namespace SKDX::Graphics;

RenderObject::RenderObject( const std::shared_ptr< Graphics >& g )
{
	graphics = std::weak_ptr< Graphics >( g );
	transform = SKDX::Transform::Create( );
}

RenderObject::~RenderObject( )
{
	Dispose( );
}


