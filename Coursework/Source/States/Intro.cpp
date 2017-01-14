#include "States/Intro.h"

Intro::Intro()
{

}

Intro::~Intro()
{

}

std::string Intro::GetName()
{
	return "Intro";
}

bool Intro::OnInitialise( std::weak_ptr< GameBase > pGame )
{
	if ( pGame.expired() )
	{
		return false;
	}

	m_pContext = pGame;

	Zeno::Program::Ptr pFontProgram = m_pContext.lock()->GetProgram( "font.frag" );

	Zeno::Program::Ptr pTextureProgram = m_pContext.lock()->GetProgram( "texture.frag" );

	m_pFont = m_pContext.lock()->GetFont( "mavenpro-regular.ttf" );

	m_pBackground = Layer::Create( pTextureProgram, m_pContext.lock()->GetTexture( "intro-bg.png" ) );

	m_pLogo = Layer::Create( pTextureProgram, m_pContext.lock()->GetTexture( "logo.png" ) );

	return true;
}

void Intro::OnEnter( std::weak_ptr< GameState > pOldState )
{
	// Enable Transparency
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Background color
	glClearColor( 0.7f, 0.7f, 0.7f, 1.0f );

	m_nElapsedTime = 0.0f;
}

void Intro::OnLeave( std::weak_ptr< GameState > pNewState )
{
	// Disable transparency
	glDisable( GL_BLEND );

	m_nElapsedTime = 0.0f;
}

void Intro::OnUpdate( float nDeltaTime )
{
	m_nElapsedTime += nDeltaTime;

	/*
		Change state to menu
	*/
	if ( m_nElapsedTime > 3.0f )
	{
		if ( !m_pContext.expired() )
		{
			m_pContext.lock()->ChangeState( "Menu" );
		}
	}
}

void Intro::OnRender( Zeno::Window* pWindow )
{
	glClear( GL_COLOR_BUFFER_BIT );

	/*
		Render background texture
	*/
	m_pBackground->Draw( Zeno::Vector3( 0.0f ) );

	/*
		Render logo
	*/
	m_pLogo->Draw( Zeno::Vector3( 250.0f, 110.0f, 0.0f ), 0.3f );

	/*
		Render title text
	*/
	m_pFont->Draw( "Urban Cityscape", 
		Zeno::Vector3( 90.0f, 480.0f, 0.0f ), 0.6f );

	/*
		Render sub-title text
	*/
	m_pFont->Draw( "Press SPACE key to continue ...", 
		Zeno::Vector3( 200.0f, 50.0f, 0.0f ), 0.2f );

	pWindow->Present();
}

bool Intro::OnEvent( Zeno::WindowMessage* pMessage )
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
