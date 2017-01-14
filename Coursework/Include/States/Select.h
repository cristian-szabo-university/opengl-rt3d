#pragma once

#include "GameBase.h"
#include "GameState.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Model.h"

#include "Zeno/Math/Matrix4.h"

#include "Misc/Font.h"
#include "Misc/Button.h"
#include "Misc/Layer.h"

#include "Objects/Player.h"
#include "Objects/Demo.h"

enum ButtonSlectType
{
	BUTTON_SELECT_NEXT,
	BUTTON_SELECT_GO,
	BUTTON_SELECT_COUNT
};

class Select : public GameState
{
public:
	Select();

	virtual ~Select();
	
	virtual std::string GetName();

	virtual bool OnInitialise( std::weak_ptr< GameBase > pGame );

	virtual void OnEnter( std::weak_ptr< GameState > pOldState );

	virtual void OnLeave( std::weak_ptr< GameState > pNewState );

	virtual void OnUpdate( float nDeltaTime );

	virtual void OnRender( Zeno::Window* pWindow );

	virtual bool OnEvent( Zeno::WindowMessage* pMessage );

	bool OnLoad();

	Zeno::Model::Ptr GetModelPlayer();

private:
	bool m_bLoaded;

	std::weak_ptr< GameBase > m_pContext;

	Font::Ptr m_pFont;

	Layer::Ptr m_pBackground;

	GameObject::Ptr m_pDemo;

	std::vector< Button::Ptr > m_vecButtons;

	std::vector< Zeno::Model::Ptr > m_vecModels;

	int m_nSelectModel;

	void NextModel();

};
