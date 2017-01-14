#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Program.h"

namespace Zeno
{
	const Variable::Ptr Variable::s_kDefault = Variable::Ptr( new Variable );

	//-------------------------------------------------------------------------------------------------
	Variable::Variable()
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	Variable::~Variable()
	{
		Clear();
	}

	GLboolean Variable::SetProgram( std::shared_ptr< Program > pProgram )
	{
		if ( !pProgram.get() || m_pProgram.get() )
		{
			return false;
		}

		m_pProgram = pProgram;

		return true;
	}

	GLboolean Variable::SetName( std::string Name )
	{
		if ( Name.empty() || m_Name != std::string( "Unknown" ) )
		{
			return false;
		}

		m_Name = Name;

		return true;
	}

	GLboolean Variable::Load()
	{
		if ( m_bReady )
		{
			return false;
		}

		if ( !m_pProgram.get() || !m_pProgram->IsReady() )
		{
			return false;
		}

		if ( m_Name == std::string( "Unknown" ) )
		{
			return false;
		}

		m_nLocation = glGetUniformLocation( m_pProgram->GetHandle(), m_Name.c_str() );

		if ( m_nLocation < 0 || CheckOpenGLState() )
		{
			return false;
		}

		m_bReady = true;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Variable::UpdateValue( float nValue )
	{
		if ( !m_bReady ) 
		{
			return false;
		}

		glProgramUniform1fv( m_pProgram->GetHandle(), m_nLocation, 1, &nValue );  

		return !CheckOpenGLState();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Variable::UpdateVector( Vector3 Vector )
	{
		if ( !m_bReady ) 
		{
			return false;
		}

		glProgramUniform3fv( m_pProgram->GetHandle(), m_nLocation, 1, Vector );

		return !CheckOpenGLState();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Variable::UpdateVector( Vector4 Vector )
	{
		if ( !m_bReady ) 
		{
			return false;
		}

		glProgramUniform4fv( m_pProgram->GetHandle(), m_nLocation, 1, Vector );

		return !CheckOpenGLState();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Variable::UpdateMatrix( Matrix4 Matrix )
	{
		if ( !m_bReady ) 
		{
			return false;
		}

		glProgramUniformMatrix4fv( m_pProgram->GetHandle(), m_nLocation, 1, false, Matrix );

		return !CheckOpenGLState();
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Variable::Clear()
	{
		m_bReady = false;

		m_pProgram.reset();

		m_Name = "Unknown";

		m_nLocation = -1;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Variable::IsReady()
	{
		return m_bReady;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Variable::GetValue( float& rValue )
	{
		if ( !m_bReady ) 
		{
			return false;
		}

		glGetUniformfv( m_pProgram->GetHandle(), m_nLocation, &rValue );

		return !CheckOpenGLState();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Variable::GetVector( Vector3& rVector )
	{
		if ( !m_bReady ) 
		{
			return false;
		}

		glGetUniformfv( m_pProgram->GetHandle(), m_nLocation, rVector );

		return !CheckOpenGLState();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Variable::GetVector( Vector4& rVector )
	{
		if ( !m_bReady ) 
		{
			return false;
		}

		glGetUniformfv( m_pProgram->GetHandle(), m_nLocation, rVector );

		return !CheckOpenGLState();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Variable::GetMatrix( Matrix4& rMatrix )
	{
		if ( !m_bReady ) 
		{
			return false;
		}

		glGetUniformfv( m_pProgram->GetHandle(), m_nLocation, rMatrix );

		return !CheckOpenGLState();
	}

	//-------------------------------------------------------------------------------------------------
	GLint Variable::GetLocation()
	{
		return m_nLocation;
	}

	//-------------------------------------------------------------------------------------------------
	std::string Variable::GetName()
	{
		return m_Name;
	}

	//-------------------------------------------------------------------------------------------------
	std::shared_ptr< Variable > Variable::Create( std::shared_ptr< Program > pProgram, std::string Name )
	{
		Variable::Ptr pVariable( new Variable );

		if ( !pVariable->SetProgram( pProgram ) )
		{
			return s_kDefault;
		}

		if ( !pVariable->SetName( Name ) )
		{
			return s_kDefault;
		}

		if ( !pVariable->Load() )
		{
			return s_kDefault;
		}

		return pVariable;
	}
}
