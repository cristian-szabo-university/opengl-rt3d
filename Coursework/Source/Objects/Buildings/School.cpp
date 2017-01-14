#include "Objects/Buildings/School.h"

School::School()
{

}

School::~School()
{

}

bool School::Load()
{
	if ( !GameObject::Load() )
	{
		return false;
	}

	if ( !m_pBox->IsReady() )
	{
		m_pBox = AABB::Create( m_pProgram, 20.0f, 20.0f, 22.0f );
	}

	return true;
}

void School::Update( float nDeltaTime )
{
	GameObject::Update( nDeltaTime );

	m_ModelMatrix.Translate( Zeno::Vector3( 0.0f, 0.0f, 10.0f ) );

	m_ModelMatrix.Scale( Zeno::Vector3( 0.01f ) );
}

std::string School::GetName()
{
	return "Building";
}
