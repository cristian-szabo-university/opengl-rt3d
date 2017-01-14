#include "GameObject.h"

const GameObject::Ptr GameObject::s_kDefault = GameObject::Ptr( new GameObject );

GameObject::GameObject()
{
	m_pSound = nullptr;

	m_pBox = nullptr;

	Clear();
}

GameObject::~GameObject()
{
	Clear();
}

bool GameObject::SetProgram( Zeno::Program::Ptr pProgram )
{
	if ( !pProgram.get() || m_pProgram->IsReady() )
	{
		return false;
	}

	m_pProgram = pProgram;

	return true;
}

bool GameObject::SetModel( Zeno::Model::Ptr pModel )
{
	if ( !pModel.get() || m_pModel->IsReady() )
	{
		return false;
	}

	m_pModel = pModel;

	return true;
}

bool GameObject::SetAABB( AABB::Ptr pBox )
{
	if ( !pBox.get() || m_pBox->IsReady() )
	{
		return false;
	}

	m_pBox = pBox;

	return true;
}

bool GameObject::SetSound( irrklang::ISound* pSound )
{
	if ( !pSound || m_pSound )
	{
		return false;
	}

	m_pSound = pSound;

	return true;
}

bool GameObject::Load()
{
	if ( m_bReady )
	{
		return false;
	}

	if ( !m_pProgram->IsReady() )
	{
		return false;
	}

	if ( !m_pModel->IsReady() )
	{
		return false;
	}

	m_bReady = true;

	return true;
}

bool GameObject::Draw()
{
	if ( !m_bReady )
	{
		return false;
	}
	
	m_pProgram->GetVariable( "ModelMatrix" )->UpdateMatrix( m_ModelMatrix );

	if ( !m_pModel->Draw() )
	{
		return false;
	}

	if ( m_bDrawAABB )
	{
		if ( m_pBox->IsReady() )
		{
			m_pBox->Draw();
		}
	}

	m_ModelMatrix.Identity();

	return true;
}

void GameObject::Update( float nDeltaTime )
{
	m_pModel->Update( nDeltaTime );

	m_ModelMatrix.Translate( m_pBox->GetPosition() );

	m_ModelMatrix.Translate( m_pBox->GetCenter() );
}

void GameObject::Event( Zeno::WindowMessage* pMessage )
{

}

bool GameObject::IsReady()
{
	return m_bReady;
}

void GameObject::Clear()
{
	m_bReady = false;

	m_bDrawAABB = false;

	m_pProgram = Zeno::Program::s_kDefault;

	m_pModel = Zeno::Model::s_kDefault;

	m_ModelMatrix.Identity();

	m_pBox = AABB::s_kDefault;

	if ( m_pSound )
	{
		m_pSound->drop();

		m_pSound = nullptr;
	}
}

bool GameObject::Move( float nSpeed, Zeno::Vector3 Axis )
{
	if ( !m_pBox->IsReady() )
	{
		return false;
	}

	m_pBox->Move( nSpeed, Axis );

	return true;
}

bool GameObject::CheckCollision( GameObject::Ptr pOther )
{
	if ( !m_pBox->IsReady() )
	{
		return false;
	}

	return m_pBox->CheckCollision( pOther->m_pBox );
}

void GameObject::ToggleAABB()
{
	m_bDrawAABB = !m_bDrawAABB;
}

std::string GameObject::GetName()
{
	return "Unknown";
}

Zeno::Vector3 GameObject::GetPosition()
{
	return m_pBox->GetPosition();
}