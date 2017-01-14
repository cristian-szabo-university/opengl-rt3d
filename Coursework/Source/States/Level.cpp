#include "States/Level.h"
#include "States/Select.h"
#include "States/End.h"

#include "Objects/Obstacles/Road.h"
#include "Objects/Obstacles/Barrier.h"
#include "Objects/Obstacles/Treasure.h"

#include "Objects/Vehicles/Car.h"
#include "Objects/Vehicles/Police.h"

#include "Objects/Buildings/Building.h"
#include "Objects/Buildings/House.h"
#include "Objects/Buildings/School.h"

#include "Objects/Player.h"

Level::Level()
{

}

Level::~Level()
{

}

std::string Level::GetName()
{
	return "Level";
}

bool Level::OnInitialise( std::weak_ptr< GameBase > pGame )
{
	m_pContext = pGame;

	m_bLoaded = false;

	irrklang::ISoundDeviceList* pDeviceList = irrklang::createSoundDeviceList();

	if ( !pDeviceList )
	{
		return false;
	}

	const char* pDeviceIndex = pDeviceList->getDeviceID( 0 );

	m_pSoundDevice = irrklang::createIrrKlangDevice(
		irrklang::ESOD_DIRECT_SOUND_8,
		irrklang::ESEO_MULTI_THREADED | irrklang::ESEO_LOAD_PLUGINS | irrklang::ESEO_USE_3D_BUFFERS,
		pDeviceIndex );

	if ( !m_pSoundDevice )
	{
		return false;
	}

	if ( pDeviceList )
	{
		pDeviceList->drop();

		pDeviceList = nullptr;
	}

	Zeno::Program::Ptr pPhongProgram = m_pContext.lock()->GetProgram( "phong.frag" );

	if ( !pPhongProgram->IsReady() )
	{
		return false;
	}

	Zeno::Program::Ptr pFontProgram = m_pContext.lock()->GetProgram( "font.frag" );

	if ( !pFontProgram->IsReady() )
	{
		return false;
	}

	Zeno::Program::Ptr pTextureProgram = m_pContext.lock()->GetProgram( "texture.frag" );

	if ( !pTextureProgram->IsReady() )
	{
		return false;
	}

	std::string SkyboxTextures[] =
	{
		"data/skybox/pr_ft.tga", "data/skybox/pr_bk.tga", 
		"data/skybox/pr_lf.tga", "data/skybox/pr_rt.tga", 
		"data/skybox/pr_up.tga", "data/skybox/pr_dn.tga"
	};
	
	m_pSkybox = Skybox::Create( pPhongProgram, SkyboxTextures, 50.0f );

	if ( !m_pSkybox->IsReady() )
	{
		return false;
	}
	
	m_pFont = m_pContext.lock()->GetFont( "mavenpro-regular.ttf" );

	if ( !m_pFont->IsReady() )
	{
		return false;
	}

	m_pBox = Layer::Create( pTextureProgram, m_pContext.lock()->GetTexture( "ui-box.png" ) );

	if ( !m_pBox->IsReady() )
	{
		return false;
	}

	return true;
}

void Level::OnEnter( std::weak_ptr< GameState > pOldState )
{
	// Enable Transparency
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// Enable Z-buffer
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	// Background color
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glClearDepth( 1.0f );

	glLineWidth( 1.5f );

	m_nTimeLeft = 99;

	m_nGold = 0;

	m_nElapsedTime = 0;

	m_nLastTime = 1;

	m_bLoaded = true;

	m_pSoundDevice->setAllSoundsPaused( false );

	if ( !pOldState.expired() )
	{
		GameState::Ptr pState = pOldState.lock();

		if ( pState->GetName() == "Select" )
		{
			std::shared_ptr< Select > pCastState = std::static_pointer_cast< Select >( pState );

			m_pPlayer = GameObject::Create< Player >( 
				m_pContext.lock()->GetProgram( "phong.frag" ),
				pCastState->GetModelPlayer(),
				Zeno::Vector3( 2.5f, 0.0f, 17.0f ));
		}
	}

	m_pSoundCar = m_pSoundDevice->addSoundSourceFromFile(
		"data/sounds/citycarhorn.mp3", irrklang::ESM_NO_STREAMING, true );

	m_pSoundPolice = m_pSoundDevice->addSoundSourceFromFile(
		"data/sounds/policesiren3.mp3", irrklang::ESM_NO_STREAMING, true );

	m_pSoundBackground = m_pSoundDevice->addSoundSourceFromFile(
		"data/sounds/publictransitbus.mp3", irrklang::ESM_NO_STREAMING, true );

	irrklang::ISound* pSound = m_pSoundDevice->play3D( "data/sounds/publictransitbus.mp3", 
		irrklang::vec3df( 0.0f, 10.0f, 0.0f ), true, false, true );

	pSound->setMinDistance( 20.0f );

	Zeno::Program::Ptr pPhongProgram = m_pContext.lock()->GetProgram( "phong.frag" );

	float nPosZ = 10;

	for ( int nIdx = 0; nIdx < 5; nIdx++ )
	{
		GameObject::Ptr pObject = GameObject::Create< Road >( 
			m_pContext.lock()->GetProgram( "phong.frag" ), 
			m_vecObstacles[0], Zeno::Vector3( 4.0f, 0.0f, nPosZ ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}
		
		pObject = GameObject::Create< Road >( 
			m_pContext.lock()->GetProgram( "phong.frag" ), 
			m_vecObstacles[0], Zeno::Vector3( -6.25f, 0.0f, nPosZ ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}
		
		nPosZ -= 10.25f;
	}

	nPosZ = 19.0f;

	for ( int nIdx = 0; nIdx < 6; nIdx++ )
	{
		GameObject::Ptr pObject = GameObject::Create< Barrier >( 
			pPhongProgram, m_vecObstacles[1], Zeno::Vector3( 12.4f, 0.3f, nPosZ ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		pObject = GameObject::Create< Barrier >( 
			pPhongProgram, m_vecObstacles[1], Zeno::Vector3( -6.2f, 0.3f, nPosZ ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		nPosZ -= 10.0f;
	}
	
	nPosZ = 13.5f;
	
	for ( int nIdx = 0; nIdx < 5; nIdx++ )
	{
		GameObject::Ptr pObject = GameObject::Create< Treasure >( 
			pPhongProgram, m_vecObstacles[2], Zeno::Vector3( 12.4f, 0.7f, nPosZ ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		pObject = GameObject::Create< Treasure >( 
			pPhongProgram, m_vecObstacles[2], Zeno::Vector3( -6.2f, 0.7f, nPosZ ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		nPosZ -= 10.0f;
	}
	
	nPosZ = 15;

	for ( int nIdx = 0; nIdx < 5; nIdx++ )
	{
		GameObject::Ptr	pObject = GameObject::Create< Barrier >( 
			pPhongProgram, m_vecObstacles[1], Zeno::Vector3( 2.0f, 0.3f, nPosZ ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		pObject = GameObject::Create< Barrier >( 
			pPhongProgram, m_vecObstacles[1], Zeno::Vector3( 4.0f, 0.3f, nPosZ ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		nPosZ -= 10.0f;
	}

	nPosZ = -26.0f;

	// Add 2 cars to the first and third line of road
	for ( int nIdx = 0; nIdx < 2; nIdx++ )
	{
		GameObject::Ptr pObject = GameObject::Create< Car >( 
			pPhongProgram, m_vecVehicles[0], Zeno::Vector3( 6.5f, 0.0f, nPosZ ) );

		irrklang::vec3df ikPos( 5.6f, 0.0f, nPosZ );

		irrklang::ISound* pSound = m_pSoundDevice->play3D( 
			m_pSoundCar, ikPos, true, true, true, false );

		pSound->setMinDistance( 1.0f );

		pObject->SetSound( pSound );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}
		
		pObject = GameObject::Create< Car >( 
			pPhongProgram, m_vecVehicles[0], Zeno::Vector3( -0.5f, 0.0f, nPosZ ) );

		ikPos = irrklang::vec3df( -2.6f, 0.0f, nPosZ );

		pSound = m_pSoundDevice->play3D( 
			m_pSoundCar, ikPos, true, true, true, false );

		pSound->setMinDistance( 1.0f );

		pObject->SetSound( pSound );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}
		
		nPosZ += 22;
	}
	
	nPosZ = 20;
	
	// Add 2 police cars to the second and forth line of road
	for ( int nIdx = 0; nIdx < 2; nIdx++ )
	{
		GameObject::Ptr pObject = GameObject::Create< Police >( 
			pPhongProgram, m_vecVehicles[1], Zeno::Vector3( 9.5f, 0.0f, nPosZ ) );
		
		irrklang::vec3df ikPos( 5.6f, 0.0f, nPosZ );

		irrklang::ISound* pSound = m_pSoundDevice->play3D( 
			m_pSoundPolice, ikPos, true, true, true, false );

		pSound->setIsPaused( true );

		pSound->setMinDistance( 1.0f );

		pObject->SetSound( pSound );
		
		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		pObject = GameObject::Create< Police >( 
			pPhongProgram, m_vecVehicles[1], Zeno::Vector3( -3.5f, 0.0f, nPosZ ) );
		
		ikPos = irrklang::vec3df( -5.6f, 0.0f, nPosZ );

		pSound = m_pSoundDevice->play3D( 
			m_pSoundPolice, ikPos, true, true, true, false );

		pSound->setMinDistance( 1.0f );

		pObject->SetSound( pSound );
		
		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		nPosZ -= 20;
	}

	nPosZ = -35.0f;

	for ( int nIdx = 0; nIdx < 2; nIdx++ )
	{
		GameObject::Ptr pObject = GameObject::Create< Building >( 
			pPhongProgram, m_vecBuildings[0], Zeno::Vector3( 14.5f, 0.0f, nPosZ ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		pObject = GameObject::Create< House >( 
			pPhongProgram, m_vecBuildings[1], Zeno::Vector3( 14.0f, 0.0f, nPosZ + 13.0f) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		nPosZ += 30.0f;
	}
	
	nPosZ = -35.0f;

	for ( int nIdx = 0; nIdx < 2; nIdx++ )
	{
		GameObject::Ptr pObject = GameObject::Create< House >( 
			pPhongProgram, m_vecBuildings[1], Zeno::Vector3( -12.2f, 0.0f, nPosZ ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		pObject = GameObject::Create< Building >( 
			pPhongProgram, m_vecBuildings[0], Zeno::Vector3( -18.5f, 0.0f, nPosZ + 18.0f ) );

		if ( pObject->IsReady() )
		{
			m_vecObjects.push_back( pObject );
		}

		nPosZ += 30.0f;
	}
	
	GameObject::Ptr pObject = GameObject::Create< School >( 
		pPhongProgram, m_vecBuildings[2], Zeno::Vector3( -5.5f, 0.0f, -52.0f ) );

	if ( pObject->IsReady() )
	{
		m_vecObjects.push_back( pObject );
	}
	
	pObject = GameObject::Create< School >( 
		pPhongProgram, m_vecBuildings[2], Zeno::Vector3( -6.0f, 0.0f, 20.0f ) );

	if ( pObject->IsReady() )
	{
		m_vecObjects.push_back( pObject );
	}

	m_bCarHit = false;
}

void Level::OnLeave( std::weak_ptr< GameState > pNewState )
{
	// Disable Z-buffer
	glDisable( GL_DEPTH_TEST );

	// Disable transparency
	glDisable( GL_BLEND );

	m_pSoundDevice->setAllSoundsPaused( true );

	m_vecObjects.clear();

	m_pSoundDevice->removeAllSoundSources();

	if ( !pNewState.expired() )
	{
		GameState::Ptr pState = pNewState.lock();

		if ( pState->GetName() == "End" )
		{
			std::shared_ptr< End > pCastState = std::static_pointer_cast< End >( pState );

			if ( m_bCarHit )
			{
				pCastState->SetStatus( GAME_OVER_HIT_BY_CAR );
			}
			else
			{
				if ( m_nTimeLeft > 0 )
				{
					pCastState->SetStatus( GAME_OVER_VICTORY );

					pCastState->SetScore( m_nTimeLeft * m_nGold );
				}
				else
				{
					pCastState->SetStatus( GAME_OVER_TIME_ELAPSED );

					pCastState->SetScore( m_nGold );
				}				
			}
		}
	}
}

void Level::OnUpdate( float nDeltaTime )
{
	// Update time elapsed since the state started
	m_nElapsedTime += nDeltaTime;

	// Check if one second elapsed
	if ( m_nElapsedTime > m_nLastTime )
	{
		// Decrease time left for the game
		m_nTimeLeft--;

		// Set the new upper limit for time
		m_nLastTime = m_nElapsedTime + 1;
	}
	// If time left is zero, exit application
	else if ( m_nTimeLeft == 0 )
	{
		if ( !m_pContext.expired() )
		{
			m_pContext.lock()->ChangeState( "End" );
		}
	}

	if ( m_nGold == 100 )
	{
		if ( !m_pContext.expired() )
		{
			m_pContext.lock()->ChangeState( "End" );
		}
	}
	
	// Loop through all objects and call update function 
	for ( auto iterObj = m_vecObjects.begin();
		iterObj != m_vecObjects.end();
		iterObj++ )
	{
		( *iterObj )->Update( nDeltaTime );
	}

	m_pPlayer->Update( nDeltaTime );
	
	irrklang::vec3df ikPos( 0.0f, 0.0f, 0.0f );

	irrklang::vec3df ikView( 0.0f, 0.0f, 0.0f );

	m_pSoundDevice->setListenerPosition( ikPos, ikView );

	for ( auto iterObj = m_vecObjects.begin();
		iterObj != m_vecObjects.end();
		iterObj++ )
	{
		if ( m_pPlayer->CheckCollision( ( *iterObj ) ) && 
			( ( *iterObj )->GetName() == "Barrier" || 
			( *iterObj )->GetName() == "Building" ) )
		{
			std::shared_ptr< Player > pCastPlayer = std::static_pointer_cast< Player >( m_pPlayer );

			pCastPlayer->StepBack();
		}

		if ( m_pPlayer->CheckCollision( ( *iterObj ) ) && 
			( *iterObj )->GetName() == "Treasure" )
		{
			irrklang::vec3df ikPos( ( *iterObj )->GetPosition().m_S.X,
				( *iterObj )->GetPosition().m_S.Y,
				( *iterObj )->GetPosition().m_S.Z);

			iterObj = m_vecObjects.erase( iterObj );

			m_nGold += 10;

			if ( iterObj == m_vecObjects.end() )
			{
				break;
			}
		}
		
		if ( m_pPlayer->CheckCollision( ( *iterObj ) ) && 
			( *iterObj )->GetName() == "Vehicle" )
		{
			m_bCarHit = true;

			if ( !m_pContext.expired() )
			{
				m_pContext.lock()->ChangeState( "End" );
			}
		}
	}
}

void Level::OnRender( Zeno::Window* pWindow )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_pSkybox->Draw();

	m_pPlayer->Draw();

	for ( auto iterObj = m_vecObjects.begin();
		iterObj != m_vecObjects.end();
		iterObj++ )
	{
		( *iterObj )->Draw();
	}

	glDisable( GL_DEPTH_TEST );

	m_pBox->Draw( Zeno::Vector3( 0.0f ) );

	m_pFont->Draw( std::string( "Gold:" ) + std::to_string( m_nGold ),
		Zeno::Vector3( 20.0f, 30.0f, 0.0f ), 0.3f );

	m_pBox->Draw( Zeno::Vector3( 600.0f, 0.0f, 0.0f ) );

	m_pFont->Draw( std::string( "Time:" ) + std::to_string( m_nTimeLeft ),
		Zeno::Vector3( 620.0f, 30.0f, 0.0f ), 0.3f );

	glEnable( GL_DEPTH_TEST );

	pWindow->Present();
}

bool Level::OnEvent( Zeno::WindowMessage* pMessage )
{
	switch ( pMessage->m_nMessage )
	{
	case WM_KEYDOWN:
		{
			switch ( pMessage->m_wParam )
			{
			case VK_F1:
				{
					for ( auto iterObj = m_vecObjects.begin();
						iterObj != m_vecObjects.end();
						iterObj++ )
					{
						GameObject::Ptr pObject = *iterObj;

						( *iterObj )->ToggleAABB();
					}

					m_pPlayer->ToggleAABB();
				}
				break;

			}
		}
		break;

	}

	return true;
}

void Level::OnTerminate()
{
	if ( m_pSoundDevice )
	{
		m_pSoundDevice->drop();

		m_pSoundDevice = nullptr;
	}
}

bool Level::OnLoad()
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

	Model::Ptr pRoadModel = Model::Create( pPhongProgram, "data/models/road/road1.obj" );

	if ( !pRoadModel->IsReady() )
	{
		return false;
	}	
	
	m_vecObstacles.push_back( pRoadModel );

	Model::Ptr pBarrierModel = Model::Create( pPhongProgram, "data/models/obstacles/barrier/barrier1.3ds" );

	if ( !pBarrierModel->IsReady() )
	{
		return false;
	}
	
	m_vecObstacles.push_back( pBarrierModel );

	Model::Ptr pTreasureModel = Model::Create( pPhongProgram, "data/models/obstacles/gold/tyvekrone.obj" );

	if ( !pTreasureModel->IsReady() )
	{
		return false;
	}

	m_vecObstacles.push_back( pTreasureModel );
	
	std::string VehicleModels[ 2 ] = 
	{ 
		"data/models/vehicles/car/car.obj", 
		"data/models/vehicles/police/police.obj",
	};

	// Load vehicles models
	for ( int nIdx = 0; nIdx < 2; nIdx++ )
	{
		Model::Ptr pVehicleModel = Model::Create( pPhongProgram, VehicleModels[ nIdx ]  );

		if ( pVehicleModel->IsReady() )
		{
			m_vecVehicles.push_back( pVehicleModel );
		}
		else
		{
			return false;
		}
	}
	
	std::string BuildingsModels[ 3 ] = 
	{ 
		"data/models/buildings/building/building2.obj",
		"data/models/buildings/house/building10.obj",
		"data/models/buildings/school/building3.obj"
	};

	std::vector< Model::Ptr > vecBuildings;

	// Load buildings models
	for ( int nIdx = 0; nIdx < 3; nIdx++ )
	{
		Model::Ptr pBuildingModel = Model::Create( pPhongProgram, BuildingsModels[ nIdx ]  );

		if ( pBuildingModel->IsReady() )
		{
			m_vecBuildings.push_back( pBuildingModel );
		}
		else
		{
			return false;
		}
	}

	m_bLoaded = true;

	return true;
}
