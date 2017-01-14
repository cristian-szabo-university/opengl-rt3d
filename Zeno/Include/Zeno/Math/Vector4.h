#pragma once

#include "Zeno/Config.h"

#include "Vector3.h"

namespace Zeno
{
	class ZENO_DLL Vector4 
	{
	public:
		Vector4();

		Vector4( float value );

		Vector4( float x, float y, float z, float w );

		Vector4( const Vector4& rOther );

		~Vector4();

		operator float*();

		void Set( float x, float y, float z, float w );

		float Length() const;

		float SqaredLength() const;

		Vector4 operator + ( Vector4& rOther );

		Vector4 &operator += ( Vector4& rOther );

		Vector4 operator - ( Vector4& rOther );

		Vector4 &operator -= ( Vector4& rOther );

		Vector4 operator * ( Vector4& rOther );

		Vector4 &operator *= ( Vector4& rOther );

		Vector4 operator + ( float nValue );

		Vector4 &operator += ( float nValue );

		Vector4 operator - ( float nValue );

		Vector4 &operator -= ( float nValue );

		Vector4 operator * ( float nValue );

		Vector4 &operator *= ( float nValue );

		bool operator == ( const Vector4& rOther ) const;

		Vector4 &operator = ( const Vector4& rOther );

		union
		{
			struct
			{
				float X, Y, Z, W;
			} m_S;

			float m_A[4];
		};
	};

	Vector4 operator * ( float scalar, Vector4& vector );
}
