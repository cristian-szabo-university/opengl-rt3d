#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Mesh.h"
#include "Zeno/Render/Material.h"
#include "Zeno/Render/Texture.h"

#include "Misc/Layer.h"

class Button : public Layer
{
public:
	typedef std::shared_ptr< Button > Ptr;

	static const Ptr s_kDefault;

	Button();

	virtual ~Button();

	bool SetFont( Font::Ptr pFont );

	bool SetText( std::string Message );

	virtual bool Load();

	virtual bool Draw( Zeno::Vector3 Position, float nScale = 1.0f );

	virtual void Clear();

	bool OnClick( int nMousePosX, int MousePosY );

	static Ptr Create( Zeno::Program::Ptr pProgram, 
		Font::Ptr pFont, Zeno::Texture::Ptr pTexture, 
		std::string Message );

private:
	Font::Ptr m_pFont;

	Zeno::Vector3 m_LastPos;

	std::string m_Message;

};
