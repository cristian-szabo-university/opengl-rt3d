#include "Zeno/Render/Shader.h"

namespace Zeno
{
	const Shader::Ptr Shader::s_kDefault = Shader::Create();

	//-------------------------------------------------------------------------------------------------
	Shader::Shader()
	{
		m_nHandle = 0;

		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	Shader::~Shader()
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Shader::SetType( GLenum Type )
	{
		if ( Type != GL_VERTEX_SHADER &&
			Type != GL_FRAGMENT_SHADER )
		{
			return false;
		}

		m_Type = Type;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Shader::SetFile( std::string FileName )
	{
		if ( FileName.empty() || m_FileName != std::string( "Unknown" ) )
		{
			return false;
		}

		m_FileName = FileName;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Shader::Load()
	{
		if ( m_bReady )
		{
			return false;
		}

		m_nHandle = glCreateShader( m_Type );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		std::ifstream File;
		std::string Data;

		File.open( m_FileName.c_str(), std::ios::app | std::ios::in );

		if ( File.is_open() ) 
		{
			while( !File.eof() ) 
			{
				std::string Line;

				std::getline( File, Line, '\n' );

				Data.append( Line + "\n" );
    		}
		}

		File.close();

		if ( Data.empty() )
		{
			return false;
		}

		const GLint pSize = Data.size();

		const GLchar* pSource = Data.c_str(); 
	
		glShaderSource( m_nHandle, 1, &pSource, &pSize );

		glCompileShader( m_nHandle );

		if ( !CheckShaderState( m_nHandle ) )
		{
			return false;
		}

		m_bReady = true;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Shader::Clear()
	{
		m_bReady = false;

		m_FileName = "Unknown";

		if ( m_nHandle )
		{
			glDeleteShader( m_nHandle );

			m_nHandle = 0;
		}
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Shader::IsReady()
	{
		return m_bReady;
	}

	//-------------------------------------------------------------------------------------------------
	GLuint Shader::GetHandle()
	{
		return m_nHandle;
	}

	//-------------------------------------------------------------------------------------------------
	std::string Shader::GetName()
	{
		return m_FileName;
	}

	//-------------------------------------------------------------------------------------------------
	Shader::Ptr Shader::Create()
	{
		return std::make_shared< Shader >();
	}

	//-------------------------------------------------------------------------------------------------
	Shader::Ptr Shader::Create( GLenum Type, std::string FileName )
	{
		Shader::Ptr pShader = Create();

		if ( !pShader->SetType( Type ) )
		{
			return s_kDefault;
		}

		if ( !pShader->SetFile( FileName ) )
		{
			return s_kDefault;
		}

		if ( !pShader->Load() )
		{
			return s_kDefault;
		}

		return pShader;
	}
}
