#include "Zeno/Render/Texture.h"

struct TGA_Header 
{
	unsigned char	ID_Length;
	unsigned char	ColorMapType;
	unsigned char	ImageType;
	unsigned char	ColorMapSpecification[5];
	short			xOrigin;
	short			yOrigin;
	short			ImageWidth;
	short			ImageHeight;
	unsigned char	PixelDepth;
	unsigned char	ImageDescriptor;
};

namespace Zeno
{
	const Texture::Ptr Texture::s_kDefault = Texture::Ptr( new Texture );

	//-------------------------------------------------------------------------------------------------
	Texture::Texture()
	{
		m_nName = m_nSampler = 0;

		m_pData = nullptr;

		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	Texture::~Texture()
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Texture::Enable()
	{
		if ( !m_bReady )
		{
			return false;
		}

		glBindTexture( m_Target, m_nName );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		glBindSampler( 0, m_nSampler );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Texture::Disable()
	{
		if ( !m_bReady )
		{
			return false;
		}

		glBindSampler( 0, 0 );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		glBindTexture( m_Target, 0 );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Texture::SetTarget( GLenum Target )
	{
		if ( Target != GL_TEXTURE_2D )
		{
			return false;
		}

		m_Target = Target;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Texture::SetFile( std::string FileName )
	{
		if ( FileName.empty() || m_FileName != "Unknown" )
		{
			return false;
		}

		m_FileName = FileName;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Texture::SetPixels( GLvoid* pData, GLuint nWidth, GLuint nHeight, GLuint nBPP )
	{
		if ( !pData || m_pData )
		{
			return false;
		}

		GLuint nSize = nWidth * nHeight;

		m_pData = new GLubyte[ nSize ];

		CopyMemory( m_pData, pData, nSize * sizeof( GLubyte ) );

		m_nWidth = nWidth;

		m_nHeight = nHeight;

		m_nBPP = nBPP;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Texture::SetSampler( GLenum Sampler, GLenum Filter )
	{
		if ( !m_bReady )
		{
			return false;
		}

		glSamplerParameteri( m_nSampler, Sampler, Filter );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Texture::Load()
	{
		if ( m_bReady )
		{
			return false;
		}

		if ( !m_pData && !LoadTexture() )
		{
			return false;
		}

		glGenTextures( 1, &m_nName );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		glGenSamplers( 1, &m_nSampler );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		m_bReady = true;

		if ( !Enable() )
		{
			return false;
		}

		GLenum ImageFormat;
		GLint InternalFormat;

		if ( m_nBPP == 32 )
		{
			ImageFormat = GL_BGRA;

			InternalFormat = GL_RGBA;
		}
		else if ( m_nBPP == 24 )
		{
			ImageFormat = GL_RGB;

			InternalFormat = GL_RGB;
		}
		else if ( m_nBPP == 8 )
		{
			ImageFormat = GL_RED;

			InternalFormat = GL_RED;
		}
		else
		{
			return false;
		}

		// Store the texture data for OpenGL use
		glTexImage2D
		( 
			m_Target, 
			0, InternalFormat, 
			m_nWidth, m_nHeight,
			0, ImageFormat,
			GL_UNSIGNED_BYTE, m_pData 
		);

		if ( CheckOpenGLState() )
		{
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Texture::Clear()
	{
		m_bReady = false;

		m_nWidth = m_nHeight = m_nBPP = 0;

		m_FileName = "Unknown";

		if ( m_pData )
		{
			delete [] m_pData;

			m_pData = nullptr;
		}

		if ( m_nName )
		{
			glDeleteTextures( 1, &m_nName );

			m_nName = 0;
		}

		if ( m_nSampler )
		{
			glDeleteSamplers( 1, &m_nSampler );

			m_nSampler = 0;
		}
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Texture::IsReady()
	{
		return m_bReady;
	}

	//-------------------------------------------------------------------------------------------------
	std::string Texture::GetName()
	{
		return m_FileName;
	}

	//-------------------------------------------------------------------------------------------------
	GLuint Texture::GetWidth()
	{
		return m_nWidth;
	}

	//-------------------------------------------------------------------------------------------------
	GLuint Texture::GetHeight()
	{
		return m_nHeight;
	}

	//-------------------------------------------------------------------------------------------------
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

	//-------------------------------------------------------------------------------------------------
	Texture::Ptr Texture::Create( GLenum Target, GLvoid* pData,
		GLuint nWidth, GLuint nHeight, GLuint nBPP )
	{
		Texture::Ptr pTexture( new Texture );

		if ( !pTexture->SetTarget( Target ) )
		{
			return s_kDefault;
		}

		if ( !pTexture->SetPixels( pData, nWidth, nHeight, nBPP ) )
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
		TGA_Header Header;

		std::ifstream File( m_FileName.c_str(), std::ios::binary );

		if ( !File.is_open() ) 
		{
			File.close();

			return false;
		}

		// Get TGA header file
		if ( !File.read( (char*)&Header, sizeof( TGA_Header ) ) ) 
		{
			File.close();

			return false;
		}

		// We can only load uncompressed, true-color images
		if ( ( Header.ImageType != 2 ) ) 
		{
			File.close();

			return false;
		}

		// Test if image has correct number of bits per pixel
		m_nBPP = Header.PixelDepth;

		if ( ( m_nBPP != 24 ) && ( m_nBPP != 32 ) ) 
		{
			File.close();

			return false;
		}
	
		// Convert Bits per pixel to Bytes per pixel
		GLuint nBytesPP = m_nBPP / 8;

		m_nWidth = Header.ImageWidth;
		m_nHeight = Header.ImageHeight;

		GLuint nImageSize = m_nWidth * m_nHeight * nBytesPP;

		m_pData = new unsigned char[ nImageSize ];

		// Move read pointer to beginning of image data
		File.seekg( Header.ID_Length, std::ios::cur );

		// TGA data is uncompressed
		if ( !File.read( (char*)m_pData, nImageSize) ) 
		{
			delete [] m_pData;

			File.close();

			return false;
		}

		File.close();

		// Convert all image data from BGR to RGB data
		GLuint nTemp;

		for ( GLuint nIndex = 0; nIndex < nImageSize; nIndex += nBytesPP ) 
		{
			// Save Blue color
			nTemp = m_pData[ nIndex ];			

			// Set Red color
			m_pData[ nIndex ] = m_pData[ nIndex + 2 ];		

			// Set Blue color
			m_pData[ nIndex + 2 ] = nTemp;					
		}

		return true;
	}
}
