#include <Windowsx.h>

#include "States/Menu.h"
#include "States/Select.h"

Menu::Menu()
{

}

Menu::~Menu()
{

}

std::string Menu::GetName()
{
	return "Menu";
}

bool Menu::OnInitialise( std::weak_ptr< GameBase > pGame )
{
	if ( pGame.expired() )
	{
		return false;
	}

	m_pContext = pGame;

	Zeno::Program::Ptr pFontProgram = m_pContext.lock()->GetProgram( "font.frag" );

	Zeno::Program::Ptr pTextureProgram = m_pContext.lock()->GetProgram( "texture.frag" );

	m_pFont = m_pContext.lock()->GetFont( "mavenpro-regular.ttf" );

	Zeno::Texture::Ptr pTexture = m_pContext.lock()->GetTexture( "ui-button.png" );

	m_pBackground = Layer::Create( pTextureProgram, m_pContext.lock()->GetTexture( "menu-bg.png" ) );

	if ( !m_pBackground->IsReady() )
	{
		return false;
	}

	m_vecButtons.resize( BUTTON_MENU_COUNT );

	std::string ButtonText[ BUTTON_MENU_COUNT ] = 
	{
		"START",
		"QUIT"
	};

	for ( GLuint nBtnIdx = 0; nBtnIdx < BUTTON_MENU_COUNT; nBtnIdx++ )
	{
		m_vecButtons[ nBtnIdx ] = Button::Create( 
			pTextureProgram, m_pFont, pTexture,
			ButtonText[ nBtnIdx ] );

		if ( !m_vecButtons[ nBtnIdx ]->IsReady() )
		{
			return false;
		}
	}

	return true;
}

void Menu::OnEnter( std::weak_ptr< GameState > pOldState )
{
	// Enable Transparency
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Background color
	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
}

void Menu::OnLeave( std::weak_ptr< GameState > pNewState )
{
	// Disable transparency
	glDisable( GL_BLEND );

	if ( !pNewState.expired() )
	{
		GameState::Ptr pState = pNewState.lock();

		if ( pState->GetName() == "Select" )
		{
			std::shared_ptr< Select > pCastState = std::static_pointer_cast< Select >( pState );

			if ( !pCastState->OnLoad() )
			{
				PostQuitMessage( 0 );
			}
		}
	}
}

void Menu::OnRender( Zeno::Window* pWindow )
{
	glClear( GL_COLOR_BUFFER_BIT );
	
	/*
		Render background texture
	*/
	m_pBackground->Draw( Zeno::Vector3( 0.0f ) );

	/*
		The pre-rendered screen before changing the state
	*/
	if ( !m_pContext.expired() )
	{
		if ( m_pContext.lock()->PeekState()->GetName() != GetName() )
		{
			/*
				Render title text
			*/
			m_pFont->Draw( "Loading", Zeno::Vector3( 250.0f, 480.0f, 0.0f ), 0.6f );

			/*
				Render sub-title text
			*/
			m_pFont->Draw( "Please wait for the game to be ready ...",
				Zeno::Vector3( 150.0f, 50.0f, 0.0f ), 0.2f );

		}
		else
		{		
			/*
				Render buttons
			*/
			Zeno::Vector3 Position( 280.0f, 300.0f, 0.0f );

			for ( size_t nBtnIdx = 0; nBtnIdx < m_vecButtons.size(); nBtnIdx++ )
			{
				Button::Ptr pButton = m_vecButtons[ nBtnIdx ];

				pButton->Draw( Position );

				Position.m_S.Y -= 100;
			}
			
			/*
				Render title text
			*/
			m_pFont->Draw( "Main Menu", Zeno::Vector3( 200.0f, 480.0f, 0.0f ), 0.6f );
		}
	}

	pWindow->Present();
}

bool Menu::OnEvent( Zeno::WindowMessage* pMessage )
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
						m_pContext.lock()->ChangeState( "Select" );
					}
				}
				break;

			case VK_F1:
				{
					if ( !m_pContext.expired() )
					{
						m_pContext.lock()->ChangeState( "Help" );
					}
				};

			case VK_ESCAPE:
				{
					PostQuitMessage( 0 );

					return false;
				}
				break;

			}
		}
		break;

	case WM_LBUTTONDOWN:
		{
			int nMousePosX = GET_X_LPARAM( pMessage->m_lParam );
			int nMousePosY = pMessage->m_pWindow->GetHeight() - GET_Y_LPARAM( pMessage->m_lParam );

			if ( m_vecButtons[ BUTTON_MENU_START ]->OnClick( nMousePosX, nMousePosY ) )
			{
				if ( !m_pContext.expired() )
				{
					m_pContext.lock()->ChangeState( "Select" );
				}
			}

			if ( m_vecButtons[ BUTTON_MENU_EXIT ]->OnClick( nMousePosX, nMousePosY ) )
			{
				PostQuitMessage( 0 );

				return false;
			}
		}
		break;

	}

	return true;
}
