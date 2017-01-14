#include "Zeno/Render/Buffer.h"

namespace Zeno
{
	const Buffer::Ptr Buffer::s_kDefault = Buffer::Ptr( new Buffer );

	//-------------------------------------------------------------------------------------------------
	Buffer::Buffer()
	{
		m_nName = 0;

		m_pData = nullptr;

		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	Buffer::~Buffer()
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Buffer::Enable()
	{
		if ( !m_bReady )
		{
			return false;
		}

		glBindBuffer( m_Target, m_nName );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Buffer::Disable()
	{
		if ( !m_bReady )
		{
			return false;
		}

		glBindBuffer( m_Target, 0 );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Buffer::SetTarget( GLenum Target )
	{
		if ( Target != GL_ARRAY_BUFFER && Target != GL_ELEMENT_ARRAY_BUFFER )
		{
			return false;
		}

		m_Target = Target;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Buffer::SetUsage( GLenum Usage )
	{
		if ( Usage != GL_STATIC_DRAW && Usage != GL_DYNAMIC_DRAW )
		{
			return false;
		}

		m_Usage = Usage;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Buffer::SetAttribute( std::string Name, GLuint nSize )
	{
		if ( Name.empty() || m_AttribName != std::string( "Unknown" ) ||
			!nSize || m_nAttribSize )
		{
			return false;
		}

		m_AttribName = Name;

		m_nAttribSize = nSize;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Buffer::SetData( GLvoid* pData, GLuint nSize )
	{
		if ( !pData || !nSize || m_pData )
		{
			return false;
		}

		if ( m_Target == GL_ARRAY_BUFFER )
		{
			m_nSize = nSize * sizeof( GLfloat );

			m_pData = new GLfloat[ nSize ];
		}
		else if ( m_Target == GL_ELEMENT_ARRAY_BUFFER )
		{
			m_nSize = nSize * sizeof( GLuint );

			m_pData = new GLuint[ nSize ];
		}
		else
		{
			return false;
		}

		CopyMemory( m_pData, pData, m_nSize );

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Buffer::Load()
	{
		if ( m_bReady )
		{
			return false;
		}

		// Generate buffer object name
		glGenBuffers( 1, &m_nName );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		m_bReady = true;

		// Check for last GL function state
		if ( !Enable() )
		{
			return false;
		}

		// Create and initialize a buffer object's data store
		glBufferData( m_Target, m_nSize, m_pData, m_Usage );

		// Check for last GL function state
		if ( CheckOpenGLState() )
		{
			return false;
		}

		// Check for last GL function state
		if ( !Disable() )
		{
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Buffer::Clear()
	{
		m_bReady = false;

		m_AttribName = "Unknown";

		m_nAttribSize = 0;

		m_Target = 0;

		m_Usage = 0;

		m_nSize = 0;

		if ( m_pData )
		{
			delete m_pData;

			m_pData = nullptr;
		}	

		if ( m_nName )
		{
			glDeleteBuffers( 1, &m_nName );

			m_nName = 0;
		}
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Buffer::IsReady()
	{
		return m_bReady;
	}

	//-------------------------------------------------------------------------------------------------
	GLuint Buffer::GetName()
	{
		return m_nName;
	}

	//-------------------------------------------------------------------------------------------------
	GLuint Buffer::GetSize()
	{
		return m_nSize;
	}

	//-------------------------------------------------------------------------------------------------
	std::string Buffer::GetAttribName()
	{
		return m_AttribName;
	}

	//-------------------------------------------------------------------------------------------------
	GLuint Buffer::GetAttribSize()
	{
		return m_nAttribSize;
	}

	//-------------------------------------------------------------------------------------------------
	std::shared_ptr< Buffer > Buffer::Create( std::string AttribName, GLuint nAttribSize, 
		GLvoid* pData, GLuint nSize, GLenum Target, GLenum Usage )
	{
		Buffer::Ptr pBuffer( new Buffer );

		if ( !pBuffer->SetTarget( Target ) )
		{
			return s_kDefault;
		}

		if ( !pBuffer->SetUsage( Usage ) )
		{
			return s_kDefault;
		}

		if ( !pBuffer->SetAttribute( AttribName, nAttribSize ) )
		{
			return s_kDefault;
		}

		if ( !pBuffer->SetData( pData, nSize ) )
		{
			return s_kDefault;
		}

		if ( !pBuffer->Load() )
		{
			return s_kDefault;
		}

		return pBuffer;
	}
}
