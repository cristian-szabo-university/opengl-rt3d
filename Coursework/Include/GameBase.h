#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Interface/EventManager.h"
#include "Zeno/Interface/Window.h"
#include "Zeno/Interface/Timer.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Texture.h"

#include "Misc/Font.h"

class GameState;

class GameBase
{
public:
	typedef std::shared_ptr< GameBase > Ptr;

	~GameBase();

	bool Initialise();

	int Execute();

	void Terminate();

	void AttachState( std::shared_ptr< GameState > pState );

	void AttachProgram( Zeno::Program::Ptr pProgram );

	void AttachTexture( Zeno::Texture::Ptr pTexture );

	void AttachFont( Font::Ptr pFont );

	std::shared_ptr< GameState > PeekState();

	void ChangeState( std::string Name );

	Zeno::Program::Ptr GetProgram( std::string Name );

	Zeno::Texture::Ptr GetTexture( std::string Name );

	Font::Ptr GetFont( std::string Name );

	static Ptr Create( std::string Title );

private:
	std::string m_Title;

	Zeno::EventManager* m_pEventManager;

	Zeno::Window* m_pWindow;

	std::weak_ptr< GameState > m_pCurrentState;

	std::weak_ptr< GameState > m_pNextState;

	std::vector< std::shared_ptr< GameState > > m_vecStates;

	std::vector< Zeno::Program::Ptr > m_vecPrograms;

	std::vector< Zeno::Texture::Ptr > m_vecTextures;

	std::vector< Font::Ptr > m_vecFonts;

	static std::vector< Ptr > s_vecShareadGames;

	GameBase( std::string Title );

};
