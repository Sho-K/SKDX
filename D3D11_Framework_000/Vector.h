
#pragma once

class Vector2;
class Vector3;
class Vector4;

class Vector3 {
public:
	float x, y, z;

	static const Vector3 Zero;
	static const Vector3 Forward;
	static const Vector3 Backward;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Right;
	static const Vector3 Left;

	Vector3( );
	Vector3( float f );
	Vector3( float x, float y, float z );
	Vector3( const Vector2& v );
	//Vector3( const Vector2& v, float z );
	//Vector3( const Vector4& v );

	float Length( ) const ; 
	void Normalize( );
	Vector3 GetNormalized( ) const;

	float Dot( const Vector3& v ) const;
	Vector3 Cross( const Vector3& v ) const;

	static float Length( const Vector3& v );
	static const Vector3 Normalize( const Vector3& v );
	static float Dot( const Vector3& v0, const Vector3& v1 );
	static const Vector3 Cross( const Vector3& v0, const Vector3& v1 );

	static Vector3 Lerp( const Vector3& from, const Vector3& to, float t );


	/*		operator overloads		*/
	Vector3 operator +( const Vector3& ) const;
	Vector3 operator -( const Vector3& ) const;
	Vector3 operator *( float f ) const;
	Vector3 operator /( float f ) const;

	Vector3& operator =( float f );
	Vector3& operator =( const Vector2& v );

	Vector3& operator +=( const Vector3& v );
	Vector3& operator -=( const Vector3& v );
	Vector3& operator *=( float f );
	Vector3& operator /=( float f );

	operator float*( ) { return &x; }
};

class Vector2 {
public:
	float x, y;

	static const Vector2 Zero;
	static const Vector2 Up;
	static const Vector2 Down;
	static const Vector2 Right;
	static const Vector2 Left;

	Vector2( );
	Vector2( float x, float y );
	Vector2( float f );

	float Length( ) const;

	void Normalize( );
	Vector2 GetNormalized( ) const;

	float Dot( const Vector2& v ) const;
	float Cross( const Vector2& v ) const;

	static float Length( const Vector2& v );
	static Vector2 Normalize( const Vector2& v );
	static float Dot( const Vector2& v0, const Vector2& v1 );
	static float Cross( const Vector2& v0, const Vector2& v1 );

	/*		operators		*/
	Vector2 operator +( const Vector2& v ) const;
	Vector2 operator -( const Vector2& v ) const;
	Vector2 operator *( float f ) const;
	Vector2 operator /( float f ) const;

	Vector2& operator =( float f );
	Vector2& operator =( const Vector3& v );

	Vector2& operator +=( const Vector2& v );
	Vector2& operator -=( const Vector2& v );
	Vector2& operator *=( float f );
	Vector2& operator /=( float f );

	operator float*( ) { return &x; }
};