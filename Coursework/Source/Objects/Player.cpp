#include "Objects/Player.h"

#include "Zeno/Interface/EventManager.h"

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Load()
{
	if ( !GameObject::Load() )
	{
		return false;
	}

	m_State = PLAYER_STATE_INVALID;

	ChangeState( PLAYER_STATE_STAND );

	if ( !m_pBox->IsReady() )
	{
		m_pBox = AABB::Create( m_pProgram, 1.7f, 1.7f, 1.7f );
	}

	m_nHorizontalAngle = 180.0f;

	m_nVerticalAngle = 0.0f;

	return true;
}

void Player::Update( float nDeltaTime )
{
	if ( KEY_DOWN( VK_KEYW ) || KEY_DOWN( VK_KEYS ) || 
		KEY_DOWN( VK_KEYA ) || KEY_DOWN( VK_KEYD ) )
	{
		ChangeState( PLAYER_STATE_WALK );
	}
	else
	{
		ChangeState( PLAYER_STATE_STAND );
	}

	if ( KEY_DOWN( VK_KEYQ ) )
	{
		m_nHorizontalAngle += 2.0f;
	}
	else if ( KEY_DOWN( VK_KEYE ) )
	{
		m_nHorizontalAngle -= 2.0f;
	}

	float nHorizAngleRad = m_nHorizontalAngle * ( 3.14f / 180.0f );
	float nVertAngleRad = m_nVerticalAngle * ( 3.14f / 180.0f );

	Zeno::Vector3 Direction( cos( nVertAngleRad ) * sin( nHorizAngleRad ), 
		sin( nVertAngleRad ), cos( nVertAngleRad ) * cos( nHorizAngleRad ) );

	Zeno::Vector3 Right( sin( nHorizAngleRad - 3.14f / 2.0f ), 
		0, cos( nVertAngleRad - 3.14f / 2.0f ) );

	Zeno::Vector3 Up = Right.Cross( Direction );

	GameObject::Update( nDeltaTime / 2.0f );

	if ( KEY_DOWN( VK_KEYW ) )
	{
		m_nSpeed = 0.06f;

		m_Velocity = Direction;

		m_nViewAngle = 90.0f;
	}
	else if ( KEY_DOWN( VK_KEYS ) )
	{
		m_nSpeed = -0.06f;

		m_Velocity = Direction;

		m_nViewAngle = 270.0f;
	}
	else if ( KEY_DOWN( VK_KEYA ) )
	{
		m_nSpeed = -0.06f;

		m_Velocity = Right;

		m_nViewAngle = 180.0f;
	}
	else if ( KEY_DOWN( VK_KEYD ) )
	{
		m_nSpeed = 0.06f;

		m_Velocity = Right;

		m_nViewAngle = 0.0f;
	}
	else
	{
		m_nSpeed = 0.0f;

		m_Velocity.Set( 0.0f, 0.0f, 0.0f );
	}

	Move( m_nSpeed, m_Velocity );

	m_ModelMatrix.Translate( Zeno::Vector3( 0.0f, 0.5f, 0.0f ) );

	m_ModelMatrix.Rotate( m_nViewAngle, Zeno::Vector3( 0.0f, 1.0f, 0.0f ) );	

	m_ModelMatrix.Rotate( 90.0f, Zeno::Vector3( -1.0f, 0.0f, 0.0f ) );	

	m_ModelMatrix.Scale( Zeno::Vector3( 0.045f ) );

	Zeno::Matrix4 ViewMatrix;

	Zeno::Vector3 Position = m_pBox->GetPosition();

	Position.m_S.X += m_pBox->GetWidth() / 2.0f;
	Position.m_S.Y += m_pBox->GetHeight() * 1.5f;
	Position.m_S.Z += m_pBox->GetLength() * 1.5f;

	Direction.m_S.Y -= 0.5f;

	ViewMatrix.LookAt( Position, Position + Direction, Up );

	m_pProgram->GetVariable( "ViewMatrix" )->UpdateMatrix( ViewMatrix );
}

void Player::ChangeState( PlayerStateType NewState )
{
	if ( NewState == m_State )
	{
		return;
	}

	if ( NewState == PLAYER_STATE_STAND )
	{
		m_pModel->SetAnim( 0 );
	}
	else if ( NewState == PLAYER_STATE_WALK )
	{
		m_pModel->SetAnim( 1 );
	}

	m_State = NewState;
}

std::string Player::GetName()
{
	return "Player";
}

void Player::StepBack()
{
	Move( -m_nSpeed, m_Velocity );
}
