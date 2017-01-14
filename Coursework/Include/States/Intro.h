#pragma once

#include "GameBase.h"
#include "GameState.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"

#include "Zeno/Math/Matrix4.h"

#include "Misc/Font.h"
#include "Misc/Layer.h"

class Intro : public GameState
{
public:
	Intro();

	virtual ~Intro();

	virtual std::string GetName();

	virtual bool OnInitialise( std::weak_ptr< GameBase > pGame );

	virtual void OnEnter( std::weak_ptr< GameState > pOldState );

	virtual void OnLeave( std::weak_ptr< GameState > pNewState );

	virtual void OnUpdate( float nDeltaTime );

	virtual void OnRender( Zeno::Window* pWindow );

	virtual bool OnEvent( Zeno::WindowMessage* pMessage );

private:
	std::weak_ptr< GameBase > m_pContext;

	float m_nElapsedTime;

	Font::Ptr m_pFont;

	Layer::Ptr m_pBackground;

	Layer::Ptr m_pLogo;

};
