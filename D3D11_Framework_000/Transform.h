
#pragma once

#include <memory>
#include "Math.h"

namespace SKDX{
	class Transform {
	public:
		static std::shared_ptr< Transform > Create( );
		static std::shared_ptr< Transform > Create( const Math::Vector3& pos, const Math::Quaternion& rot, const Math::Vector3& size=Math::Vector3(1,1,1) );

		~Transform( );
		void Update( );

		void SetParent( const std::shared_ptr< Transform >& transform );

		void SetPosition( const Math::Vector3& pos );
		void SetPosition( float x, float y, float z );
		void SetRotation( const Math::Quaternion& rotation );
		void SetRotation( const Math::Vector3& axis, float angle );
		void SetRotation( const Math::Vector3& eularAngles );
		void SetRotation( float yaw, float pitch, float roll );
		void SetSize( const Math::Vector3& size );
		void SetSize( float x, float y, float z );
		void SetSize( float size );

		void Translate( const Math::Vector3& translation );
		void Translate( float x, float y, float z );

		void Rotate( const Math::Quaternion& rotation );
		void Rotate( const Math::Vector3& axis, float angle );
		void Rotate( const Math::Vector3& eularAngles );
		void Rotate( float yaw, float pitch, float roll );

		const Math::Vector3&			GetPosition( )	const { return position; }
		const Math::Quaternion&		GetRotaiton( )	const { return rotation; }
		const Math::Matrix4x4&			GetMatrix( )	const { return matrix; }

		const Math::Vector3&			GetForward( )	const;
		const Math::Vector3&			GetBackward( )	const;
		const Math::Vector3&			GetRight( )		const;
		const Math::Vector3&			GetLeft( )		const;
		const Math::Vector3&			GetUpward( )	const;
		const Math::Vector3&			GetDownward( )	const;
	private:
		Transform( );
		Transform( const Math::Vector3& pos, const Math::Quaternion& rot, const Math::Vector3& size );
		
		void UpdateTranslationMatrix( );
		void UpdateRotationMatrix( );
		void UpdateScalingMatrix( );

		Math::Vector3				position;
		Math::Quaternion			rotation;
		Math::Vector3				size;

		Math::Matrix4x4			mtxTranslation;
		Math::Matrix4x4			mtxRotation;
		Math::Matrix4x4			mtxScaling;

		Math::Matrix4x4			matrix;

		Math::Vector3				forward;
		Math::Vector3				right;
		Math::Vector3				up;

		std::weak_ptr< Transform > parent;
	};
};
