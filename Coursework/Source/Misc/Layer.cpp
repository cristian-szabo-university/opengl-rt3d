#include "Misc/Layer.h"

const Layer::Ptr Layer::s_kDefault = Layer::Ptr( new Layer );

Layer::Layer()
{
	Clear();
}

Layer::~Layer()
{
	Clear();
}

bool Layer::SetProgram( Zeno::Program::Ptr pProgram )
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

	pModelMatVar->UpdateMatrix( Zeno::Matrix4() );

	pProgram->AttachVariable( pModelMatVar );

	m_pProgram = pProgram;

	return true;
}

bool Layer::SetMesh( Zeno::Mesh::Ptr pMesh )
{
	if ( !pMesh.get() || m_pMesh->IsReady() )
	{
		return false;
	}

	m_pMesh = pMesh;

	return true;
}

bool Layer::SetTexture( Zeno::Texture::Ptr pTexture )
{
	if ( !pTexture.get() || m_pTexture->IsReady() )
	{
		return false;
	}

	m_pTexture = pTexture;

	return true;
}

bool Layer::Load()
{
	if ( m_bReady )
	{
		return false;
	}

	if ( !m_pProgram->IsReady() )
	{
		return false;
	}

	if ( !m_pMesh->IsReady() )
	{
		return false;
	}

	if ( !m_pTexture->IsReady() )
	{
		return false;
	}

	m_bReady = true;

	return true;
}

bool Layer::Draw( Zeno::Vector3 Position, float nScale )
{
	if ( !m_bReady )
	{
		return false;
	}

	m_ModelMatrix.Translate( Position );

	m_ModelMatrix.Scale( Zeno::Vector3( nScale ) );

	m_pProgram->GetVariable( "ModelMatrix" )->UpdateMatrix( m_ModelMatrix );

	if ( !m_pTexture->Enable() )
	{
		return false;
	}

	if ( !m_pMesh->Draw( GL_TRIANGLE_STRIP ) )
	{
		return false;
	}

	if ( !m_pTexture->Disable() )
	{
		return false;
	}

	m_ModelMatrix.Identity();

	return true;
}

bool Layer::IsReady()
{
	return m_bReady;
}

void Layer::Clear()
{
	m_bReady = false;

	m_pProgram = Zeno::Program::s_kDefault;

	m_pMesh = Zeno::Mesh::s_kDefault;

	m_pTexture = Zeno::Texture::s_kDefault;
}

Layer::Ptr Layer::Create( Zeno::Program::Ptr pProgram, Zeno::Texture::Ptr pTexture )
{
	Ptr pLayer( new Layer );

	if ( !pLayer->SetProgram( pProgram ) )
	{
		return s_kDefault;
	}

	if ( !pLayer->SetTexture( pTexture ) )
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

	if ( !pLayer->SetMesh( pMesh ) )
	{
		return s_kDefault;
	}

	if ( !pLayer->Load() )
	{
		return s_kDefault;
	}

	return pLayer;
}
