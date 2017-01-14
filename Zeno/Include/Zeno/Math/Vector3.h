#pragma once

#include "Zeno/Config.h"

namespace Zeno
{
	class ZENO_DLL Vector3 
	{
	public:
		Vector3();

		Vector3( float nValue );

		Vector3( float x, float y, float z );

		Vector3( const Vector3& rOther );

		~Vector3();

		operator float*();

		void Set( float x, float y, float z );

		float Length() const;

		float SqaredLength() const;

		Vector3& Normalize();

		float Dot( Vector3& rOther ) const;

		Vector3 Cross( Vector3& rOther ) const;

		Vector3 operator + ( Vector3& rOther ) const;

		Vector3 &operator += ( Vector3& rOther );

		Vector3 operator - ( Vector3& rOther ) const;

		Vector3 &operator -= ( Vector3& rOther );

		Vector3 operator * ( Vector3& rOther ) const;

		Vector3 &operator *= ( Vector3& rOther );

		Vector3 operator + ( float nValue ) const;

		Vector3 &operator += ( float nValue );

		Vector3 operator - ( float nValue ) const;

		Vector3 &operator -= ( float nValue );

		Vector3 operator * ( float nValue ) const;

		Vector3 &operator *= ( float nValue );

		bool operator == ( const Vector3& rOther ) const;

		bool operator != ( const Vector3& rOther ) const;

		Vector3 &operator = ( Vector3& rOther );

		union
		{
			struct
			{
				float X, Y, Z;
			} m_S;

			float m_A[3];
		};
	};
}
