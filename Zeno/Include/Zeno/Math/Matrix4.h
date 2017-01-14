#pragma once

#include "Zeno/Config.h"

#include "Vector3.h"

namespace Zeno
{
	class ZENO_DLL Matrix4 
	{
	public:
		Matrix4();

		Matrix4( float* pData );

		Matrix4( float v11, float v12, float v13, float v14,	
			float v21, float v22, float v23, float v24,
			float v31, float v32, float v33, float v34,	
			float v41, float v42, float v43, float v44 );

		Matrix4( const Matrix4& rOther );
	
		~Matrix4();

		operator float*();
	
		void Identity();

		void Set( Matrix4& rOther );

		void Translate( Vector3 Translation );

		void Scale( Vector3 Scale );

		void Rotate( float nAngle, Vector3 Rotate );

		void Perspective( float fov, float aspect, float zNear, float zFar );

		void Ortho( float left, float right, float bottom, float top, float zNear, float zFar );

		void LookAt( Vector3& rPosition, Vector3& rEye, Vector3& rUp );
	
		void Transpose();

		void operator *= ( Matrix4 &rOther );

		bool operator == ( Matrix4 &rOther ) const;
	
		Matrix4 &operator = ( Matrix4 &rOther );

		union 
		{
			struct 
			{
				float _11, _21, _31, _41;   
				float _12, _22, _32, _42;
				float _13, _23, _33, _43;
				float _14, _24, _34, _44;
			} m_S;

			float m_A[ 16 ];

			float m_M[ 4 ][ 4 ];
		};

	private:
		void Multiply( Matrix4& rOther );

	};
}
