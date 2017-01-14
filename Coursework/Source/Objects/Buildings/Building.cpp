#include "Objects/Buildings/Building.h"

Building::Building()
{

}

Building::~Building()
{

}

bool Building::Load()
{
	if ( !GameObject::Load() )
	{
		return false;
	}

	if ( !m_pBox->IsReady() )
	{
		m_pBox = AABB::Create( m_pProgram, 13.0f, 12.0f, 16.0f );
	}

	return true;
}

void Building::Update( float nDeltaTime )
{
	GameObject::Update( nDeltaTime );

	m_ModelMatrix.Translate( Zeno::Vector3( 0.0f, 0.0f, 6.0f ) );

	m_ModelMatrix.Scale( Zeno::Vector3( 0.006f ) );
}

std::string Building::GetName()
{
	return "Building";
}
