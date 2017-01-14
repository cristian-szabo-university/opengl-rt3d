#include "Misc/Button.h"

#include "Zeno/Interface/EventManager.h"

const Button::Ptr Button::s_kDefault = Button::Ptr( new Button );

Button::Button()
{
	Clear();
}

Button::~Button()
{
	Clear();
}

bool Button::SetFont( Font::Ptr pFont )
{
	if ( !pFont.get() || m_pFont->IsReady() )
	{
		return false;
	}

	m_pFont = pFont;

	return true;
}

bool Button::SetText( std::string Message )
{
	if ( Message.empty() || m_Message != std::string( "Unknown" ) )
	{
		return false;
	}

	m_Message = Message;

	return true;
}

bool Button::Load()
{
	if ( !m_pFont.get() || !m_pFont->IsReady() )
	{
		return false;
	}

	return Layer::Load();
}

bool Button::Draw( Zeno::Vector3 Position, float nScale )
{
	if ( !Layer::Draw( Position, nScale ) ) 
	{
		return false;
	}

	float nMsgWidth = float( m_pFont->GetWidth( m_Message ) );
	float nMsgHeight = float( m_pFont->GetHeight( m_Message ) );

	float nMsgScale = float( m_pTexture->GetHeight() ) / nMsgHeight * 0.6f;

	nMsgWidth *= nMsgScale;
	nMsgHeight *= nMsgScale;

	Zeno::Vector3 MsgPos
	(
		float( m_pTexture->GetWidth() - nMsgWidth ) / 2.0f,
		float( m_pTexture->GetHeight() - nMsgHeight ) / 2.0f,
		0.0f
	);

	m_LastPos = Position;

	if ( m_pFont->Draw( m_Message, m_LastPos + MsgPos, nMsgScale ) )
	{
		return false;
	}

	return true;
}

void Button::Clear()
{
	Layer::Clear();

	m_pFont = Font::s_kDefault;

	m_Message = "Unknown";
}

bool Button::OnClick( int nMousePosX, int MousePosY )
{
	if ( nMousePosX >= m_LastPos.m_S.X && nMousePosX <= m_LastPos.m_S.X + m_pTexture->GetWidth() )
	{
		if ( MousePosY >= m_LastPos.m_S.Y && MousePosY <= m_LastPos.m_S.Y + m_pTexture->GetHeight() )
		{
			return true;
		}
	}

	return false;
}

Button::Ptr Button::Create( Zeno::Program::Ptr pProgram, 
	Font::Ptr pFont, Zeno::Texture::Ptr pTexture, 
	std::string Message )
{
	Ptr pButton( new Button );

	if ( !pButton->SetProgram( pProgram ) )
	{
		return s_kDefault;
	}

	if ( !pButton->SetTexture( pTexture ) )
	{
		return s_kDefault;
	}

	GLfloat Vertices[] =
	{
		0.0f, float( pTexture->GetHeight() ), 0.0f,
		0.0f, 0.0f, 0.0f,
		float( pTexture->GetWidth() ), float( pTexture->GetHeight() ), 0.0f,
		float( pTexture->GetWidth() ), 0.0f, 0.0f
	};

	GLfloat TexCoords[] = 
	{
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	Zeno::Mesh::Ptr pMesh = Zeno::Mesh::Create( pProgram, 
		4, Vertices, nullptr, TexCoords );

	if ( !pButton->SetMesh( pMesh ) )
	{
		return s_kDefault;
	}

	if ( !pButton->SetFont( pFont ) )
	{
		return s_kDefault;
	}

	if ( !pButton->SetText( Message ) )
	{
		return s_kDefault;
	}

	if ( !pButton->Load() )
	{
		return s_kDefault;
	}

	return pButton;
}
