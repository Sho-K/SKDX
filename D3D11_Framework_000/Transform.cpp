
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
	return forward;
}

const Vector3& Transform::GetBackward( ) const
{
	return -forward;
}

const Vector3& Transform::GetRight( ) const
{
	return right;
}

const Vector3& Transform::GetLeft( ) const
{
	return -right;
}

const Vector3& Transform::GetUpward( ) const
{
	return up;
}

const Vector3& Transform::GetDownward( ) const
{
	return -up;
}

void Transform::SetParent( const std::shared_ptr< Transform >& transform )
{
	if( !parent.expired() ){
		parent.swap( std::weak_ptr<Transform>(transform) );
	}else{
		parent = transform;
	}
}

//	Translation
void Transform::SetPosition( const Vector3& pos )
{
	position = pos;
	UpdateTranslationMatrix( );
}

void Transform::SetPosition( float x, float y, float z )
{
	position = Vector3( x, y, z );
	UpdateTranslationMatrix( );
}

void Transform::Translate( const Vector3& translation )
{
	position += translation;
	UpdateTranslationMatrix( );
}

void Transform::Translate( float x, float y, float z )
{
	position += Vector3( x, y, z );
	UpdateTranslationMatrix( );
}



//	Rotation
void Transform::SetRotation( const Quaternion& rot )
{
	rotation = rot;
	UpdateRotationMatrix( );
}

void Transform::SetRotation( const Vector3& axis, float angle )
{
	rotation = Quaternion::CreateRotation( axis, angle );
	UpdateRotationMatrix( );
}

void Transform::SetRotation( const Vector3& eularAngles )
{
	rotation = Quaternion::CreateRotation( eularAngles.y, eularAngles.x, eularAngles.z );
	UpdateRotationMatrix( );
}

void Transform::SetRotation( float yaw, float pitch, float roll )
{
	rotation = Quaternion::CreateRotation( yaw, pitch, roll );
	UpdateRotationMatrix( );
}

void Transform::Rotate( const Quaternion& rot )
{
	rotation *= rot;
	UpdateRotationMatrix( );
}

void Transform::Rotate( const Vector3& axis, float angle )
{
	auto rot = Quaternion::CreateRotation( axis, angle );
	rotation *= rot;
	UpdateRotationMatrix( );
}

void Transform::Rotate( const Vector3& eularAngles )
{
	auto rot = Quaternion::CreateRotation( eularAngles );
	rotation *= rot;
	UpdateRotationMatrix( );
}

void Transform::Rotate( float yaw, float pitch, float roll )
{
	auto rot = Quaternion::CreateRotation( yaw, pitch, roll );
	rotation *= rot;
	UpdateRotationMatrix( );
}

//	Sclaing
void Transform::SetSize( const Vector3& size )
{
	this->size = size;
	UpdateScalingMatrix( );
}

void Transform::SetSize( float x, float y, float z )
{
	this->size = Vector3( x, y, z );
	UpdateScalingMatrix( );
}

void Transform::SetSize( float size )
{
	this->size = Vector3( size, size, size );
	UpdateScalingMatrix( );
}



void Transform::UpdateTranslationMatrix( )
{
	mtxTranslation = Matrix4x4::CreateTranslation( position );
}

void Transform::UpdateRotationMatrix( )
{
	mtxRotation = Matrix4x4::CreateRotation( rotation );

	forward		= Vector3( mtxRotation._11, mtxRotation._21, mtxRotation._31 ).GetNormalized( );
	right		= Vector3( mtxRotation._12, mtxRotation._22, mtxRotation._32 ).GetNormalized( );
	up			= Vector3( mtxRotation._31, mtxRotation._32, mtxRotation._33 ).GetNormalized( );
}

void Transform::UpdateScalingMatrix( )
{
	mtxScaling = Matrix4x4::CreateScaling( size );
}
