#include "States/End.h"

End::End()
{

}

End::~End()
{

}

std::string End::GetName()
{
	return "End";
}

bool End::OnInitialise( std::weak_ptr< GameBase > pGame )
{
	if ( pGame.expired() )
	{
		return false;
	}

	m_pContext = pGame;

	Zeno::Program::Ptr pFontProgram = m_pContext.lock()->GetProgram( "font.frag" );

	Zeno::Program::Ptr pTextureProgram = m_pContext.lock()->GetProgram( "texture.frag" );

	m_pFont = m_pContext.lock()->GetFont( "mavenpro-regular.ttf" );

	m_pBackground = Layer::Create( pTextureProgram, m_pContext.lock()->GetTexture( "end-bg.png" ) );

	m_nTotalScore = 0;

	return true;
}

void End::OnEnter( std::weak_ptr< GameState > pOldState )
{
	// Enable Transparency
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Background color
	glClearColor( 0.7f, 0.7f, 0.7f, 1.0f );
}

void End::OnLeave( std::weak_ptr< GameState > pNewState )
{
	// Disable transparency
	glDisable( GL_BLEND );

	m_nTotalScore = 0;
}

void End::OnRender( Zeno::Window* pWindow )
{
	glClear( GL_COLOR_BUFFER_BIT );

	/*
		Render background texture
	*/
	m_pBackground->Draw( Zeno::Vector3( 0.0f ) );

	/*
		Render title text
	*/
	if ( m_Type == GAME_OVER_HIT_BY_CAR )
	{
		m_pFont->Draw( "Defeat", 
			Zeno::Vector3( 260.0f, 480.0f, 0.0f ), 0.6f );

		m_pFont->Draw( "You were hit by a car. Try again!", 	
			Zeno::Vector3( 90.0f, 300.0f, 0.0f ), 0.3f );
	}
	else
	{
		if (  m_Type == GAME_OVER_VICTORY )
		{
			m_pFont->Draw( "Victory", 
				Zeno::Vector3( 260.0f, 480.0f, 0.0f ), 0.6f );

			m_pFont->Draw( "You have collected all the coins!", 	
				Zeno::Vector3( 100.0f, 300.0f, 0.0f ), 0.3f );
		}
		else
		{
			m_pFont->Draw( "Draw", 
				Zeno::Vector3( 310.0f, 480.0f, 0.0f ), 0.6f );

			m_pFont->Draw( "Your score is " + 
				std::to_string( m_nTotalScore ) + " points.", 	
				Zeno::Vector3( 180.0f, 300.0f, 0.0f ), 0.3f );
		}				
	}

	/*
		Render sub-title text
	*/
	m_pFont->Draw( "Press SPACE key to continue ...", 
		Zeno::Vector3( 200.0f, 50.0f, 0.0f ), 0.2f );

	pWindow->Present();
}

bool End::OnEvent( Zeno::WindowMessage* pMessage )
{
	switch ( pMessage->m_nMessage )
	{
	case WM_KEYDOWN:
		{
			switch ( pMessage->m_wParam )
			{
			case VK_SPACE:
				{
					if ( !m_pContext.expired() )
					{
						m_pContext.lock()->ChangeState( "Menu" );
					}
				}
				break;

			}
		}
		break;

	}

	return true;
}

void End::SetScore( int nValue )
{
	m_nTotalScore = nValue;
}

void End::SetStatus( GameOverType Type )
{
	m_Type = Type;
}
