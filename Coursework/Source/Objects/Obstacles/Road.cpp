#include "Objects/Obstacles/Road.h"

Road::Road()
{

}

Road::~Road()
{

}

bool Road::Load()
{
	if ( !GameObject::Load() )
	{
		return false;
	}

	if ( !m_pBox->IsReady() )
	{
		m_pBox = AABB::Create( m_pProgram, 10.2f, 10.2f, 0.25f );
	}

	return true;
}

void Road::Update( float nDeltaTime )
{
	GameObject::Update( nDeltaTime );

	m_ModelMatrix.Translate( Zeno::Vector3( 0.0f, -0.1f, 0.0f ) );

	m_ModelMatrix.Scale( Zeno::Vector3( 0.01f ) );
}

std::string Road::GetName()
{
	return "Road";
}
