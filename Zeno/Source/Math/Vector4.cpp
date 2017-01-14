#include "Zeno/Math/Vector4.h"

namespace Zeno
{
	//-------------------------------------------------------------------------------------------------
	Vector4::Vector4()
	{
		m_S.X = 0.0f;
		m_S.Y = 0.0f;
		m_S.Z = 0.0f;
		m_S.W = 1.0f;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4::Vector4( float value )
	{
		m_S.X = value;
		m_S.Y = value;
		m_S.Z = value;
		m_S.W = 1.0f;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4::Vector4( float x, float y, float z, float w )
	{
		m_S.X = x;
		m_S.Y = y;
		m_S.Z = z;
		m_S.W = w;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4::Vector4( const Vector4& rOther )
	{
		m_S.X = rOther.m_S.X;
		m_S.Y = rOther.m_S.Y;
		m_S.Z = rOther.m_S.Z;
		m_S.W = rOther.m_S.W;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4::~Vector4() 
	{
	
	}

	//-------------------------------------------------------------------------------------------------
	Vector4::operator float*()
	{
		return &m_A[0];
	}

	//-------------------------------------------------------------------------------------------------
	void Vector4::Set( float x, float y, float z, float w ) 
	{
		m_S.X = x;
		m_S.Y = y;
		m_S.Z = z;
		m_S.W = w;
	}

	//-------------------------------------------------------------------------------------------------
	float Vector4::Length() const 
	{
		return sqrt( m_S.X * m_S.X + m_S.Y * m_S.Y + m_S.Z * m_S.Z + m_S.W * m_S.W );
	}

	//-------------------------------------------------------------------------------------------------
	float Vector4::SqaredLength() const 
	{
		return ( m_S.X * m_S.X + m_S.Y * m_S.Y + m_S.Z * m_S.Z + m_S.W * m_S.W );
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 Vector4::operator + ( Vector4& rOther ) 
	{
		return Vector4( m_S.X + rOther.m_S.X,
			m_S.Y + rOther.m_S.Y, 
			m_S.Z + rOther.m_S.Z, 
			m_S.W + rOther.m_S.W );
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 &Vector4::operator += ( Vector4& rOther ) 
	{
		m_S.X += rOther.m_S.X;
		m_S.Y += rOther.m_S.Y;
		m_S.Z += rOther.m_S.Z;

		return *this;

	}

	//-------------------------------------------------------------------------------------------------
	Vector4 Vector4::operator - ( Vector4& rOther ) 
	{
		return Vector4( m_S.X - rOther.m_S.X,
			m_S.Y - rOther.m_S.Y, 
			m_S.Z - rOther.m_S.Z, 
			m_S.W - rOther.m_S.W );
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 &Vector4::operator -= ( Vector4& rOther ) 
	{
		m_S.X -= rOther.m_S.X;
		m_S.Y -= rOther.m_S.Y;
		m_S.Z -= rOther.m_S.Z;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 Vector4::operator * ( Vector4& rOther ) 
	{
		return Vector4( m_S.X * rOther.m_S.X, 
			m_S.Y * rOther.m_S.Y, 
			m_S.Z * rOther.m_S.Z, 
			m_S.W * rOther.m_S.W );
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 &Vector4::operator *= ( Vector4& rOther ) 
	{
		m_S.X *= rOther.m_S.X;
		m_S.Y *= rOther.m_S.Y;
		m_S.Z *= rOther.m_S.Z;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 Vector4::operator + ( float nValue ) 
	{
		return Vector4( m_S.X + nValue, m_S.Y + nValue,  m_S.Z + nValue, m_S.W + nValue );
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 &Vector4::operator += ( float nValue ) 
	{
		m_S.X += nValue;
		m_S.Y += nValue;
		m_S.Z += nValue;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 Vector4::operator - ( float nValue ) 
	{
		Vector4 newValue;

		newValue.m_S.X = m_S.X - nValue;
		newValue.m_S.Y = m_S.Y - nValue;
		newValue.m_S.Z = m_S.Z - nValue;

		return newValue;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 &Vector4::operator -= ( float nValue ) 
	{
		m_S.X -= nValue;
		m_S.Y -= nValue;
		m_S.Z -= nValue;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 Vector4::operator * ( float nValue ) 
	{
		Vector4 newValue;

		newValue.m_S.X = m_S.X * nValue;
		newValue.m_S.Y = m_S.Y * nValue;
		newValue.m_S.Z = m_S.Z * nValue;

		return newValue;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 &Vector4::operator *= ( float nValue ) 
	{
		m_S.X *= nValue;
		m_S.Y *= nValue;
		m_S.Z *= nValue;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	bool Vector4::operator == ( const Vector4& rOther ) const 
	{
		return ( m_S.X == rOther.m_S.X && 
			m_S.Y == rOther.m_S.Y && 
			m_S.Z == rOther.m_S.Z && 
			m_S.W == rOther.m_S.W );
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 &Vector4::operator = ( const Vector4& rOther ) {
		if ( rOther == *this ) 
		{
			return *this;
		}

		m_S.X = rOther.m_S.X;
		m_S.Y = rOther.m_S.Y;
		m_S.Z = rOther.m_S.Z;
		m_S.W = rOther.m_S.W;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	Vector4 operator * ( float scalar, Vector4& vector ) 
	{
		return vector * scalar; 
	}
}
