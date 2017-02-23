
#pragma once

class Vector3;
class Quaternion;

class Matrix4x4 {
public:
	union { 
		float m[16];
		struct { float _11, _21, _31, _41;
				 float _12, _22, _32, _42;
				 float _13, _23, _33, _43;
				 float _14, _24, _34, _44; };
	};

	static const Matrix4x4 Identity;

	Matrix4x4( );
	Matrix4x4( float* m );
	Matrix4x4( float _11, float _12, float _13, float _14,
			   float _21, float _22, float _23, float _24,
			   float _31, float _32, float _33, float _34,
			   float _41, float _42, float _43, float _44 );

	//void Transpose( );
	//void Inverse( );

	//Matrix4x4 GetTransposed( ) const;
	//Matrix4x4 GetInversed( ) const;

	void Translate( const Vector3& translation );
	void Translate( float x, float y, float z );

	void Rotate( const Vector3& eulerAngles );
	void Rotate( float yaw, float pitch, float roll );
	void Rotate( const Vector3& axis, float angle );
	void Rotate( const Quaternion& q );

	void RotateY( float angle );
	void RotateX( float angle );
	void RotateZ( float angle );

	void Scale( const Vector3& size );
	void Scale( float sizeX, float sizeY, float sizeZ );
	void Scale( float size );

	void LookAt( const Vector3& eye, const Vector3& lookAt, const Vector3& upVec );
	void PerspectiveFov( float fov, float aspect, float nearClip, float farClip );

	void Multiply( const Matrix4x4& mtx );

	Vector3 TransformCoord( const Vector3& v );
	Vector3 TransformNormal( const Vector3& v );

	/*		Static functions 	*/
	static Matrix4x4 CreateTranslation( const Vector3& translation );
	static Matrix4x4 CreateTranslation( float x, float y, float z );

	static Matrix4x4 CreateRotation( const Vector3& eulerAngles );
	static Matrix4x4 CreateRotation( float yaw, float pitch, float roll );
	static Matrix4x4 CreateRotation( const Vector3& axis, float angle );
	static Matrix4x4 CreateRotation( const Quaternion& q );

	static Matrix4x4 CreateRotationY( float angle );
	static Matrix4x4 CreateRotationX( float angle );
	static Matrix4x4 CreateRotationZ( float angle );

	static Matrix4x4 CreateScaling( const Vector3& size );
	static Matrix4x4 CreateScaling( float sizeX, float sizeY, float sizeZ );
	static Matrix4x4 CreateScaling( float size );

	static Matrix4x4 CreateLookAt( const Vector3& eye, const Vector3& lookAt, const Vector3& upVec );
	static Matrix4x4 CreatePersectiveFov( float fov, float aspect, float nearClip, float farClip );

	static Matrix4x4 Multiply( const Matrix4x4& left, const Matrix4x4& right ); 

	/*		Operators		*/
	Matrix4x4 operator *( const Matrix4x4& ) const;
};
