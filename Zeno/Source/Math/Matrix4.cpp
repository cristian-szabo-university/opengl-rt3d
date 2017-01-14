#include <memory>

#include "Zeno/Math/Matrix4.h"

namespace Zeno
{
	//-------------------------------------------------------------------------------------------------
	Matrix4::Matrix4() 
	{
		Identity();
	}

	//-------------------------------------------------------------------------------------------------
	Matrix4::Matrix4( float* pData ) 
	{
		memcpy( m_M, pData, sizeof( m_M ) );
	}

	//-------------------------------------------------------------------------------------------------
	Matrix4::Matrix4( float v11, float v12, float v13, float v14,	
					 float v21, float v22, float v23, float v24, 
					 float v31, float v32, float v33, float v34,	
					 float v41, float v42, float v43, float v44 ) 
	{
		m_M[ 0 ][ 0 ] = v11; m_M[ 0 ][ 1 ] = v12; m_M[ 0 ][ 2 ] = v13; m_M[ 0 ][ 3 ] = v14;
		m_M[ 1 ][ 0 ] = v21; m_M[ 1 ][ 1 ] = v22; m_M[ 1 ][ 2 ] = v23; m_M[ 1 ][ 3 ] = v24;
		m_M[ 2 ][ 0 ] = v31; m_M[ 2 ][ 1 ] = v32; m_M[ 2 ][ 2 ] = v33; m_M[ 2 ][ 3 ] = v34;
		m_M[ 3 ][ 0 ] = v41; m_M[ 3 ][ 1 ] = v42; m_M[ 3 ][ 2 ] = v43; m_M[ 3 ][ 3 ] = v44;
	}

	//-------------------------------------------------------------------------------------------------
	Matrix4::Matrix4( const Matrix4& rOther ) 
	{
		memcpy( m_M, rOther.m_M, sizeof( m_M ) );
	}

	//-------------------------------------------------------------------------------------------------
	Matrix4::~Matrix4() 
	{
	
	}

	//-------------------------------------------------------------------------------------------------
	Matrix4::operator float*()
	{
		return &m_A[0];
	}

	//-------------------------------------------------------------------------------------------------
	void Matrix4::Identity() 
	{
		m_M[ 0 ][ 0 ] = 1.0;
		m_M[ 1 ][ 0 ] = 0.0;
		m_M[ 2 ][ 0 ] = 0.0;
		m_M[ 3 ][ 0 ] = 0.0;

		m_M[ 0 ][ 1 ] = 0.0;
		m_M[ 1 ][ 1 ] = 1.0;
		m_M[ 2 ][ 1 ] = 0.0;
		m_M[ 3 ][ 1 ] = 0.0;

		m_M[ 0 ][ 2 ] = 0.0;
		m_M[ 1 ][ 2 ] = 0.0;
		m_M[ 2 ][ 2 ] = 1.0;
		m_M[ 3 ][ 2 ] = 0.0;

		m_M[ 0 ][ 3 ] = 0.0;
		m_M[ 1 ][ 3 ] = 0.0;
		m_M[ 2 ][ 3 ] = 0.0;
		m_M[ 3 ][ 3 ] = 1.0;
	}

	//-------------------------------------------------------------------------------------------------
	void Matrix4::Set( Matrix4& rOther )
	{
		memcpy( m_M, rOther.m_M, sizeof( m_M ) );
	}

	//-------------------------------------------------------------------------------------------------
	void Matrix4::Translate( Vector3 Translation ) 
	{
		Matrix4 Result( *this );

		Result.m_M[3][0] = m_M[0][0] * Translation.m_A[0] + m_M[1][0] * Translation.m_A[1] + m_M[2][0] * Translation.m_A[2] + m_M[3][0];
		Result.m_M[3][1] = m_M[0][1] * Translation.m_A[0] + m_M[1][1] * Translation.m_A[1] + m_M[2][1] * Translation.m_A[2] + m_M[3][1];
		Result.m_M[3][2] = m_M[0][2] * Translation.m_A[0] + m_M[1][2] * Translation.m_A[1] + m_M[2][2] * Translation.m_A[2] + m_M[3][2];
		Result.m_M[3][3] = m_M[0][3] * Translation.m_A[0] + m_M[1][3] * Translation.m_A[1] + m_M[2][3] * Translation.m_A[2] + m_M[3][3];

		*this = Result;
	}

	//-------------------------------------------------------------------------------------------------
	void  Matrix4::Scale( Vector3 Scale ) 
	{
		Matrix4 Result;

		Result.m_M[0][0] = m_M[0][0] * Scale.m_A[0];
		Result.m_M[0][1] = m_M[0][1] * Scale.m_A[0];
		Result.m_M[0][2] = m_M[0][2] * Scale.m_A[0];
		Result.m_M[0][3] = m_M[0][3] * Scale.m_A[0];

		Result.m_M[1][0] = m_M[1][0] * Scale.m_A[1];
		Result.m_M[1][1] = m_M[1][1] * Scale.m_A[1];
		Result.m_M[1][2] = m_M[1][2] * Scale.m_A[1];
		Result.m_M[1][3] = m_M[1][3] * Scale.m_A[1];

		Result.m_M[2][0] = m_M[2][0] * Scale.m_A[2];
		Result.m_M[2][1] = m_M[2][1] * Scale.m_A[2];
		Result.m_M[2][2] = m_M[2][2] * Scale.m_A[2];
		Result.m_M[2][3] = m_M[2][3] * Scale.m_A[2];

		Result.m_M[3][0] = m_M[3][0];
		Result.m_M[3][1] = m_M[3][1];
		Result.m_M[3][2] = m_M[3][2];
		Result.m_M[3][3] = m_M[3][3];

		*this = Result;
	}

	//-------------------------------------------------------------------------------------------------
	void Matrix4::Rotate( float nAngle, Vector3 Rotate )
	{
		nAngle *= ( 3.14f / 180.0f );

		float c = cos( nAngle );
		float s = sin( nAngle );

		Vector3 axis( Rotate.Normalize() );
		Vector3 temp(axis * (float(1) - c));

		Matrix4 MatRot;

		MatRot.m_M[0][0] = c + temp.m_A[0] * axis.m_A[0];
		MatRot.m_M[0][1] = 0 + temp.m_A[0] * axis.m_A[1] + s * axis.m_A[2];
		MatRot.m_M[0][2] = 0 + temp.m_A[0] * axis.m_A[2] - s * axis.m_A[1];

		MatRot.m_M[1][0] = 0 + temp.m_A[1] * axis.m_A[0] - s * axis.m_A[2];
		MatRot.m_M[1][1] = c + temp.m_A[1] * axis.m_A[1];
		MatRot.m_M[1][2] = 0 + temp.m_A[1] * axis.m_A[2] + s * axis.m_A[0];

		MatRot.m_M[2][0] = 0 + temp.m_A[2] * axis.m_A[0] + s * axis.m_A[1];
		MatRot.m_M[2][1] = 0 + temp.m_A[2] * axis.m_A[1] - s * axis.m_A[0];
		MatRot.m_M[2][2] = c + temp.m_A[2] * axis.m_A[2];

		Matrix4 Result;

		Result.m_M[0][0] = m_M[0][0] * MatRot.m_M[0][0] +  m_M[1][0] *  MatRot.m_M[0][1] + m_M[2][0] * MatRot.m_M[0][2];
		Result.m_M[0][1] = m_M[0][1] * MatRot.m_M[0][0] +  m_M[1][1] *  MatRot.m_M[0][1] + m_M[2][1] * MatRot.m_M[0][2];
		Result.m_M[0][2] = m_M[0][2] * MatRot.m_M[0][0] +  m_M[1][2] *  MatRot.m_M[0][1] + m_M[2][2] * MatRot.m_M[0][2];
		Result.m_M[0][3] = m_M[0][3] * MatRot.m_M[0][0] +  m_M[1][3] *  MatRot.m_M[0][1] + m_M[2][3] * MatRot.m_M[0][2];

		Result.m_M[1][0] = m_M[0][0] * MatRot.m_M[1][0] +  m_M[1][0] *  MatRot.m_M[1][1] + m_M[2][0] * MatRot.m_M[1][2];
		Result.m_M[1][1] = m_M[0][1] * MatRot.m_M[1][0] +  m_M[1][1] *  MatRot.m_M[1][1] + m_M[2][1] * MatRot.m_M[1][2];
		Result.m_M[1][2] = m_M[0][2] * MatRot.m_M[1][0] +  m_M[1][2] *  MatRot.m_M[1][1] + m_M[2][2] * MatRot.m_M[1][2];
		Result.m_M[1][3] = m_M[0][3] * MatRot.m_M[1][0] +  m_M[1][3] *  MatRot.m_M[1][1] + m_M[2][3] * MatRot.m_M[1][2];

		Result.m_M[2][0] = m_M[0][0] * MatRot.m_M[2][0] +  m_M[1][0] *  MatRot.m_M[2][1] + m_M[2][0] * MatRot.m_M[2][2];
		Result.m_M[2][1] = m_M[0][1] * MatRot.m_M[2][0] +  m_M[1][1] *  MatRot.m_M[2][1] + m_M[2][1] * MatRot.m_M[2][2];
		Result.m_M[2][2] = m_M[0][2] * MatRot.m_M[2][0] +  m_M[1][2] *  MatRot.m_M[2][1] + m_M[2][2] * MatRot.m_M[2][2];
		Result.m_M[2][3] = m_M[0][3] * MatRot.m_M[2][0] +  m_M[1][3] *  MatRot.m_M[2][1] + m_M[2][3] * MatRot.m_M[2][2];

		Result.m_M[3][0] = m_M[3][0];
		Result.m_M[3][1] = m_M[3][1];
		Result.m_M[3][2] = m_M[3][2];
		Result.m_M[3][3] = m_M[3][3];

		*this = Result;
	}

	//-------------------------------------------------------------------------------------------------
	void Matrix4::Perspective( float fov, float aspect, float zNear, float zFar ) 
	{
		fov *= ( 3.14f / 180.0f );

		float tanHalfFovy = tan( fov / 2.0f );

		m_A[0] = 1.0f / ( aspect * tanHalfFovy );
		m_A[1] = 0;
		m_A[2] = 0;
		m_A[3] = 0;

		m_A[4] = 0;
		m_A[5] = 1.0f / tanHalfFovy;
		m_A[6] = 0;
		m_A[7] = 0;

		m_A[8] = 0;
		m_A[9] = 0;
		m_A[10] = - (zFar + zNear) / (zFar - zNear);
		m_A[11] = -1;

		m_A[12] = 0;
		m_A[13] = 0;
		m_A[14] = - (2.0f * zFar * zNear) / (zFar - zNear);
		m_A[15] = 0;
	}

	//-------------------------------------------------------------------------------------------------
	void Matrix4::Ortho( float left, float right, float bottom, float top, float zNear, float zFar )
	{
		Matrix4 Result;

		Result.m_M[0][0] = 2.0f / (right - left);
		Result.m_M[1][1] = 2.0f / (top - bottom);
		Result.m_M[2][2] = - 2.0f / (zFar - zNear);
		Result.m_M[3][0] = - (right + left) / (right - left);
		Result.m_M[3][1] = - (top + bottom) / (top - bottom);
		Result.m_M[3][2] = - (zFar + zNear) / (zFar - zNear);

		*this = Result;
	}

	//-------------------------------------------------------------------------------------------------
	void Matrix4::LookAt( Vector3 &rPosition, Vector3 &rEye, Vector3 &rUp ) 
	{
		Vector3 zAxis = rEye - rPosition;
		zAxis.Normalize();

		Vector3 xAxis = zAxis.Cross( rUp );
		xAxis.Normalize();

		Vector3 yAxis = xAxis.Cross( zAxis );

		m_A[ 0 ] = xAxis.m_S.X;
		m_A[ 1 ] = yAxis.m_S.X;
		m_A[ 2 ] = -zAxis.m_S.X;
		m_A[ 3 ] = 0;

		m_A[ 4 ] = xAxis.m_S.Y;
		m_A[ 5 ] = yAxis.m_S.Y;
		m_A[ 6 ] = -zAxis.m_S.Y;
		m_A[ 7 ] = 0;

		m_A[ 8 ]  = xAxis.m_S.Z;
		m_A[ 9 ]  = yAxis.m_S.Z;
		m_A[ 10 ] = -zAxis.m_S.Z;
		m_A[ 11 ] = 0; 

		m_A[ 12 ] = -xAxis.Dot( rPosition );
		m_A[ 13 ] = -yAxis.Dot( rPosition );
		m_A[ 14 ] = zAxis.Dot( rPosition );
		m_A[ 15 ] = 1;
	}

	//-------------------------------------------------------------------------------------------------
	void Matrix4::Transpose() 
	{
		float m[ 16 ];

		memcpy( &m[ 0 ], m_A, sizeof( float ) * 16 );

		m_S._11 = m[ 0 ];
		m_S._21 = m[ 4 ];
		m_S._31 = m[ 8 ];
		m_S._41 = m[ 12 ];

		m_S._12 = m[ 1 ];
		m_S._22 = m[ 5 ];
		m_S._32 = m[ 9 ];
		m_S._42 = m[ 13 ];

		m_S._13 = m[ 2 ];
		m_S._23 = m[ 6 ];
		m_S._33 = m[ 10 ];
		m_S._43 = m[ 14 ];

		m_S._14 = m[ 3 ];
		m_S._24 = m[ 7 ];
		m_S._34 = m[ 11 ];
		m_S._44 = m[ 15 ];
	}

	//-------------------------------------------------------------------------------------------------
	void Matrix4::Multiply( Matrix4 &rOther ) 
	{
		Matrix4 m1( 
			m_M[0][0]*rOther.m_M[0][0] + m_M[0][1]*rOther.m_M[1][0] + m_M[0][2]*rOther.m_M[2][0] + m_M[0][3]*rOther.m_M[3][0],
			m_M[0][0]*rOther.m_M[0][1] + m_M[0][1]*rOther.m_M[1][1] + m_M[0][2]*rOther.m_M[2][1] + m_M[0][3]*rOther.m_M[3][1],
			m_M[0][0]*rOther.m_M[0][2] + m_M[0][1]*rOther.m_M[1][2] + m_M[0][2]*rOther.m_M[2][2] + m_M[0][3]*rOther.m_M[3][2],
			m_M[0][0]*rOther.m_M[0][3] + m_M[0][1]*rOther.m_M[1][3] + m_M[0][2]*rOther.m_M[2][3] + m_M[0][3]*rOther.m_M[3][3],

			m_M[1][0]*rOther.m_M[0][0] + m_M[1][1]*rOther.m_M[1][0] + m_M[1][2]*rOther.m_M[2][0] + m_M[1][3]*rOther.m_M[3][0],
			m_M[1][0]*rOther.m_M[0][1] + m_M[1][1]*rOther.m_M[1][1] + m_M[1][2]*rOther.m_M[2][1] + m_M[1][3]*rOther.m_M[3][1],
			m_M[1][0]*rOther.m_M[0][2] + m_M[1][1]*rOther.m_M[1][2] + m_M[1][2]*rOther.m_M[2][2] + m_M[1][3]*rOther.m_M[3][2],
			m_M[1][0]*rOther.m_M[0][3] + m_M[1][1]*rOther.m_M[1][3] + m_M[1][2]*rOther.m_M[2][3] + m_M[1][3]*rOther.m_M[3][3],

			m_M[2][0]*rOther.m_M[0][0] + m_M[2][1]*rOther.m_M[1][0] + m_M[2][2]*rOther.m_M[2][0] + m_M[2][3]*rOther.m_M[3][0],
			m_M[2][0]*rOther.m_M[0][1] + m_M[2][1]*rOther.m_M[1][1] + m_M[2][2]*rOther.m_M[2][1] + m_M[2][3]*rOther.m_M[3][1],
			m_M[2][0]*rOther.m_M[0][2] + m_M[2][1]*rOther.m_M[1][2] + m_M[2][2]*rOther.m_M[2][2] + m_M[2][3]*rOther.m_M[3][2],
			m_M[2][0]*rOther.m_M[0][3] + m_M[2][1]*rOther.m_M[1][3] + m_M[2][2]*rOther.m_M[2][3] + m_M[2][3]*rOther.m_M[3][3],

			m_M[3][0]*rOther.m_M[0][0] + m_M[3][1]*rOther.m_M[1][0] + m_M[3][2]*rOther.m_M[2][0] + m_M[3][3]*rOther.m_M[3][0],
			m_M[3][0]*rOther.m_M[0][1] + m_M[3][1]*rOther.m_M[1][1] + m_M[3][2]*rOther.m_M[2][1] + m_M[3][3]*rOther.m_M[3][1],
			m_M[3][0]*rOther.m_M[0][2] + m_M[3][1]*rOther.m_M[1][2] + m_M[3][2]*rOther.m_M[2][2] + m_M[3][3]*rOther.m_M[3][2],
			m_M[3][0]*rOther.m_M[0][3] + m_M[3][1]*rOther.m_M[1][3] + m_M[3][2]*rOther.m_M[2][3] + m_M[3][3]*rOther.m_M[3][3] 
		);

		memcpy( &m_M, m1, sizeof( float ) * 16 );
	}

	//-------------------------------------------------------------------------------------------------
	void Matrix4::operator *= ( Matrix4 &rOther )
	{
		Multiply( rOther );
	}

	//-------------------------------------------------------------------------------------------------
	bool Matrix4::operator == ( Matrix4 &rOther ) const 
	{
		for ( int i = 0; i < 4; ++i ) 
		{
			for ( int j = 0; j < 4; ++j ) 
			{
				if ( m_M[ i ][ j ] != rOther.m_M[ i ][ j ] ) 
				{
					return false;
				}
			}
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	Matrix4& Matrix4::operator = ( Matrix4 &rOther ) 
	{
		if ( *this == rOther ) 
		{
			return *this;
		}

		memcpy( m_M, rOther.m_M, sizeof( m_M ) );
	
		return *this;
	}
}
