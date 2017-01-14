#include "Zeno/Render/Material.h"
#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Texture.h"

namespace Zeno
{
	const Material::Ptr Material::s_kDefault = Material::Ptr( new Material );

	//-------------------------------------------------------------------------------------------------
	Material::Material()
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	Material::~Material()
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Material::Enable()
	{
		if ( !m_bReady )
		{
			return false;
		}

		m_pProgram->GetVariable( "Material.Ambient" )->UpdateVector( m_Ambient );

		m_pProgram->GetVariable( "Material.Diffuse" )->UpdateVector( m_Diffuse );

		m_pProgram->GetVariable( "Material.Specular" )->UpdateVector( m_Specular );

		m_pProgram->GetVariable( "Material.Shininess" )->UpdateValue( m_nShininess );

		if ( m_pTexture->IsReady() )
		{
			if ( !m_pTexture->Enable() )
			{
				return false;
			}
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Material::Disable()
	{
		if ( !m_bReady )
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

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Material::Load()
	{
		if ( m_bReady )
		{
			return false;
		}

		if ( !m_pProgram->IsReady() )
		{
			return false;
		}

		m_bReady = true;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Material::Clear()
	{
		m_bReady = false;

		m_pProgram = Program::s_kDefault;

		m_pTexture = Texture::s_kDefault;

		m_Ambient = Vector4( 0.0f );

		m_Diffuse = Vector4( 0.0f );

		m_Specular = Vector4( 0.0f );

		m_nShininess = 0.0f;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Material::IsReady()
	{
		return m_bReady;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Material::SetProgram( std::shared_ptr< Program > pProgram  )
	{
		if ( !pProgram.get() || m_pProgram->IsReady() )
		{
			return false;
		}

		Variable::Ptr pAmbientVar = Variable::Create( pProgram, "Material.Ambient" );

		if ( !pAmbientVar->IsReady() )
		{
			return false;
		}

		pProgram->AttachVariable( pAmbientVar );

		Variable::Ptr pDiffuseVar = Variable::Create( pProgram, "Material.Diffuse" );

		if ( !pDiffuseVar->IsReady() )
		{
			return false;
		}

		pProgram->AttachVariable( pDiffuseVar );

		Variable::Ptr pSpecularVar = Variable::Create( pProgram, "Material.Specular" );

		if ( !pSpecularVar->IsReady() )
		{
			return false;
		}

		pProgram->AttachVariable( pSpecularVar );

		Variable::Ptr pShininessVar = Variable::Create( pProgram, "Material.Shininess" );

		if ( !pShininessVar->IsReady() )
		{
			return false;
		}

		pProgram->AttachVariable( pShininessVar );

		m_pProgram = pProgram;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean Material::SetTexture( std::shared_ptr< Texture > pTexture  )
	{
		if ( !pTexture.get() )
		{
			return false;
		}

		if ( !pTexture->IsReady() || m_pTexture->IsReady() )
		{
			return false;
		}

		m_pTexture = pTexture;

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Material::SetAmbient( Vector4 Color )
	{
		m_Ambient = Color;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Material::SetDiffuse( Vector4 Color )
	{
		m_Diffuse = Color;
	}

	//-------------------------------------------------------------------------------------------------
	GLvoid Material::SetSpecular( Vector4 Color )
	{
		m_Specular = Color;
	}

	GLvoid Material::SetShininess( GLfloat nValue )
	{
		m_nShininess = nValue;
	}

	std::shared_ptr< Texture > Material::GetTexture()
	{
		return m_pTexture;
	}

	Material::Ptr Material::Create( std::shared_ptr< Program > pProgram, 
		Vector4 Ambient, Vector4 Diffuse, Vector4 Specular, GLfloat nShininess,
		std::string TextureFile )
	{
		Material::Ptr pMaterial( new Material );

		if ( !pMaterial->SetProgram( pProgram ) )
		{
			return s_kDefault;
		}

		Texture::Ptr pTexture = Texture::Create( GL_TEXTURE_2D, TextureFile );

		pMaterial->SetTexture( pTexture );

		pMaterial->SetAmbient( Ambient );

		pMaterial->SetDiffuse( Diffuse );

		pMaterial->SetSpecular( Specular );

		pMaterial->SetShininess( nShininess );

		if ( !pMaterial->Load() )
		{
			return s_kDefault;
		}

		return pMaterial;
	}

	Material::Ptr Material::Create( std::shared_ptr< Program > pProgram, 
		Vector4 Ambient, Vector4 Diffuse, Vector4 Specular, GLfloat nShininess )
	{
		return Create( pProgram, Ambient, Diffuse, Specular, nShininess, "Unknown" );
	}

}
