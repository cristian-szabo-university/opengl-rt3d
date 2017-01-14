#pragma once

#include "GameBase.h"
#include "GameState.h"
#include "GameObject.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Light.h"

#include "Zeno/Math/Matrix4.h"

#include "Misc/Model.h"
#include "Misc/Layer.h"
#include "Misc/Skybox.h"

#include "irrKlang.h"

class Level : public GameState
{
public:
	Level();

	virtual ~Level();

	virtual std::string GetName();

	virtual bool OnInitialise( std::weak_ptr< GameBase > pGame );

	virtual void OnEnter( std::weak_ptr< GameState > pOldState );

	virtual void OnLeave( std::weak_ptr< GameState > pNewState );

	virtual void OnUpdate( float nDeltaTime );

	virtual void OnRender( Zeno::Window* pWindow );

	virtual bool OnEvent( Zeno::WindowMessage* pMessage );

	virtual void OnTerminate();

	bool OnLoad();

private:
	bool m_bLoaded;

	bool m_bCarHit;

	std::weak_ptr< GameBase > m_pContext;

	float m_nElapsedTime;

	float m_nLastTime;

	int m_nTimeLeft;

	int m_nGold;

	Layer::Ptr m_pBox;

	Font::Ptr m_pFont;

	Skybox::Ptr m_pSkybox;

	GameObject::Ptr m_pPlayer;

	irrklang::ISoundEngine* m_pSoundDevice;

	irrklang::ISoundSource* m_pSoundBackground;

	irrklang::ISoundSource* m_pSoundCar;

	irrklang::ISoundSource* m_pSoundPolice;

	std::vector< GameObject::Ptr > m_vecObjects;

	std::vector< Zeno::Model::Ptr > m_vecVehicles;

	std::vector< Zeno::Model::Ptr > m_vecBuildings;

	std::vector< Zeno::Model::Ptr > m_vecObstacles;

	Zeno::Matrix4 m_ProjMatrix;

	Zeno::Matrix4 m_ViewMatrix;

};
