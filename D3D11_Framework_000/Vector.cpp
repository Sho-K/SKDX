
#include "Vector.h"
#include <math.h>

using namespace SKDX::Math;

/*
	Vector3 
*/
const Vector3 Vector3::Zero( 0, 0, 0 );
const Vector3 Vector3::Forward( 0, 0, 1 );
const Vector3 Vector3::Backward( 0, 0, -1 );
const Vector3 Vector3::Up( 0, 1, 0 );
const Vector3 Vector3::Down( 0, -1, 0 );
const Vector3 Vector3::Right( 1, 0, 0 );
const Vector3 Vector3::Left( -1, 0, 0 );

Vector3::Vector3( ) : x( 0.0f ), y( 0.0f ), z( 0.0f )
{
}

Vector3::Vector3( float f ) : x( f ), y( f ), z( f )
{
}

Vector3::Vector3( float x, float y, float z ) : x( x ), y( y ), z( z )
{
}

Vector3::Vector3( const Vector2& v ) : x( v.x ), y( v.y ), z( 0.0f )
{
}


/*	 Member functions	*/
float Vector3::Length( ) const
{
	return sqrtf( x*x + y*y + z*z );
}

Vector3 Vector3::GetNormalized( ) const
{
	return *this / Length( );
}

void Vector3::Normalize( )
{
	auto v = *this;
	*this = v / Length( );
}

float Vector3::Dot( const Vector3& v ) const
{
	return x*v.x + y*v.y + z*v.z;
}

Vector3 Vector3::Cross( const Vector3& v ) const
{
	auto x = y*v.z - z*v.y;
	auto y = z*v.x - x*v.z;
	auto z = x*v.y - y*v.x;
	return Vector3( x, y, z );
}

/*		static functions		*/
float Vector3::Length( const Vector3& v )
{
	return v.Length( );
}

const Vector3 Vector3::Normalize( const Vector3& v )
{
	return v.GetNormalized( );
}

float Vector3::Dot( const Vector3& v0, const Vector3& v1 )
{
	return v0.Dot( v1 );
}

const Vector3 Vector3::Cross( const Vector3& v0, const Vector3& v1 )
{
	auto x = v0.y*v1.z - v0.z*v1.y;
	auto y = v0.z*v1.x - v0.x*v1.z;
	auto z = v0.x*v1.y - v0.y*v1.x;

	return Vector3( x, y, z );
}

Vector3 Vector3::Lerp( const Vector3& from, const Vector3& to, float t )
{
	return (to-from)*t + from;
}

/*		operators	*/
Vector3 Vector3::operator +( const Vector3& v ) const
{
	return Vector3( x+v.x, y+v.y, z+v.z );
}

Vector3 Vector3::operator -( const Vector3& v ) const
{
	return Vector3( x-v.x, y-v.y, z-v.z );
}

Vector3 Vector3::operator *( float f ) const 
{
	return Vector3( x*f, y*f, z*f );
}

Vector3 Vector3::operator /( float f ) const
{
	auto inv = 1.0f / f;
	return *this * inv;
}

Vector3& Vector3::operator =( float f )
{
	x = y = z = f;
	return *this;
}

Vector3& Vector3::operator =( const Vector2& v )
{
	x = v.x;
	y = v.y;
	return *this;
}


Vector3& Vector3::operator +=( const Vector3& v )
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator -=( const Vector3& v )
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3& Vector3::operator *=( float f )
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

Vector3& Vector3::operator /=( float f )
{
	auto inv = 1.0f / f;
	x *= inv;
	y *= inv;
	z *= inv;
	return *this;
}

bool Vector3::operator ==( const Vector3& v ) const
{
	return ( x == v.x ) && ( y == v.y ) && ( z == v.z );
}

bool Vector3::operator !=( const Vector3& v ) const
{
	return !( *this == v );
}

Vector3 Vector3::operator -( ) const
{
	return Vector3( -x, -y, -z );
}


/*
	Vector2
*/

const Vector2 Vector2::Zero		= Vector2( 0.0f, 0.0f );
const Vector2 Vector2::Up		= Vector2( 0.0f, 1.0f );
const Vector2 Vector2::Down		= Vector2( 0.0f, -1.0f );
const Vector2 Vector2::Right	= Vector2( 1.0f, 0.0f );
const Vector2 Vector2::Left		= Vector2( -1.0f, 0.0f );

Vector2::Vector2( ) : x( 0.0f ), y( 0.0f )
{
}

Vector2::Vector2( float x, float y ) : x( x ), y( y )
{
}

Vector2::Vector2( float f ) : x( f ), y( f )
{
}

/*		member functions		*/
float Vector2::Length( ) const 
{
	return sqrtf( x*x + y*y );	
}

void Vector2::Normalize( )
{
	*this /= Length( );
}

Vector2 Vector2::GetNormalized( ) const 
{
	return *this / Length( );
}

float Vector2::Dot( const Vector2& v ) const
{
	return x*v.x + y*v.y;
}

float Vector2::Cross( const Vector2& v ) const
{
	return x*v.y - y*v.x;
}


/*		static functions		*/
float Vector2::Length( const Vector2& v )
{
	return sqrtf( v.x*v.x + v.y*v.y );
}

Vector2 Vector2::Normalize( const Vector2& v )
{
	return v.GetNormalized( );
}

float Vector2::Dot( const Vector2& v0, const Vector2& v1 )
{
	return v0.x*v1.x + v0.y*v1.y;
}

float Vector2::Cross( const Vector2& v0, const Vector2& v1 )
{
	return v0.x*v1.y - v0.y*v1.x;
}


/*		operators		*/
Vector2 Vector2::operator +( const Vector2& v ) const 
{
	return Vector2( x+v.x, y*v.y );
}

Vector2 Vector2::operator -( const Vector2& v ) const 
{
	return Vector2( x-v.x, y-v.y );
}

Vector2 Vector2::operator *( float f ) const 
{
	return Vector2( x*f, y*f );
}

Vector2 Vector2::operator /( float f ) const
{
	auto inv = 1.0f / f;
	return Vector2( x*inv, y*inv );
}

Vector2& Vector2::operator =( float f ) 
{
	x = y = f;
	return *this;
}

Vector2& Vector2::operator =( const Vector3& v )
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2& Vector2::operator +=( const Vector2& v )
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator -=( const Vector2& v )
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator *=( float f )
{
	x *= f;
	y *= f;
	return *this;
}

Vector2& Vector2::operator /=( float f )
{
	auto inv = 1.0f / f;
	x *= inv;
	y *= inv;
	return *this;
}

bool Vector2::operator ==( const Vector2& v ) const
{
	return ( x == v.x ) && ( y == v.y );
}

bool Vector2::operator !=( const Vector2& v ) const
{
	return !( *this == v );
}

Vector2 Vector2::operator -( ) const
{
	return Vector2( -x, -y );
}


/*		Vector4			*/
Vector4::Vector4( float x, float y, float z, float w )	: x( x ), y( y ), z( z ), w( w )
{
}

Vector4::Vector4( const Vector3& v, float w ) : x( v.x ), y( v.y ), z( v.z ), w( w )
{
}

Vector4::Vector4( const Vector2& v, float z, float w ) : x( v.x ), y( v.y ), z( z ), w( w )
{
}

float Vector4::Length( ) const 
{
	return sqrtf( (x*x) + (y*y) + (z*z) + (w*w) );
}

float Vector4::Length( const Vector4& v )
{
	return v.Length( );
}

void Vector4::Normalize( )
{
	*this /= Length( );
}

Vector4 Vector4::GetNormalize( ) const 
{
	return *this / Length( );
}

Vector4 Vector4::Normalize( const Vector4& v ) 
{
	return v.GetNormalize( );
}

Vector4 Vector4::operator +( const Vector4& v ) const
{
	return Vector4( x+v.x, y+v.y, z+v.z, w+v.w );
}

Vector4 Vector4::operator -( const Vector4& v ) const
{
	return Vector4( x-v.x, y-v.y, z-v.z, w-v.w );
}

Vector4 Vector4::operator *( float f ) const 
{
	return Vector4( x*f, y*f, z*f, w*f );
}

Vector4 Vector4::operator/( float f ) const 
{
	auto inv = 1.0f / f;
	return *this * inv;
}

Vector4& Vector4::operator +=( const Vector4& v )
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4& Vector4::operator -=( const Vector4& v ) 
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4& Vector4::operator *=( float f ) 
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}

Vector4& Vector4::operator /=( float f )
{
	auto inv = 1.0f / f;
	x *= inv;
	y *= inv;
	z *= inv;
	w *= inv;
	return *this;
}

Vector4 Vector4::operator -( ) const
{
	return Vector4( -x, -y, -z, -w );
}

bool Vector4::operator ==( const Vector4& v ) const
{
	return ( x == v.x ) && ( y == v.y ) && ( z == v.z ) && ( w == v.w );
}

bool Vector4::operator !=( const Vector4& v ) const
{
	return !( *this == v );
}
