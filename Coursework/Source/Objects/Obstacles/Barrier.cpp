#include "Objects/Obstacles/Barrier.h"

Barrier::Barrier()
{

}

Barrier::~Barrier()
{

}

bool Barrier::Load()
{
	if ( !GameObject::Load() )
	{
		return false;
	}

	if ( !m_pBox->IsReady() )
	{
		m_pBox = AABB::Create( m_pProgram, 0.6f, 1.8f, 1.1f );
	}

	return true;
}

void Barrier::Update( float nDeltaTime )
{
	GameObject::Update( nDeltaTime );

	m_ModelMatrix.Translate( Zeno::Vector3( 0.0f, -0.6f, 0.0f ) );

	m_ModelMatrix.Rotate( 90.0f, Zeno::Vector3( -1.0f, 0.0f, 0.0f ) );

	m_ModelMatrix.Scale( Zeno::Vector3( 0.023f ) );
}

std::string Barrier::GetName()
{
	return "Barrier";
}
