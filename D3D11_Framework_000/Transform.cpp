
#include "Transform.h"

using namespace SKDX;
using namespace SKDX::Math;

std::shared_ptr< Transform > Transform::Create( )
{
	std::shared_ptr< Transform > transform( new Transform() );
	return transform;
}

std::shared_ptr< Transform > Transform::Create( const Vector3& pos, const Quaternion& rot, const Vector3& size )
{
	std::shared_ptr< Transform > transform( new Transform(pos, rot, size) );
	return transform;
}

Transform::Transform( )
{
	position	= Vector3::Zero;
	rotation	= Quaternion::Identity;
	size		= Vector3( 1, 1, 1 );

	mtxTranslation	= Matrix4x4::CreateTranslation( position );
	mtxRotation		= Matrix4x4::CreateRotation( rotation );
	mtxScaling		= Matrix4x4::CreateScaling( size );
	matrix			= mtxScaling * mtxRotation * mtxTranslation;
}

Transform::Transform( const Vector3& pos, const Quaternion& rot, const Vector3& size )
{
	this->position	= pos;
	this->rotation	= rot;
	this->size		= size;

	mtxTranslation	= Matrix4x4::CreateTranslation( position );
	mtxRotation		= Matrix4x4::CreateRotation( rotation );
	mtxScaling		= Matrix4x4::CreateScaling( size );
	matrix			= mtxScaling * mtxRotation * mtxTranslation;
}

void Transform::SetParent( const std::shared_ptr< Transform >& transform )
{
	if( !parent.expired() ){
		parent.swap( std::weak_ptr<Transform>(transform) );
	}else{
		parent = transform;
	}
}

void Transform::SetPosition( const Vector3& pos )
{
	position = pos;
}

void Transform::SetPosition( float x, float y, float z )
{
	position = Vector3( x, y, z );
}

void Transform::SetRotation( const Quaternion& rot )
{
	rotation = rot;
}

void Transform::SetRotation( const Vector3& axis, float angle )
{
	rotation = Quaternion::CreateRotation( axis, angle );
}


