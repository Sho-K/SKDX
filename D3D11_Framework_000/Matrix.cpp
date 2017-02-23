
#include <math.h>

#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

const Matrix4x4 Matrix4x4::Identity = Matrix4x4( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 );

Matrix4x4::Matrix4x4( )
{
	*this = Identity;
}

Matrix4x4::Matrix4x4( float* m )
{
	for( int i=0; i<16; ++i ) this->m[i] = m[i];
}

Matrix4x4::Matrix4x4( float _11, float _12, float _13, float _14,
					  float _21, float _22, float _23, float _24,
					  float _31, float _32, float _33, float _34,
					  float _41, float _42, float _43, float _44 )
{
	this->_11 = _11;
	this->_12 = _12;
	this->_13 = _13;
	this->_14 = _14;

	this->_21 = _21;
	this->_22 = _22;
	this->_23 = _23;
	this->_24 = _24;

	this->_31 = _31;
	this->_32 = _32;
	this->_33 = _33;
	this->_34 = _34;

	this->_41 = _41;
	this->_42 = _42;
	this->_43 = _43;
	this->_44 = _44;
}

Matrix4x4 Matrix4x4::operator *( const Matrix4x4& mtx ) const 
{
	Matrix4x4 out = Identity;

	auto left	= mtx;
	auto right	= *this;

	for( int i=0; i<4; ++i ){
		for( int j=0; j<4; ++j ){
			out.m[i*4+j] = left.m[i*4+0]*right.m[j] + left.m[i*4+1]*right.m[j+4] + left.m[i*4+2]*right.m[j+8] + left.m[i*4+3]*right.m[12+j];
		}
	}
	return out;
}


/*		Translation		*/
void Matrix4x4::Translate( const Vector3& translation )
{
	*this = Identity;
	this->_41 = translation.x;
	this->_42 = translation.y;
	this->_43 = translation.z;
}

void Matrix4x4::Translate( float x, float y, float z )
{
	Translate( Vector3(x,y,x) );
}

Matrix4x4 Matrix4x4::CreateTranslation( const Vector3& translation )
{
	auto out = Identity;
	out._41 = translation.x;
	out._42 = translation.y;
	out._43 = translation.z;
	return out;
}

Matrix4x4 Matrix4x4::CreateTranslation( float x, float y, float z )
{
	return CreateTranslation( Vector3(x, y, z) );
}


/*			Rotation		*/
void Matrix4x4::RotateY( float angle )
{
	*this = Identity;
	this->_11 = cosf( angle );
	this->_31 = sinf( angle );
	this->_13 = -sinf( angle );
	this->_33 = cosf( angle );
}

void Matrix4x4::RotateX( float angle )
{
	*this = Identity;
	this->_22 = cosf( angle );
	this->_23 = sinf( angle );
	this->_32 = -sinf( angle );
	this->_33 = cosf( angle );
}

void Matrix4x4::RotateZ( float angle )
{
	*this = Identity;
	this->_11 = cosf( angle );
	this->_12 = sinf( angle );
	this->_21 = -sinf( angle );
	this->_22 = cosf( angle );
}

void Matrix4x4::Rotate( const Vector3& eulerAngles )
{
	auto yawing = CreateRotationY( eulerAngles.y );
	auto pitching = CreateRotationX( eulerAngles.x );
	auto rolling = CreateRotationZ( eulerAngles.z );
	*this = yawing * pitching * rolling;
}

void Matrix4x4::Rotate( float yaw, float pitch, float roll )
{
	Rotate( Vector3(pitch, yaw, roll) );
}

void Matrix4x4::Rotate( const Vector3& axis, float angle )
{
	auto q = Quaternion::CreateRotation( axis, angle );
	Rotate( q );
}

Matrix4x4 Matrix4x4::CreateRotation( const Vector3& axis, float angle )
{
	auto q = Quaternion::CreateRotation( axis, angle );
	return CreateRotation( q );
}


void Matrix4x4::Rotate( const Quaternion& q )
{
	auto x2 = q.x * q.x;
	auto y2 = q.y * q.y;
	auto z2 = q.z * q.z;

	auto xy = q.x * q.y;
	auto zw = q.z * q.w;
	auto xz = q.x * q.z;
	auto yw = q.y * q.w;
	auto xw = q.x * q.w;
	auto yz = q.y * q.z;

	_11 = 1.0f - 2*y2 - 2*z2;
	_12 = 2*xy + 2*zw;
	_13 = 2*xz - 2*yw;
	_14 = 0.0f;

	_21 = 2*xy - 2*zw;
	_22 = 1 - 2*x2 - 2*z2;
	_23 = 2*yz + 2*xw;
	_24 = 0.0f;

	_31 = 2*xz + 2*yw;
	_32 = 2*yz - 2*xw;
	_33 = 1 - 2*x2 - 2*y2;
	_34 = 0.0f;

	_41 = 0.0f;
	_42 = 0.0f;
	_43 = 0.0f;
	_44 = 1.0f;
}

Matrix4x4 Matrix4x4::CreateRotation( const Quaternion& q )
{
	auto x2 = q.x * q.x;
	auto y2 = q.y * q.y;
	auto z2 = q.z * q.z;

	auto xy = q.x * q.y;
	auto zw = q.z * q.w;
	auto xz = q.x * q.z;
	auto yw = q.y * q.w;
	auto xw = q.x * q.w;
	auto yz = q.y * q.z;

	auto out = Identity;
	out._11 = 1.0f - 2*y2 - 2*z2;
	out._12 = 2*xy + 2*zw;
	out._13 = 2*xz - 2*yw;
	out._14 = 0.0f;

	out._21 = 2*xy - 2*zw;
	out._22 = 1 - 2*x2 - 2*z2;
	out._23 = 2*yz + 2*xw;
	out._24 = 0.0f;

	out._31 = 2*xz + 2*yw;
	out._32 = 2*yz - 2*xw;
	out._33 = 1 - 2*x2 - 2*y2;
	out._34 = 0.0f;

	out._41 = 0.0f;
	out._42 = 0.0f;
	out._43 = 0.0f;
	out._44 = 1.0f;
	
	return out;
}

Matrix4x4 Matrix4x4::CreateRotationY( float angle )
{
	auto mtx = Identity;
	mtx.RotateY( angle );
	return mtx;
}

Matrix4x4 Matrix4x4::CreateRotationX( float angle )
{
	auto mtx = Identity;
	mtx.RotateX( angle );
	return mtx;
}

Matrix4x4 Matrix4x4::CreateRotationZ( float angle )
{
	auto mtx = Identity;
	mtx.RotateZ( angle );
	return mtx;
}

Matrix4x4 Matrix4x4::CreateRotation( const Vector3& eulerAngles )
{
	auto yawing = CreateRotationY( eulerAngles.y );
	auto pitching = CreateRotationX( eulerAngles.x );
	auto rolling = CreateRotationZ( eulerAngles.z );
	return yawing * pitching * rolling;
}

Matrix4x4 Matrix4x4::CreateRotation( float yaw, float pitch, float roll )
{
	return CreateRotation( Vector3(pitch, yaw, roll) );
}


/*			Scaling			*/
void Matrix4x4::Scale( const Vector3& size )
{
	*this = Identity;
	this->_11 = size.x;
	this->_22 = size.y;
	this->_33 = size.z;
}

void Matrix4x4::Scale( float sizeX, float sizeY, float sizeZ )
{
	Scale( Vector3(sizeX, sizeY, sizeZ) );
}

void Matrix4x4::Scale( float size )
{
	Scale( Vector3(size,size,size) );
}

Matrix4x4 Matrix4x4::CreateScaling( const Vector3& size )
{
	auto out = Identity;
	out._11 = size.x;
	out._22 = size.y;
	out._33 = size.z;
	return out;
}

Matrix4x4 Matrix4x4::CreateScaling( float sizeX, float sizeY, float sizeZ )
{
	return CreateScaling( Vector3(sizeX, sizeY, sizeZ) );
}

Matrix4x4 Matrix4x4::CreateScaling( float size )
{
	return CreateScaling( Vector3(size, size, size) );
}


/*		LookAt		*/
void Matrix4x4::LookAt( const Vector3& eye, const Vector3& at, const Vector3& up )
{
	auto z = (at - eye).GetNormalized( );
	auto x = Vector3::Cross( up, z ).GetNormalized( );
	auto y= Vector3::Cross( z, x ).GetNormalized( );
	
	auto px = Vector3::Dot( x, eye );
	auto py = Vector3::Dot( y, eye );
	auto pz = Vector3::Dot( z, eye );

	*this = Matrix4x4( x.x, y.x, z.x, 0.0f,
					   x.y, y.y, z.y, 0.0f,
					   x.z, y.z, z.z, 0.0f,
					   -px, -py, -pz, 1.0f );
}

Matrix4x4 Matrix4x4::CreateLookAt( const Vector3& eye, const Vector3& at, const Vector3& up )
{
	auto z = (at - eye).GetNormalized( );
	auto x = Vector3::Cross( up, z ).GetNormalized( );
	auto y = Vector3::Cross( z, x ).GetNormalized( );
	
	auto px = Vector3::Dot( x, eye );
	auto py = Vector3::Dot( y, eye );
	auto pz = Vector3::Dot( z, eye );

	return Matrix4x4( x.x, y.x, z.x, 0.0f,
					  x.y, y.y, z.y, 0.0f,
					  x.z, y.z, z.z, 0.0f,
					  -px, -py, -pz, 1.0f );
}

/*			Projection			*/
void Matrix4x4::PerspectiveFov( float fov, float aspect, float nearClip, float farClip )
{
	auto sy = 1.0f / tanf( fov*0.5f );
	auto sx = sy / aspect;
	auto sz = farClip / (farClip-nearClip);
	auto szn = -sz * nearClip;
	
	*this =  Matrix4x4(   sx, 0.0f, 0.0f, 0.0f, 
						0.0f,   sy, 0.0f, 0.0f,
						0.0f, 0.0f,   sz, 1.0f,
						0.0f, 0.0f,  szn, 0.0f );
}

Matrix4x4 Matrix4x4::CreatePersectiveFov( float fov, float aspect, float nearClip, float farClip )
{
	auto sy = 1.0f / tanf( fov*0.5f );
	auto sx = sy / aspect;
	auto sz = farClip / (farClip-nearClip);
	auto szn = -sz * nearClip;
	return Matrix4x4(   sx,	0.0f, 0.0f, 0.0f, 
					  0.0f,   sy, 0.0f, 0.0f,
					  0.0f,	0.0f,   sz, 1.0f,
					  0.0f, 0.0f,  szn, 0.0f );
}