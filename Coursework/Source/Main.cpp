#include "GameBase.h"

#include "States/Intro.h"
#include "States/Menu.h"
#include "States/Select.h"
#include "States/Level.h"
#include "States/End.h"

int main()
{
	GameBase::Ptr pGame = GameBase::Create( "Urban Cityscape" );

	if ( !pGame->Initialise() )
	{
		return 1;
	}

	Zeno::Matrix4 ProjMat;
	
	ProjMat.Ortho( 0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f );

	Zeno::Matrix4 ViewMat;
	
	ViewMat.LookAt( Zeno::Vector3( 0.0f, 0.0f, 0.0f ), 
		Zeno::Vector3( 0.0f, 0.0f, -1.0f ), 
		Zeno::Vector3( 0.0f, 1.0f, 0.0f ) );

	/*
		Prepare font shader program
	*/
	Zeno::Program::Ptr pFontProgram = Zeno::Program::Create( "data/shaders/ortho.vert", "data/shaders/font.frag" );

	pGame->AttachProgram( pFontProgram );

	pGame->AttachFont( Font::Create( pFontProgram, "data/fonts/mavenpro-regular.ttf", 128 ) );

	pFontProgram->GetVariable( "ProjMatrix" )->UpdateMatrix( ProjMat );

	pFontProgram->GetVariable( "ViewMatrix" )->UpdateMatrix( ViewMat );

	/*
		Prepare texture shader program
	*/
	Zeno::Program::Ptr pTextureProgram = Zeno::Program::Create( "data/shaders/ortho.vert", "data/shaders/texture.frag" );

	pGame->AttachProgram( pTextureProgram );

	pTextureProgram->GetVariable( "ProjMatrix" )->UpdateMatrix( ProjMat );

	pTextureProgram->GetVariable( "ViewMatrix" )->UpdateMatrix( ViewMat );

	pGame->AttachTexture( Texture::Create( GL_TEXTURE_2D, "data/textures/intro-bg.png" ) );

	pGame->AttachTexture( Texture::Create( GL_TEXTURE_2D, "data/textures/logo.png" ) );

	pGame->AttachTexture( Texture::Create( GL_TEXTURE_2D, "data/textures/menu-bg.png" ) );

	pGame->AttachTexture( Texture::Create( GL_TEXTURE_2D, "data/textures/ui-button.png" ) );

	pGame->AttachTexture( Texture::Create( GL_TEXTURE_2D, "data/textures/select-bg.png" ) );

	pGame->AttachTexture( Texture::Create( GL_TEXTURE_2D, "data/textures/ui-box.png" ) );

	pGame->AttachTexture( Texture::Create( GL_TEXTURE_2D, "data/textures/end-bg.png" ) );

	/*
		Prepare phong shader program
	*/
	Zeno::Program::Ptr pPhongProgram = Zeno::Program::Create( "data/shaders/phong.vert", "data/shaders/phong.frag" );

	pGame->AttachProgram( pPhongProgram );

	ProjMat.Perspective( 60.0f, 800.0f / 600.0f, 1.0f, 250.0f );

	pPhongProgram->GetVariable( "ProjMatrix" )->UpdateMatrix( ProjMat );

	ViewMat.LookAt( Zeno::Vector3( 0.0f, 0.0f, 1.0f ), 
		Zeno::Vector3( 0.0f, 0.0f, 0.0f ), 
		Zeno::Vector3( 0.0f, 1.0f, 0.0f ) );

	pPhongProgram->GetVariable( "ViewMatrix" )->UpdateMatrix( ViewMat );

	Zeno::Variable::Ptr pLightPosVar = Zeno::Variable::Create( pPhongProgram, "LightPosition" );

	if ( !pLightPosVar->IsReady() )
	{
		return false;
	}

	pLightPosVar->UpdateVector( Zeno::Vector4( 0.0f, 15.0f, 0.0f, 1.0f ) );

	pPhongProgram->AttachVariable( pLightPosVar );

	Zeno::Light::Ptr pLight = Zeno::Light::Create( 
		pPhongProgram,
		Zeno::Vector4( 0.3f, 0.3f, 0.3f, 1.0f ),
		Zeno::Vector4( 1.0f, 1.0f, 1.0f, 1.0f ),
		Zeno::Vector4( 0.8f, 0.8f, 0.8f, 1.0f ) );

	if ( !pLight->IsReady() )
	{
		return false;
	}

	pGame->AttachState( GameState::Ptr( new Intro ) );
	pGame->AttachState( GameState::Ptr( new Menu ) );
	pGame->AttachState( GameState::Ptr( new Select ) );
	pGame->AttachState( GameState::Ptr( new Level ) );
	pGame->AttachState( GameState::Ptr( new End ) );

	pGame->ChangeState( "Intro" );

	int nExitCode = pGame->Execute();

	pGame->Terminate();

	return nExitCode;
}
