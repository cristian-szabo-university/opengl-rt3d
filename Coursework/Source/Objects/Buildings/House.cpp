#include "Objects/Buildings/House.h"

House::House()
{

}

House::~House()
{

}

bool House::Load()
{
	if ( !GameObject::Load() )
	{
		return false;
	}

	if ( !m_pBox->IsReady() )
	{
		m_pBox = AABB::Create( m_pProgram, 17.0f, 6.0f, 12.0f );
	}

	return true;
}

void House::Update( float nDeltaTime )
{
	GameObject::Update( nDeltaTime );

	m_ModelMatrix.Translate( Zeno::Vector3( 2.5f, -0.5f, 2.5f ) );

	m_ModelMatrix.Rotate( 90.0f, Zeno::Vector3( 0.0f, 1.0f, 0.0f ) );

	m_ModelMatrix.Scale( Zeno::Vector3( 0.006f ) );
}

std::string House::GetName()
{
	return "Building";
}
