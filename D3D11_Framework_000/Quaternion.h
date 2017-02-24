
#pragma once


namespace SKDX {
	namespace Math {

		class Vector3;

		class Quaternion{
		public:
			float x, y, z, w;

			static const Quaternion Identity;

			Quaternion( );
			Quaternion( float x, float y, float z, float w );
			Quaternion( const Vector3& v, float w );

			float Length( ) const;
			void Normalize( );
			Quaternion GetNormalized( ) const;

			void Rotate( const Vector3& axis, float angle );
			void Rotate( const Vector3& eulerAngles );
			void Rotate( float yaw, float pitch, float roll );

			Vector3 Transform( const Vector3& v );

			static Quaternion Slerp( const Quaternion& from, const Quaternion& to, float t );
			static Quaternion CreateRotation( const Vector3& axis, float angle );
			static Quaternion CreateRotation( float yaw, float pitch, float roll );
			static Quaternion CreateRotation( const Vector3& eulerAngles );
			Quaternion operator +( const Quaternion& q ) const;
			Quaternion operator -( const Quaternion& q ) const;
			Quaternion operator *( float f ) const;
			Quaternion operator /( float f ) const;

			Quaternion operator *( const Quaternion& ) const;
			Quaternion& operator *=( const Quaternion& );

			Vector3 operator *( const Vector3& v ) const;
		};

	};
};
