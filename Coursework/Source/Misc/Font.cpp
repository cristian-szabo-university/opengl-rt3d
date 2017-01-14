#include "Misc/Font.h"

const Character::Ptr Character::s_kDefault = Character::Ptr( new Character );

Character::Character()
{
	Clear();
}

Character::~Character()
{
	Clear();
}

bool Character::SetProgram( Zeno::Program::Ptr pProgram )
{
	if ( !pProgram.get() ||  m_pProgram->IsReady() )
	{
		return false;
	}

	m_pProgram = pProgram;

	return true;
}

bool Character::SetGlyph( FT_GlyphSlot pGlyph )
{
	if ( !pGlyph || m_pTexture->IsReady() )
	{
		return false;
	}

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	m_pTexture = Zeno::Texture::Create( GL_TEXTURE_2D, 
		pGlyph->bitmap.buffer, 
		pGlyph->bitmap.width, 
		pGlyph->bitmap.rows, 8 );

	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

	m_nWidth = pGlyph->bitmap.width;

	m_nHeight = pGlyph->bitmap.rows;

	m_nLeft = pGlyph->bitmap_left;

	m_nTop = pGlyph->bitmap_top;

	m_nAdvanceX = pGlyph->advance.x >> 6;

	m_nAdvanceY = pGlyph->advance.y >> 6;

	return true;
}

bool Character::Load()
{
	if ( m_bReady )
	{
		return false;
	}

	if ( !m_pProgram->IsReady() )
	{
		return false;
	}

	GLfloat Vertices[] =
	{		
		0.0f, 0.0f,	0.0f,
		float( m_nWidth ), 0.0f, 0.0f,
		0.0f, float( m_nHeight ), 0.0f,
		float( m_nWidth ), float( m_nHeight ), 0.0f,
	};

	GLfloat TexCoords[] = 
	{
		0.0f, 1.0f,	
		1.0f, 1.0f, 
		0.0f, 0.0f, 
		1.0f, 0.0f
	};

	m_pMesh = Zeno::Mesh::Create( m_pProgram,
		4, Vertices, nullptr, TexCoords );

	if ( !m_pMesh->IsReady() )
	{
		return false;
	}

	m_bReady = true;

	return true;
}

bool Character::IsReady()
{
	return m_bReady;
}

bool Character::Draw()
{
	if ( !m_bReady )
	{
		return false;
	}

	Zeno::Matrix4 ModelMatrix;

	m_pProgram->GetVariable( "ModelMatrix" )->GetMatrix( ModelMatrix );

	ModelMatrix.Translate( Zeno::Vector3( float( m_nLeft ), float( m_nTop - m_nHeight ), 0.0f ) );

	m_pProgram->GetVariable( "ModelMatrix" )->UpdateMatrix( ModelMatrix );

	if ( m_pTexture->IsReady() )
	{
		if ( !m_pTexture->Enable() )
		{
			return false;
		}
	}

	if ( !m_pMesh->Draw( GL_TRIANGLE_STRIP ) )
	{
		return false;
	}

	if ( m_pTexture->IsReady() )
	{
		if ( !m_pTexture->Disable() )
		{
			return false;
		}
	}

	ModelMatrix.Translate( Zeno::Vector3( float( m_nAdvanceX ), -float( m_nTop - m_nHeight ), 0.0f ) );

	m_pProgram->GetVariable( "ModelMatrix" )->UpdateMatrix( ModelMatrix );

	return true;
}

void Character::Clear()
{
	m_bReady = false;

	m_pProgram = Zeno::Program::s_kDefault;

	m_pTexture = Zeno::Texture::s_kDefault;

	m_pMesh = Zeno::Mesh::s_kDefault;

	m_nWidth = m_nHeight = 0;

	m_nLeft = m_nTop = 0;

	m_nAdvanceX = m_nAdvanceY = 0;
}

int Character::GetWidth()
{
	return m_nLeft + m_nAdvanceX;
}

int Character::GetHeight()
{
	return m_nHeight;
}

Character::Ptr Character::Create( Zeno::Program::Ptr pProgram, FT_GlyphSlot pGlyph )
{
	Ptr pChar( new Character );

	if ( !pChar->SetProgram( pProgram ) )
	{
		return s_kDefault;
	}

	if ( !pChar->SetGlyph( pGlyph ) )
	{
		return s_kDefault;
	}

	if ( !pChar->Load() )
	{
		return s_kDefault;
	}

	return pChar;
}

const Font::Ptr Font::s_kDefault = Font::Ptr( new Font );

Font::Font()
{
	m_ftLibrary = nullptr;

	m_ftFace = nullptr;

	Clear();
}

Font::~Font()
{
	Clear();
}

bool Font::SetProgram( Zeno::Program::Ptr pProgram )
{
	if ( !pProgram.get() || m_pProgram->IsReady() )
	{
		return false;
	}

	Zeno::Variable::Ptr pModelMatVar = Zeno::Variable::Create( pProgram, "ModelMatrix" );

	if ( !pModelMatVar->IsReady() )
	{
		return false;
	}

	pProgram->AttachVariable( pModelMatVar );

	m_pProgram = pProgram;

	return true;
}

bool Font::SetFile( std::string Name )
{
	if ( Name.empty() || m_Name != "Unknown" )
	{
		return false;
	}

	m_Name = Name;

	return true;
}

bool Font::SetSize( int nSize )
{
	if ( nSize < 12 || m_nSize > 12 )
	{
		return false;
	}

	m_nSize = nSize;

	return true;
}

bool Font::Load()
{
	if ( m_bReady )
	{
		return false;
	}

	BOOL bError = FT_Init_FreeType( &m_ftLibrary );

	if ( bError )
	{
		return false;
	}
	
	bError = FT_New_Face( m_ftLibrary, m_Name.c_str(), 0, &m_ftFace );

	if ( bError )
	{
		return false;
	}

	bError = FT_Set_Pixel_Sizes( m_ftFace, m_nSize, m_nSize );

	if ( bError )
	{
		return false;
	}

	for ( GLuint nCharIdx = 0; nCharIdx < 128; nCharIdx++ )
	{
		FT_Load_Glyph( m_ftFace, FT_Get_Char_Index( m_ftFace, nCharIdx ), FT_LOAD_DEFAULT );

		FT_Render_Glyph( m_ftFace->glyph, FT_RENDER_MODE_NORMAL );

		Character::Ptr pChar = Character::Create( m_pProgram, m_ftFace->glyph );

		if ( pChar->IsReady() )
		{
			m_vecChars.push_back( pChar );
		}
	}

	m_bReady = true;

	return true;
}

bool Font::Draw( std::string Message, Zeno::Vector3 Position, float nScale )
{
	m_ModelMatrix.Translate( Position );

	m_ModelMatrix.Scale( Zeno::Vector3( nScale ) );

	m_pProgram->GetVariable( "ModelMatrix" )->UpdateMatrix( m_ModelMatrix );	

	for ( auto iterChar = Message.begin();
		iterChar != Message.end();
		iterChar++ )
	{
		char Char = *iterChar;
		int nCharValue = static_cast< int >( Char );

		Character::Ptr pCharMesh = m_vecChars.at( nCharValue );

		if ( !pCharMesh->Draw() )
		{
			return false;
		}
	}

	m_ModelMatrix.Identity();

	return true;
}

bool Font::IsReady()
{
	return m_bReady;
}

void Font::Clear()
{
	m_bReady = false;

	m_Name = "Unknown";

	m_nSize = 12;

	m_pProgram = Zeno::Program::s_kDefault;

	m_vecChars.clear();

	if ( m_ftFace )
	{
		FT_Done_Face( m_ftFace );

		m_ftFace = nullptr;
	}

	if ( m_ftLibrary )
	{
		FT_Done_FreeType( m_ftLibrary );

		m_ftLibrary = nullptr;
	}
}

GLuint Font::GetWidth( std::string Message )
{
	GLuint nLineWidth = 0;

	for ( auto iterChar = Message.begin();
		iterChar != Message.end();
		iterChar++ )
	{
		char Char = *iterChar;
		int nCharValue = static_cast< int >( Char );

		Character::Ptr pCharMesh = m_vecChars.at( nCharValue );

		nLineWidth += pCharMesh->GetWidth();
	}

	return nLineWidth;
}

GLuint Font::GetHeight( std::string Message )
{
	GLint nLineHeight = 0;

	for ( auto iterChar = Message.begin();
		iterChar != Message.end();
		iterChar++ )
	{
		char Char = *iterChar;
		int nCharValue = static_cast< int >( Char );

		Character::Ptr pCharMesh = m_vecChars.at( nCharValue );

		nLineHeight = max( nLineHeight, pCharMesh->GetHeight() );
	}

	return nLineHeight;
}

std::string Font::GetName()
{
	return m_Name;
}

Font::Ptr Font::Create( Zeno::Program::Ptr pProgram, std::string FontName, int nFontSize )
{
	Ptr pFont( new Font );

	if ( !pFont->SetProgram( pProgram ) )
	{
		return s_kDefault;
	}

	if ( !pFont->SetFile( FontName ) )
	{
		return s_kDefault;
	}

	if ( !pFont->SetSize( nFontSize ) )
	{
		return s_kDefault;
	}

	if ( !pFont->Load() )
	{
		return s_kDefault;
	}

	return pFont;
}
