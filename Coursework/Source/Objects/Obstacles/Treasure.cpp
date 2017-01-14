#include "Objects/Obstacles/Treasure.h"

Treasure::Treasure()
{

}

Treasure::~Treasure()
{

}

bool Treasure::Load()
{
	if ( !GameObject::Load() )
	{
		return false;
	}

	if ( !m_pBox->IsReady() )
	{
		m_pBox = AABB::Create( m_pProgram, 1.2f, 1.2f, 1.2f );
	}

	m_nAngle = 0.0f;

	return true;
}

void Treasure::Update( float nDeltaTime )
{
	m_nAngle += 1.0f;

	if ( m_nAngle > 360.0f )
	{
		m_nAngle -= 360.0f;
	}

	GameObject::Update( nDeltaTime );	

	m_ModelMatrix.Rotate( m_nAngle, Zeno::Vector3( 0.0f, 1.0, 0.0f ) );

	m_ModelMatrix.Rotate( 60.0f, Zeno::Vector3( -1.0f, 0.0, 0.0f ) );

	m_ModelMatrix.Scale( Zeno::Vector3( 0.5f ) );
}

std::string Treasure::GetName()
{
	return "Treasure";
}
