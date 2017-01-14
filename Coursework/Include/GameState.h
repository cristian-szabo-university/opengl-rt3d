#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Interface/Window.h"

class GameBase;

class GameState
{
public:
	typedef std::shared_ptr< GameState > Ptr;

	virtual ~GameState();

	virtual std::string GetName() = 0;

	virtual bool OnInitialise( std::weak_ptr< GameBase > pGame );

	virtual void OnEnter( std::weak_ptr< GameState > pOldState );

	virtual void OnLeave( std::weak_ptr< GameState > pNewState );

	virtual void OnUpdate( float nDeltaTime );

	virtual void OnRender( Zeno::Window* pWindow );

	virtual bool OnEvent( Zeno::WindowMessage* pMessage );

	virtual void OnTerminate();

};
