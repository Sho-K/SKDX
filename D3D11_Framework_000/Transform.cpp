
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

	forward		= Vector3::Forward;
	right		= Vector3::Right;
	up			= Vector3::Up;

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

Transform::~Transform( )
{
}

void Transform::Update( )
{
	matrix = mtxScaling * mtxRotation * mtxTranslation;
}

const Vector3& Transform::GetForward( ) const
{
	return matrix.TransformNormal( Vector3::Forward );
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
	mtxTranslation = Matrix4x4::CreateTranslation( position );
}

void Transform::SetPosition( float x, float y, float z )
{
	position = Vector3( x, y, z );
	mtxTranslation = Matrix4x4::CreateTranslation( position );
}

void Transform::SetRotation( const Quaternion& rot )
{
	rotation = rot;
	mtxRotation = Matrix4x4::CreateRotation( rotation );
}

void Transform::SetRotation( const Vector3& axis, float angle )
{
	rotation = Quaternion::CreateRotation( axis, angle );
	mtxRotation = Matrix4x4::CreateRotation( rotation );
}

void Transform::SetRotation( const Vector3& eularAngles )
{
	rotation = Quaternion::CreateRotation( eularAngles.y, eularAngles.x, eularAngles.z );
	mtxRotation = Matrix4x4::CreateRotation( rotation );
}

void Transform::SetRotation( float yaw, float pitch, float roll )
{
	rotation = Quaternion::CreateRotation( yaw, pitch, roll );
	mtxRotation = Matrix4x4::CreateRotation( rotation );
}

void Transform::SetSize( const Vector3& size )
{
	this->size = size;
	mtxScaling = Matrix4x4::CreateScaling( size );
}

void Transform::SetSize( float x, float y, float z )
{
	this->size = Vector3( x, y, z );
	mtxScaling = Matrix4x4::CreateScaling( size );
}

void Transform::SetSize( float size )
{
	this->size = Vector3( size, size, size );
	mtxScaling = Matrix4x4::CreateScaling( size );
}


void Transform::Translate( const Vector3& translation )
{
	position += translation;
	mtxTranslation = Matrix4x4::CreateTranslation( position );
}

void Transform::Translate( float x, float y, float z )
{
	position += Vector3( x, y, z );
	mtxTranslation = Matrix4x4::CreateTranslation( position );
}

void Transform::Rotate( const Quaternion& rot )
{
	rotation *= rot;
	mtxRotation = Matrix4x4::CreateRotation( rotation );
}

void Transform::Rotate( const Vector3& axis, float angle )
{
	auto rot = Quaternion::CreateRotation( axis, angle );
	rotation *= rot;
	mtxRotation = Matrix4x4::CreateRotation( rotation );
}

void Transform::Rotate( const Vector3& eularAngles )
{
	auto rot = Quaternion::CreateRotation( eularAngles );
	rotation *= rot;
	mtxRotation = Matrix4x4::CreateRotation( rotation );
}

void Transform::Rotate( float yaw, float pitch, float roll )
{
	auto rot = Quaternion::CreateRotation( yaw, pitch, roll );
	rotation *= rot;
	mtxRotation = Matrix4x4::CreateRotation( rotation );
}
