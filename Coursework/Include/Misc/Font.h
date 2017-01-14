#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Mesh.h"
#include "Zeno/Render/Buffer.h"
#include "Zeno/Render/Texture.h"

#include "Zeno/Math/Matrix4.h"

#include "ft2build.h"
#include FT_FREETYPE_H

class Character
{
public:
	typedef std::shared_ptr< Character > Ptr;

	static const Ptr s_kDefault;

	Character();

	~Character();

	bool SetProgram( Zeno::Program::Ptr pProgram );

	bool SetGlyph( FT_GlyphSlot pGlyph );

	bool Load();

	bool IsReady();

	bool Draw();

	void Clear();

	int GetWidth();

	int GetHeight();

	static Ptr Create( Zeno::Program::Ptr pProgram, FT_GlyphSlot pGlyph );

private:
	bool m_bReady;

	Zeno::Program::Ptr m_pProgram;

	Zeno::Texture::Ptr m_pTexture;

	Zeno::Mesh::Ptr m_pMesh;

	int m_nWidth, m_nHeight;

	int m_nLeft, m_nTop;

	int m_nAdvanceX, m_nAdvanceY;

};

class Font
{
public:
	typedef std::shared_ptr< Font > Ptr;

	static const Ptr s_kDefault;

	Font();

	~Font();

	bool SetProgram( Zeno::Program::Ptr pProgram );

	bool SetFile( std::string Name );

	bool SetSize( int nSize );

	bool Load();

	bool Draw( std::string Message, Zeno::Vector3 Position, float nScale = 1.0f );

	bool IsReady();

	void Clear();

	GLuint GetWidth( std::string Message );

	GLuint GetHeight( std::string Message );

	std::string GetName();

	static Ptr Create( Zeno::Program::Ptr pProgram, std::string FontName, int nFontSize );

private:
	bool m_bReady;

	Zeno::Program::Ptr m_pProgram;

	std::string m_Name;

	int m_nSize;

	FT_Library m_ftLibrary;

	FT_Face m_ftFace;

	Zeno::Matrix4 m_ModelMatrix;

	std::vector< Character::Ptr > m_vecChars;

	void LoadChar( GLuint nCharIdx );

};