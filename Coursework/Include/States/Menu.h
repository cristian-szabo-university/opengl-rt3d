#pragma once

#include "GameBase.h"
#include "GameState.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"

#include "Zeno/Math/Matrix4.h"

#include "Misc/Font.h"
#include "Misc/Texture.h"
#include "Misc/Button.h"

enum ButtonMenuType
{
	BUTTON_MENU_START,
	BUTTON_MENU_EXIT,
	BUTTON_MENU_COUNT
};

class Menu : public GameState
{
public:
	Menu();

	virtual ~Menu();

	virtual std::string GetName();

	virtual bool OnInitialise( std::weak_ptr< GameBase > pGame );

	virtual void OnEnter( std::weak_ptr< GameState > pOldState );

	virtual void OnLeave( std::weak_ptr< GameState > pNewState );

	virtual void OnRender( Zeno::Window* pWindow );

	virtual bool OnEvent( Zeno::WindowMessage* pMessage );

private:
	std::weak_ptr< GameBase > m_pContext;

	Font::Ptr m_pFont;

	Layer::Ptr m_pBackground;

	std::vector< Button::Ptr > m_vecButtons;

};