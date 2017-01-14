#include "Misc/Texture.h"

const Texture::Ptr Texture::s_kDefault = Texture::Ptr( new Texture );

Texture::Texture()
{
	m_pImage = nullptr;
}

Texture::~Texture()
{

}

GLvoid Texture::Clear()
{
	m_Format = FIF_UNKNOWN;

	if ( m_pImage )
	{
		FreeImage_Unload( m_pImage );

		m_pImage = nullptr;
	}

	Zeno::Texture::Clear();
}

Texture::Ptr Texture::Create( GLenum Target, std::string FileName )
{
	Texture::Ptr pTexture( new Texture );

	if ( !pTexture->SetTarget( Target ) )
	{
		return s_kDefault;
	}

	if ( !pTexture->SetFile( FileName ) )
	{
		return s_kDefault;
	}

	if ( !pTexture->Load() )
	{
		return s_kDefault;
	}

	pTexture->SetSampler( GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	pTexture->SetSampler( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	pTexture->SetSampler( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );

	pTexture->SetSampler( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	return pTexture;
}

GLboolean Texture::LoadTexture()
{
	m_Format = FreeImage_GetFileType( m_FileName.c_str(), 0 );

	if ( m_Format == FIF_UNKNOWN ) 
	{
		m_Format = FreeImage_GetFIFFromFilename( m_FileName.c_str() );
	}

	if ( m_Format == FIF_UNKNOWN )
	{
		return false;
	}

	if ( FreeImage_FIFSupportsReading( m_Format ) )
	{
		m_pImage = FreeImage_Load( m_Format, m_FileName.c_str() );
	}

	if ( !m_pImage )
	{
		return false;
	}

	m_nBPP = FreeImage_GetBPP( m_pImage );

	m_nWidth = FreeImage_GetWidth( m_pImage );

	m_nHeight = FreeImage_GetHeight( m_pImage );

	GLubyte* pData = FreeImage_GetBits( m_pImage );

	if ( !pData || m_nWidth == 0 || m_nHeight == 0 || m_nBPP == 0 )
	{
		return false;
	}

	GLuint nSize = FreeImage_GetDIBSize( m_pImage );

	m_pData = new GLubyte[ nSize ];

	CopyMemory( m_pData, pData, nSize * sizeof( GLubyte ) );

	return true;
}
