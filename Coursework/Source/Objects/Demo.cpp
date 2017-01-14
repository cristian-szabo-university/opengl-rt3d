#include "Objects/Demo.h"

#include "Zeno/Interface/EventManager.h"

Demo::Demo()
{

}

Demo::~Demo()
{

}

bool Demo::Load()
{
	if ( !GameObject::Load() )
	{
		return false;
	}

	if ( !m_pBox->IsReady() )
	{
		m_pBox = AABB::Create( m_pProgram, 1.7f, 1.7f, 1.7f );
	}

	m_pModel->SetAnim( 0 );

	m_nViewAngle = 0.0f;

	return true;
}

void Demo::Update( float nDeltaTime )
{
	m_nViewAngle += 1.0f;

	if ( m_nViewAngle > 360.0f )
	{
		m_nViewAngle -= 360.0f;
	}

	GameObject::Update( nDeltaTime );

	m_ModelMatrix.Translate( Zeno::Vector3( 0.0f, 0.3f, 0.0f ) );

	m_ModelMatrix.Rotate( m_nViewAngle, Zeno::Vector3( 0.0f, 1.0f, 0.0f ) );

	m_ModelMatrix.Rotate( 90.0f, Zeno::Vector3( -1.0f, 0.0f, 0.0f ) );	

	m_ModelMatrix.Scale( Zeno::Vector3( 0.045f ) );

	Zeno::Matrix4 ViewMatrix;

	ViewMatrix.LookAt( Zeno::Vector3( 3.35f, 2.25f, 2.0f ), 
		Zeno::Vector3( 0.0f, 1.25f, 1.0f ), 
		Zeno::Vector3( 0.0f, 1.0f, 0.0f ) );

	m_pProgram->GetVariable( "ViewMatrix" )->UpdateMatrix( ViewMatrix );
}

std::string Demo::GetName()
{
	return "Demo";
}
