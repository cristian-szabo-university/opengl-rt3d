#include "Objects/Vehicles/Police.h"

Police::Police()
{

}

Police::~Police()
{

}

bool Police::Load()
{
	if ( !GameObject::Load() )
	{
		return false;
	}

	m_nElapsedTime = 3.0f;

	if ( !m_pBox->IsReady() )
	{
		m_pBox = AABB::Create( m_pProgram, 4.0f, 2.0f, 1.8f );
	}

	return true;
}

void Police::Update( float nDeltaTime )
{
	m_nElapsedTime += nDeltaTime;

	GameObject::Update( nDeltaTime );

	Move( 0.08f, Zeno::Vector3( 0.0f, 0.0f, -1.0f ) );
	
	if ( m_pBox->GetPosition().m_S.Z < -26.0f )
	{
		Move( 45.0f, Zeno::Vector3( 0.0f, 0.0f, 1.0f ) );
	}

	m_ModelMatrix.Translate( Zeno::Vector3( 0.0f, -0.8f, 0.0f ) );

	m_ModelMatrix.Rotate( 90.0f, Zeno::Vector3( 0.0f, 1.0f, 0.0f ) );

	m_ModelMatrix.Scale( Zeno::Vector3( 0.035f ) );

	irrklang::vec3df ikPos( m_pBox->GetPosition().m_S.X, 
		m_pBox->GetPosition().m_S.Y, m_pBox->GetPosition().m_S.Z );

	m_pSound->setPosition( ikPos );

	bool bPaused = m_pSound->getIsPaused();

	if ( m_nElapsedTime > 4.0f )
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

std::string Police::GetName()
{
	return "Vehicle";
}