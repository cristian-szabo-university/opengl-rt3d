#include "Objects/Vehicles/Car.h"

#include <iostream>

Car::Car()
{

}

Car::~Car()
{

}

bool Car::Load()
{
	if ( !GameObject::Load() )
	{
		return false;
	}

	if ( !m_pBox->IsReady() )
	{
		m_pBox = AABB::Create( m_pProgram, 4.5f, 2.0f, 1.5f );
	}

	m_nElapsedTime = 0;

	return true;
}

void Car::Update( float nDeltaTime )
{
	m_nElapsedTime += nDeltaTime;

	GameObject::Update( nDeltaTime );

	Move( 0.1f, Zeno::Vector3( 0.0f, 0.0f, 1.0f ) );

	if ( m_pBox->GetPosition().m_S.Z > 20 )
	{
		Move( -46.0f, Zeno::Vector3( 0.0f, 0.0f, 1.0f ) );
	}

	m_ModelMatrix.Translate( Zeno::Vector3( 0.0f, -0.5f, 0.0f ) );

	m_ModelMatrix.Rotate( 90.0f, Zeno::Vector3( 0.0f, 1.0f, 0.0f ) );

	m_ModelMatrix.Scale( Zeno::Vector3( 0.015f ) );

	irrklang::vec3df ikPos( m_pBox->GetPosition().m_S.X, 
		m_pBox->GetPosition().m_S.Y, m_pBox->GetPosition().m_S.Z );

	m_pSound->setPosition( ikPos );

	bool bPaused = m_pSound->getIsPaused();

	if ( m_nElapsedTime > 3.0f )
	{
		if ( bPaused )
		{
			m_pSound->setIsPaused( false );				
		}
		else
		{
			m_pSound->setIsPaused( true );
		}

		m_nElapsedTime = 0.0f;
	}
}

std::string Car::GetName()
{
	return "Vehicle";
}