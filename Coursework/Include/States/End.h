#pragma once

#include "GameBase.h"
#include "GameState.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"

#include "Zeno/Math/Matrix4.h"

#include "Misc/Font.h"
#include "Misc/Layer.h"
#include "Misc/Button.h"

enum GameOverType
{
	GAME_OVER_VICTORY,
	GAME_OVER_DEFEAT,
	GAME_OVER_TIME_ELAPSED,
	GAME_OVER_HIT_BY_CAR,
};

class End : public GameState
{
public:
	End();

	virtual ~End();

	virtual std::string GetName();

	virtual bool OnInitialise( std::weak_ptr< GameBase > pGame );

	virtual void OnEnter( std::weak_ptr< GameState > pOldState );

	virtual void OnLeave( std::weak_ptr< GameState > pNewState );

	virtual void OnRender( Zeno::Window* pWindow );

	virtual bool OnEvent( Zeno::WindowMessage* pMessage );

	void SetStatus( GameOverType Type );

	void SetScore( int nValue );

private:
	std::weak_ptr< GameBase > m_pContext;

	GameOverType m_Type;

	int m_nTotalScore;

	Font::Ptr m_pFont;

	Layer::Ptr m_pBackground;

	Button::Ptr m_pButton;

};
