#include <Windowsx.h>

#include "States/Select.h"
#include "States/Level.h"

Select::Select()
{

}

Select::~Select()
{

}

std::string Select::GetName()
{
	return "Select";
}

bool Select::OnInitialise( std::weak_ptr< GameBase > pGame )
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

	m_pBackground = Layer::Create( pTextureProgram, m_pContext.lock()->GetTexture( "select-bg.png" ) );

	if ( !m_pBackground->IsReady() )
	{
		return false;
	}

	m_vecButtons.resize( BUTTON_SELECT_COUNT );

	std::string ButtonText[ BUTTON_SELECT_COUNT ] = 
	{
		"NEXT",
		"GO"
	};

	for ( GLuint nBtnIdx = 0; nBtnIdx < BUTTON_SELECT_COUNT; nBtnIdx++ )
	{
		m_vecButtons[ nBtnIdx ] = Button::Create( 
			pTextureProgram, m_pFont, pTexture,
			ButtonText[ nBtnIdx ] );

		if ( !m_vecButtons[ nBtnIdx ]->IsReady() )
		{
			return false;
		}
	}

	m_bLoaded = false;

	return true;
}

void Select::OnEnter( std::weak_ptr< GameState > pOldState )
{
	// Enable Transparency
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Enable Z-buffer
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	// Background color
	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
	glClearDepth( 1.0f );

	m_nSelectModel = 0;

	m_pDemo = GameObject::Create< Demo >( m_pContext.lock()->GetProgram( "phong.frag" ), 
		m_vecModels[ 0 ], Zeno::Vector3( -0.5f, -0.2f, 0.9f ) );
}

void Select::OnLeave( std::weak_ptr< GameState > pNewState )
{
	// Disable Z-buffer
	glDisable( GL_DEPTH_TEST );

	// Disable transparency
	glDisable( GL_BLEND );

	if ( !pNewState.expired() )
	{
		GameState::Ptr pState = pNewState.lock();

		if ( pState->GetName() == "Level" )
		{
			std::shared_ptr< Level > pCastState = std::static_pointer_cast< Level >( pState );

			if ( !pCastState->OnLoad() )
			{
				PostQuitMessage( 0 );
			}
		}
	}

	m_pDemo.reset();
}

void Select::OnUpdate( float nDeltaTime )
{
	m_pDemo->Update( nDeltaTime );
}

void Select::OnRender( Zeno::Window* pWindow )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/*
		The pre-rendered screen before changing the state
	*/
	if ( !m_pContext.expired() )
	{
		if ( m_pContext.lock()->PeekState()->GetName() != GetName() )
		{
			glDisable( GL_DEPTH_TEST );

			/*
				Render background texture
			*/
			m_pBackground->Draw( Zeno::Vector3( 0.0f ) );

			/*
				Render title text
			*/
			m_pFont->Draw( "Loading", Zeno::Vector3( 250.0f, 480.0f, 0.0f ), 0.6f );

			/*
				Render sub-title text
			*/
			m_pFont->Draw( "Please wait for the game to be ready ...",
				Zeno::Vector3( 150.0f, 50.0f, 0.0f ), 0.2f );

			glEnable( GL_DEPTH_TEST );
		}
		else
		{
			glDisable( GL_DEPTH_TEST );

			/*
				Render background texture
			*/
			m_pBackground->Draw( Zeno::Vector3( 0.0f ) );

			/*
				Render buttons
			*/
			Zeno::Vector3 Position( 500.0f, 250.0f, 0.0f );
			
			for ( size_t nBtnIdx = 0; nBtnIdx < m_vecButtons.size(); nBtnIdx++ )
			{
				Button::Ptr pButton = m_vecButtons[ nBtnIdx ];

				pButton->Draw( Position );

				Position.m_S.Y -= 100;
			}
			
			/*
				Render title text
			*/
			m_pFont->Draw( "Character Select", Zeno::Vector3( 80.0f, 480.0f, 0.0f ), 0.6f );	

			glEnable( GL_DEPTH_TEST );

			m_pDemo->Draw();
		}
	}

	pWindow->Present();
}

bool Select::OnEvent( Zeno::WindowMessage* pMessage )
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
						m_pContext.lock()->ChangeState( "Level" );
					}
				}
				break;

			case VK_RETURN:
				{
					NextModel();
				}
				break;

			}
		}
		break;

	case WM_LBUTTONDOWN:
		{
			int nMousePosX = GET_X_LPARAM( pMessage->m_lParam );
			int nMousePosY = pMessage->m_pWindow->GetHeight() - GET_Y_LPARAM( pMessage->m_lParam );

			if ( m_vecButtons[ BUTTON_SELECT_NEXT ]->OnClick( nMousePosX, nMousePosY ) )
			{
				NextModel();
			}

			if ( m_vecButtons[ BUTTON_SELECT_GO ]->OnClick( nMousePosX, nMousePosY ) )
			{
				if ( !m_pContext.expired() )
				{
					m_pContext.lock()->ChangeState( "Level" );
				}
			}
		}
		break;

	}

	return true;
}

bool Select::OnLoad()
{
	if ( m_bLoaded )
	{
		return true;
	}

	Zeno::Program::Ptr pPhongProgram = m_pContext.lock()->GetProgram( "phong.frag" );

	if ( !pPhongProgram->IsReady() )
	{
		return false;
	}

	std::string ModelFileStr[3] = 
	{
		"data/models/player/hayden.md2",
		"data/models/player/hueteotl.md2",
		"data/models/player/yoshi.md2"
	};

	std::string ModelTextureStr[3] = 
	{
		"data/textures/hayden.tga",
		"data/textures/hueteotl.tga",
		"data/textures/yoshi.tga"
	};

	for ( int i = 0; i < 3; i++ )
	{
		Zeno::Model::Ptr pPlayerModel = Zeno::Model::Create( pPhongProgram, 
			ModelFileStr[ i ], ModelTextureStr[ i ] );	

		if ( pPlayerModel->IsReady() )
		{
			m_vecModels.push_back( pPlayerModel );
		}
		else
		{
			return false;
		}
	}

	m_bLoaded = true;

	return true;
}

Zeno::Model::Ptr Select::GetModelPlayer()
{
	return m_vecModels.at( m_nSelectModel );
}

void Select::NextModel()
{
	m_nSelectModel += 1;

	if ( m_nSelectModel >= int( m_vecModels.size() ) )
	{
		m_nSelectModel = 0;
	}

	m_pDemo = GameObject::Create< Demo >( m_pContext.lock()->GetProgram( "phong.frag" ), 
		m_vecModels[ m_nSelectModel ], Zeno::Vector3( -0.5f, -0.2f, 0.9f ) );
}
