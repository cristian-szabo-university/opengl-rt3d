#include "GameBase.h"
#include "GameState.h"

std::vector< GameBase::Ptr > GameBase::s_vecShareadGames;

GameBase::GameBase( std::string Title )
{
	m_Title = Title;

	m_pEventManager = nullptr;

	m_pWindow = nullptr;
}

GameBase::~GameBase()
{
	
}

bool GameBase::Initialise()
{
	m_pEventManager = new Zeno::EventManager;

	if ( !m_pEventManager )
	{
		return false;
	}

	Zeno::WindowParams WndParams( m_Title );

	WndParams.m_nWidth = 800;
	WndParams.m_nHeight = 600;

	m_pWindow = m_pEventManager->Initialise( &WndParams );

	if ( !m_pWindow )
	{
		return false;
	}

	if ( !m_pWindow->SetupGL( 3, 3 ) )
	{
		return false;
	}

	return true;
}

int GameBase::Execute()
{
	Zeno::Timer WndTimer;

	float nLastFrameDuration = 0.0f;

	Zeno::WindowMessage WndMessage;

	while ( WndMessage.m_nMessage != WM_QUIT )
	{
		nLastFrameDuration = WndTimer.Difference();

		WndTimer.Start();

		if ( !m_pNextState.expired() )
		{
			m_pNextState.lock()->OnEnter( m_pCurrentState );				

			m_pCurrentState = m_pNextState.lock();

			m_pNextState.reset();
		}

		if ( m_pCurrentState.expired() )
		{
			WndMessage = m_pEventManager->ProcessEvents( true );

			WndTimer.Stop();

			continue;
		}
		else
		{
			if ( m_pCurrentState.lock()->OnEvent( &WndMessage ) )
			{
				m_pCurrentState.lock()->OnUpdate( nLastFrameDuration );

				m_pCurrentState.lock()->OnRender( m_pWindow );
			}
		}

		if ( !m_pNextState.expired() )
		{
			if ( !m_pCurrentState.expired() )
			{
				m_pCurrentState.lock()->OnLeave( m_pNextState );
			}
		}

		WndMessage = m_pEventManager->ProcessEvents( true );

		WndTimer.Stop();
	}

	return WndMessage.m_nMessage;
}

void GameBase::Terminate()
{
	m_pCurrentState.reset();

	m_pNextState.reset();

	m_vecStates.clear();

	for ( auto iterGame = s_vecShareadGames.begin();
		iterGame != s_vecShareadGames.end();
		iterGame++ )
	{
		GameBase::Ptr pGame = *iterGame;

		if ( pGame.get() == this )
		{
			iterGame = s_vecShareadGames.erase( iterGame );

			if ( iterGame == s_vecShareadGames.end() )
			{
				break;
			}
		}
	}

	if ( m_pEventManager )
	{
		m_pEventManager->Terminate();
	
		delete m_pEventManager;
	}
}

void GameBase::AttachState( GameState::Ptr pState )
{
	GameBase::Ptr pFoundGame;

	for ( auto iterGame = s_vecShareadGames.begin();
		iterGame != s_vecShareadGames.end();
		iterGame++ )
	{
		GameBase::Ptr pGame = *iterGame;

		if ( pGame.get() == this )
		{
			pFoundGame = pGame;
		}
	}

	if ( pState->OnInitialise( std::weak_ptr< GameBase >( pFoundGame ) ) )
	{
		m_vecStates.push_back( pState );
	}

	
}

void GameBase::AttachProgram( Zeno::Program::Ptr pProgram )
{
	if ( pProgram.get() && pProgram->IsReady() )
	{
		m_vecPrograms.push_back( pProgram );
	}
}

void GameBase::AttachTexture( Zeno::Texture::Ptr pTexture )
{
	if ( pTexture.get() && pTexture->IsReady() )
	{
		m_vecTextures.push_back( pTexture );
	}
}

void GameBase::AttachFont( Font::Ptr pFont )
{
	if ( pFont.get() && pFont->IsReady() )
	{
		m_vecFonts.push_back( pFont );
	}
}

GameState::Ptr GameBase::PeekState()
{
	if ( !m_pNextState.expired() )
	{
		return m_pNextState.lock();
	}

	return m_pCurrentState.lock();
}

void GameBase::ChangeState( std::string Name )
{
	for ( auto iterState = m_vecStates.begin();
		iterState != m_vecStates.end();
		iterState++ )
	{
		GameState::Ptr pState = ( *iterState );

		if ( pState->GetName() == Name )
		{
			m_pNextState = pState;

			break;
		}
	}
}

Zeno::Program::Ptr GameBase::GetProgram( std::string Name )
{
	for ( auto iterProgram = m_vecPrograms.begin();
		iterProgram != m_vecPrograms.end();
		iterProgram++ )
	{
		if ( ( *iterProgram )->GetName().find( Name ) != std::string::npos )
		{
			return *iterProgram;
		}
	}

	return Zeno::Program::s_kDefault;
}

Zeno::Texture::Ptr GameBase::GetTexture( std::string Name )
{
	for ( auto iterTexture = m_vecTextures.begin();
		iterTexture != m_vecTextures.end();
		iterTexture++ )
	{
		if ( ( *iterTexture )->GetName().find( Name ) != std::string::npos )
		{
			return *iterTexture;
		}
	}

	return Zeno::Texture::s_kDefault;
}

Font::Ptr GameBase::GetFont( std::string Name )
{
	for ( auto iterFont = m_vecFonts.begin();
		iterFont != m_vecFonts.end();
		iterFont++ )
	{
		if ( ( *iterFont )->GetName().find( Name ) != std::string::npos )
		{
			return *iterFont;
		}
	}

	return Font::s_kDefault;
}

GameBase::Ptr GameBase::Create( std::string Title )
{
	GameBase::Ptr pGame( new GameBase( Title ) );

	s_vecShareadGames.push_back( pGame );

	return pGame;
}
