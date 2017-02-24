
#include "Quaternion.h"
#include "Vector.h"
#include <math.h>

using namespace SKDX::Math;

const Quaternion Quaternion::Identity = Quaternion( 0, 0, 0, 1 );

Quaternion::Quaternion( ) : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 1.0f )
{
}

Quaternion::Quaternion( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w( w )
{
}

Quaternion::Quaternion( const Vector3& v, float w ) : x( v.x ), y( v.y ), z( v.z ), w( w )
{
}

float Quaternion::Length( ) const
{
	return sqrtf( x*x + y*y + z*z + w*w );
}

void Quaternion::Normalize( ) 
{
	*this = *this / Length( );
}

Quaternion Quaternion::GetNormalized( ) const
{
	return *this / Length( );
}

void Quaternion::Rotate( const Vector3& axis, float angle )
{
	float w = angle * 0.5f;
	float sine = sinf( angle );
	x = axis.x * sine;
	y = axis.y * sine;
	z = axis.z * sine;
	w = cosf( angle );
}

void Quaternion::Rotate( float yaw, float pitch, float roll )
{
	auto yawing		= CreateRotation( Vector3::Up, yaw );
	auto pitching	= CreateRotation( Vector3::Right, pitch );
	auto rolling	= CreateRotation( Vector3::Forward, roll );
	*this = rolling * pitching * yawing;
}

void Quaternion::Rotate( const Vector3& eulerAngles )
{
	Rotate( eulerAngles.y, eulerAngles.x, eulerAngles.z );
}

Quaternion Quaternion::CreateRotation( const Vector3& axis, float angle )
{
	float ang = angle * 0.5f;
	float sine = sinf( ang );
	auto x = axis.x * sine;
	auto y = axis.y * sine;
	auto z = axis.z * sine;
	auto w = cosf( ang );
	return Quaternion( x, y, z, w );
}

Quaternion Quaternion::CreateRotation( float yaw, float pitch, float roll )
{
	auto yawing		= CreateRotation( Vector3::Up, yaw );
	auto pitching	= CreateRotation( Vector3::Right, pitch );
	auto rolling	= CreateRotation( Vector3::Forward, roll );
	return rolling * pitching * yawing;
}

Quaternion Quaternion::CreateRotation( const Vector3& eulerAngles )
{
	return CreateRotation( eulerAngles.y, eulerAngles.x, eulerAngles.z );
}


Vector3 Quaternion::Transform( const Vector3& v )
{
	Quaternion p( v.x, v.y, v.z, 0.0f );
	Quaternion q = *this;
	Quaternion r( -x, -y, -z, w );
	auto result = q * p * r;
	return Vector3( result.x, result.y, result.z );
}

Quaternion Quaternion::Slerp( const Quaternion& from, const Quaternion& to, float t )
{
	Quaternion out;

	auto qr = from.x*to.x + from.y*to.y + from.z*to.z + from.w*to.w;
	auto ss = 1.0f - qr*qr;
	auto sp = sqrtf( ss );
	if( ss <= 0.0f || sp == 0.0f ){
		out = from;	
	}else{
		auto ph = acosf( qr );
		auto pt = ph * t;
		auto t0 = sinf( ph - pt ) / sp;
		auto t1 = sinf( pt ) / sp;

		out.x = from.x * t0 + to.x * t1;
		out.y = from.y * t0 + to.y * t1;
		out.z = from.z * t0 + to.z * t1;
		out.w = from.w * t0 + to.w * t1;
	}
	return out;
}

Quaternion Quaternion::operator +( const Quaternion& q ) const
{
	return Quaternion( x+q.x, y+q.y, z+q.z, w+q.w );
}

Quaternion Quaternion::operator -( const Quaternion& q ) const 
{
	return Quaternion( x-q.x, y-q.y, z-q.z, w-q.w );
}

Quaternion Quaternion::operator *( float f ) const
{
	return Quaternion( x*f, y*f, z*f, z*f );
}

Quaternion Quaternion::operator /( float f ) const
{
	auto inv = 1.0f / f;
	return Quaternion( x*f, y*f, z*f, z*f );
}

Quaternion Quaternion::operator *( const Quaternion& quat ) const
{	
	//	D3DXQUATERNION ‚Æ“¯‚¶‚æ‚¤‚Éˆµ‚¤‚½‚ß‚É¶‰E‚ð‹t“]
	auto left	= quat;
	auto right	= *this;
	auto V = Vector3( left.x, left.y, left.z );
	auto W = Vector3( right.x, right.y, right.z );
	auto q = left.w;
	auto r = right.w;
	
	auto outW = q*r - Vector3::Dot( V, W );
	auto outVec = W*q + V*r + Vector3::Cross( V, W );
	return Quaternion( outVec, outW );
}


Quaternion& Quaternion::operator *=( const Quaternion& q )
{
	*this = *this * q;
	return *this;
}

