#include "Zeno/Render/Light.h"
#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"

namespace Zeno
{
	const Light::Ptr Light::s_kDefault = Light::Ptr( new Light );

	//-------------------------------------------------------------------------------------------------
	Light::Light()
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	Light::~Light()
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Light::Load()
	{
		if ( m_bReady )
		{
			return false;
		}

		if ( !m_pProgram.get() || !m_pProgram->IsReady() )
		{
			return false;
		}

		Variable::Ptr pAmbientVar = Variable::Create( m_pProgram, "Light.Ambient" );

		if ( pAmbientVar->IsReady() )
		{
			pAmbientVar->UpdateVector( m_Ambient );
		}

		Variable::Ptr pDiffuseVar = Variable::Create( m_pProgram, "Light.Diffuse" );

		if ( pDiffuseVar->IsReady() )
		{
			pDiffuseVar->UpdateVector( m_Diffuse );
		}

		Variable::Ptr pSpecularVar = Variable::Create( m_pProgram, "Light.Specular" );

		if ( pSpecularVar->IsReady() )
		{
			pSpecularVar->UpdateVector( m_Specular );
		}

		m_bReady = true;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Light::Clear()
	{
		m_pProgram.reset();

		m_bReady = false;

		m_Ambient = Vector4( 0.0f );

		m_Diffuse = Vector4( 0.0f );

		m_Specular = Vector4( 0.0f );
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Light::IsReady()
	{
		return m_bReady;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Light::SetProgram( std::shared_ptr< Program > pProgram )
	{
		if ( !pProgram.get() || m_pProgram.get() )
		{
			return;
		}

		m_pProgram = pProgram;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Light::SetAmbient( Vector4 Color )
	{
		if ( Color.Length() == 0 )
		{
			return;
		}

		m_Ambient = Color;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Light::SetDiffuse( Vector4 Color )
	{
		if ( Color.Length() == 0 )
		{
			return;
		}

		m_Diffuse = Color;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Light::SetSpecular( Vector4 Color )
	{
		if ( Color.Length() == 0 )
		{
			return;
		}

		m_Specular = Color;
	}

	//-------------------------------------------------------------------------------------------------
	Light::Ptr Light::Create( std::shared_ptr< Program > pProgram, 
		Vector4 Ambient, Vector4 Diffuse, Vector4 Specular )
	{
		Light::Ptr pLight( new Light );

		pLight->SetProgram( pProgram );

		pLight->SetAmbient( Ambient );

		pLight->SetDiffuse( Diffuse );

		pLight->SetSpecular( Specular );

		if ( !pLight->Load() )
		{
			return s_kDefault;
		}

		return pLight;
	}
}
