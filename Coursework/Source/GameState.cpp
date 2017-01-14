#include "GameState.h"

GameState::~GameState()
{

}

bool GameState::OnInitialise( std::weak_ptr< GameBase > pGame )
{
	return true;
}

void GameState::OnEnter( std::weak_ptr< GameState > pOldState )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
}

void GameState::OnLeave( std::weak_ptr< GameState > pNewState )
{
	
}

void GameState::OnUpdate( float nDeltaTime )
{
	
}

void GameState::OnRender( Zeno::Window* pWindow )
{
	glClear( GL_COLOR_BUFFER_BIT );

	pWindow->Present();
}

bool GameState::OnEvent( Zeno::WindowMessage* pMessage )
{
	switch ( pMessage->m_nMessage )
	{
	case WM_KEYDOWN:
		{
			switch ( pMessage->m_wParam )
			{
			case VK_ESCAPE:
				{
					PostQuitMessage( 0 );

					return false;
				}
				break;

			}
		}
		break;

	}

	return true;
}

void GameState::OnTerminate()
{

}
