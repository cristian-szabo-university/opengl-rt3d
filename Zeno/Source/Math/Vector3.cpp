#include "Zeno/Math/Vector3.h"

namespace Zeno
{
	//-------------------------------------------------------------------------------------------------
	Vector3::Vector3()
	{
		m_S.X = 0.0f;
		m_S.Y = 0.0f;
		m_S.Z = 0.0f;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3::Vector3( float nValue )
	{
		m_S.X = nValue;
		m_S.Y = nValue;
		m_S.Z = nValue;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3::Vector3( float x, float y, float z ) 
	{
		m_S.X = x;
		m_S.Y = y;
		m_S.Z = z;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3::Vector3( const Vector3& rOther )
	{
		m_S.X = rOther.m_S.X;
		m_S.Y = rOther.m_S.Y;
		m_S.Z = rOther.m_S.Z;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3::~Vector3() 
	{
	
	}

	//-------------------------------------------------------------------------------------------------
	Vector3::operator float*()
	{
		return &m_A[0];
	}

	//-------------------------------------------------------------------------------------------------
	void Vector3::Set( float x, float y, float z ) 
	{
		m_S.X = x;
		m_S.Y = y;
		m_S.Z = z;
	}

	//-------------------------------------------------------------------------------------------------
	float Vector3::Length() const 
	{
		return sqrt( m_S.X*m_S.X + m_S.Y*m_S.Y + m_S.Z*m_S.Z );
	}

	//-------------------------------------------------------------------------------------------------
	float Vector3::SqaredLength() const 
	{
		return ( m_S.X*m_S.X + m_S.Y*m_S.Y + m_S.Z*m_S.Z );
	}

	//-------------------------------------------------------------------------------------------------
	 Vector3 &Vector3::Normalize() 
	 {
		float Len = Length();

		if ( 0.0 != Len ) 
		{
			float InvLen = static_cast<float>( 1.0 / Len );

			m_S.X *= InvLen;
			m_S.Y *= InvLen;
			m_S.Z *= InvLen;
		}

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	float Vector3::Dot( Vector3& rOther ) const 
	{
		return m_S.X * rOther.m_S.X + m_S.Y * rOther.m_S.Y + m_S.Z * rOther.m_S.Z;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 Vector3::Cross( Vector3& rOther ) const 
	{
		return Vector3( 
			m_S.Y * rOther.m_S.Z - m_S.Z * rOther.m_S.Y, 
			m_S.Z * rOther.m_S.X - m_S.X * rOther.m_S.Z, 
			m_S.X * rOther.m_S.Y - m_S.Y * rOther.m_S.X );
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 Vector3::operator + ( Vector3& rOther ) const 
	{
		return Vector3( m_S.X + rOther.m_S.X, m_S.Y + rOther.m_S.Y, m_S.Z + rOther.m_S.Z );
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 &Vector3::operator += ( Vector3& rOther ) 
	{
		m_S.X += rOther.m_S.X;
		m_S.Y += rOther.m_S.Y;
		m_S.Z += rOther.m_S.Z;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 Vector3::operator - ( Vector3& rOther ) const 
	{
		return Vector3( m_S.X - rOther.m_S.X, m_S.Y - rOther.m_S.Y, m_S.Z - rOther.m_S.Z );
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 &Vector3::operator -= ( Vector3& rOther ) 
	{
		m_S.X -= rOther.m_S.X;
		m_S.Y -= rOther.m_S.Y;
		m_S.Z -= rOther.m_S.Z;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 Vector3::operator * ( Vector3& rOther ) const 
	{
		return Vector3( m_S.X * rOther.m_S.X, m_S.Y * rOther.m_S.Y, m_S.Z * rOther.m_S.Z );
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 &Vector3::operator *= ( Vector3& rOther ) 
	{
		m_S.X *= rOther.m_S.X;
		m_S.Y *= rOther.m_S.Y;
		m_S.Z *= rOther.m_S.Z;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 Vector3::operator + ( float nValue ) const 
	{
		Vector3 newValue;

		newValue.m_S.X = m_S.X + nValue;
		newValue.m_S.Y = m_S.Y + nValue;
		newValue.m_S.Z = m_S.Z + nValue;

		return newValue;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 &Vector3::operator += ( const float nValue )
	{
		m_S.X += nValue;
		m_S.Y += nValue;
		m_S.Z += nValue;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 Vector3::operator - ( float nValue ) const 
	{
		Vector3 newValue;

		newValue.m_S.X = m_S.X - nValue;
		newValue.m_S.Y = m_S.Y - nValue;
		newValue.m_S.Z = m_S.Z - nValue;

		return newValue;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 &Vector3::operator -= ( float nValue ) 
	{
		m_S.X -= nValue;
		m_S.Y -= nValue;
		m_S.Z -= nValue;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 Vector3::operator * ( float nValue ) const 
	{
		Vector3 newValue;

		newValue.m_S.X = m_S.X * nValue;
		newValue.m_S.Y = m_S.Y * nValue;
		newValue.m_S.Z = m_S.Z * nValue;

		return newValue;
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 &Vector3::operator *= ( float nValue )
	{
		m_S.X *= nValue;
		m_S.Y *= nValue;
		m_S.Z *= nValue;

		return *this;
	}

	//-------------------------------------------------------------------------------------------------
	bool Vector3::operator == ( const Vector3& rOther ) const 
	{
		return ( this->m_S.X == rOther.m_S.X && this->m_S.Y == rOther.m_S.Y && this->m_S.Z == rOther.m_S.Z );
	}

	//-------------------------------------------------------------------------------------------------
	bool Vector3::operator != ( const Vector3& rOther ) const 
	{
		return ( !( rOther == *this ) );
	}

	//-------------------------------------------------------------------------------------------------
	Vector3 &Vector3::operator = ( Vector3& rOther ) 
	{
		if ( rOther == *this ) 
		{
			return *this;
		}

		m_S.X = rOther.m_S.X;
		m_S.Y = rOther.m_S.Y;
		m_S.Z = rOther.m_S.Z;

		return *this;
	}
}
