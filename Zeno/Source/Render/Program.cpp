#include "Zeno/Render/Program.h"
#include "Zeno/Render/Shader.h"
#include "Zeno/Render/Variable.h"

namespace Zeno
{
	const Program::Ptr Program::s_kDefault = Program::Ptr( new Program );

	//-------------------------------------------------------------------------------------------------
	Program::Program()
	{
		m_nHandle = 0;

		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	Program::~Program()
	{
		Clear();
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Program::Enable()
	{
		if ( !m_nHandle )
		{
			return false;
		}

		if ( !CheckProgramValid( m_nHandle ) )
		{
			return false;
		}

		glUseProgram( m_nHandle );

		return !CheckOpenGLState();
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Program::Disable()
	{
		if ( !m_nHandle )
		{
			return false;
		}

		glUseProgram( 0 );

		return !CheckOpenGLState();
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Program::AttachShader( std::shared_ptr< Shader > pShader )
	{
		if ( !pShader.get() || !pShader->IsReady() )
		{
			return false;
		}

		for ( auto iterShader = m_vecShaders.begin();
			iterShader != m_vecShaders.end(); 
			iterShader++ )
		{
			Shader::Ptr pCheckShader = *iterShader;

			if ( pCheckShader->GetHandle() == pShader->GetHandle() )
			{
				return false;
			}
		}

		m_vecShaders.push_back( pShader );

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Program::AttachVariable( std::shared_ptr< Variable > pVariable )
	{
		if ( !pVariable.get() || !pVariable->IsReady() )
		{
			return false;
		}

		for ( auto iterVar = m_vecVariables.begin();
			iterVar != m_vecVariables.end(); 
			iterVar++ )
		{
			Variable::Ptr pCheckVar = *iterVar;

			if ( pCheckVar->GetName() == pVariable->GetName() )
			{
				return false;
			}
		}

		m_vecVariables.push_back( pVariable );

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Program::Load()
	{
		if ( m_bReady )
		{
			return false;
		}

		if ( m_Name == "Unknown" )
		{
			return false;
		}

		m_nHandle = glCreateProgram();

		if ( CheckOpenGLState() )
		{
			return false;
		}

		for ( auto iterShader = m_vecShaders.begin();
			iterShader != m_vecShaders.end(); 
			iterShader++ )
		{
			Shader::Ptr pShader = *iterShader;

			m_Name += pShader->GetName().substr( 
				pShader->GetName().find_last_of( "/" ) + 1 ) + "_";

			glAttachShader( m_nHandle, pShader->GetHandle() );

			glLinkProgram( m_nHandle );

			if ( !CheckProgramState( m_nHandle ) )
			{
				return false;
			}
		}

		m_bReady = true;

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLvoid Program::Clear()
	{
		m_bReady = false;

		m_Name.clear();

		m_vecShaders.clear();

		m_vecVariables.clear();

		if ( m_nHandle )
		{
			glDeleteProgram( m_nHandle );

			m_nHandle = 0;
		}
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Program::IsReady()
	{
		return m_bReady;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLuint Program::GetHandle()
	{
		return m_nHandle;
	}
	
	//-------------------------------------------------------------------------------------------------
	std::string Program::GetName()
	{
		return m_Name;
	}
	
	//-------------------------------------------------------------------------------------------------
	std::shared_ptr< Variable > Program::GetVariable( std::string Name )
	{
		for ( auto iterVar = m_vecVariables.begin();
			iterVar != m_vecVariables.end(); 
			iterVar++ )
		{
			Variable::Ptr pCheckVar = *iterVar;

			if ( pCheckVar->GetName() == Name )
			{
				return pCheckVar;
			}
		}

		return Variable::s_kDefault;
	}
	
	//-------------------------------------------------------------------------------------------------
	Program::Ptr Program::Create( std::string VertexShaderFile, std::string FragmentShaderFile )
	{
		Program::Ptr pProgram( new Program );

		Shader::Ptr pVertexShader = Shader::Create( GL_VERTEX_SHADER, VertexShaderFile );

		if ( pVertexShader->IsReady() )
		{
			pProgram->AttachShader( pVertexShader );
		}

		Shader::Ptr pFragmentShader = Shader::Create( GL_FRAGMENT_SHADER, FragmentShaderFile );

		if ( pFragmentShader->IsReady() )
		{
			pProgram->AttachShader( pFragmentShader );
		}

		if ( !pProgram->Load() )
		{
			return s_kDefault;
		}

		Variable::Ptr pProjMatVar = Variable::Create( pProgram, "ProjMatrix" );

		if ( !pProjMatVar->IsReady() )
		{
			return s_kDefault;
		}

		pProgram->AttachVariable( pProjMatVar );

		Variable::Ptr pViewMatVar = Variable::Create( pProgram, "ViewMatrix" );

		if ( !pViewMatVar->IsReady() )
		{
			return s_kDefault;
		}

		pProgram->AttachVariable( pViewMatVar );

		Variable::Ptr pModelMatVar = Variable::Create( pProgram, "ModelMatrix" );

		if ( !pModelMatVar->IsReady() )
		{
			return s_kDefault;
		}

		pProgram->AttachVariable( pModelMatVar );

		return pProgram;
	}
}
