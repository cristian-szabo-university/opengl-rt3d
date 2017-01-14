#include "Misc/Skybox.h"

const Skybox::Ptr Skybox::s_kDefault = Skybox::Create();

Skybox::Skybox()
{
	Clear();
}

Skybox::~Skybox()
{
	Clear();
}

bool Skybox::SetProgram( Zeno::Program::Ptr pProgram )
{
	if ( !pProgram.get() ||  m_pProgram.get() )
	{
		return false;
	}

	m_pProgram = pProgram;

	return true;
}

bool Skybox::SetSkybox( std::string* pFiles, GLfloat nSize )
{
	if ( !pFiles )
	{
		return false;
	}

	m_vecFiles.resize( 6 );

	std::copy( pFiles, pFiles + 6, m_vecFiles.begin() );

	if ( !nSize )
	{
		return false;
	}

	m_nBoxSize = nSize;

	return true;
}

bool Skybox::Load()
{
	if ( m_bReady )
	{
		return false;
	}

	GLfloat Vertices[] = 
	{
		// Front face
		m_nBoxSize, m_nBoxSize, m_nBoxSize, 
		m_nBoxSize, -m_nBoxSize, m_nBoxSize, 
		-m_nBoxSize, m_nBoxSize, m_nBoxSize, 
		-m_nBoxSize, -m_nBoxSize, m_nBoxSize,

		// Back face
		-m_nBoxSize, m_nBoxSize, -m_nBoxSize, 
		-m_nBoxSize, -m_nBoxSize, -m_nBoxSize, 
		m_nBoxSize, m_nBoxSize, -m_nBoxSize, 
		m_nBoxSize, -m_nBoxSize, -m_nBoxSize,

		// Left face
		-m_nBoxSize, m_nBoxSize, m_nBoxSize, 
		-m_nBoxSize, -m_nBoxSize, m_nBoxSize, 
		-m_nBoxSize, m_nBoxSize, -m_nBoxSize, 
		-m_nBoxSize, -m_nBoxSize, -m_nBoxSize,

		// Right face
		m_nBoxSize, m_nBoxSize, -m_nBoxSize, 
		m_nBoxSize, -m_nBoxSize, -m_nBoxSize, 
		m_nBoxSize, m_nBoxSize, m_nBoxSize, 
		m_nBoxSize, -m_nBoxSize, m_nBoxSize,

		// Top face
		-m_nBoxSize, m_nBoxSize, -m_nBoxSize, 
		m_nBoxSize, m_nBoxSize, -m_nBoxSize, 
		-m_nBoxSize, m_nBoxSize, m_nBoxSize, 
		m_nBoxSize, m_nBoxSize, m_nBoxSize,

		// Bottom face
		m_nBoxSize, -m_nBoxSize, -m_nBoxSize, 
		-m_nBoxSize, -m_nBoxSize, -m_nBoxSize, 
		m_nBoxSize, -m_nBoxSize, m_nBoxSize, 
		-m_nBoxSize, -m_nBoxSize, m_nBoxSize,

	};

	GLfloat TexCoords[] =
	{
		0.0f, 1.0f, 
		0.0f, 0.0f, 
		1.0f, 1.0f, 
		1.0f, 0.0f
	};

	GLfloat Normals[] = 
	{
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	for ( GLuint nIdx = 0; nIdx < 6; nIdx++ )
	{
		GLfloat MeshVerts[ 12 ];

		for ( GLuint i = 0; i < 12; i++ )
		{
			MeshVerts[ i ] = Vertices[ nIdx * 12 + i ];
		}

		GLfloat MeshNorms[12];

		for ( GLuint i = 0; i < 12; i++ )
		{
			MeshNorms[ i ] = Normals[ nIdx + i % 3 ];
		}

		Zeno::Material::Ptr pMaterial = Zeno::Material::Create
		(
			m_pProgram,
			Zeno::Vector4( 1.0f ),
			Zeno::Vector4( 1.0f ),
			Zeno::Vector4( 1.0f ),
			1.0f 
		);

		if ( !pMaterial->IsReady() )
		{
			return false;
		}

		Texture::Ptr pTexture = Texture::Create( GL_TEXTURE_2D, m_vecFiles[ nIdx ] );

		if ( !pTexture->IsReady() )
		{
			return false;
		}

		pMaterial->SetTexture( pTexture );

		Zeno::Mesh::Ptr pMesh = Zeno::Mesh::Create(
			m_pProgram, 4, MeshVerts, MeshNorms, TexCoords );

		if ( pMesh->IsReady() )
		{
			pMesh->SetMaterial( pMaterial );

			m_vecMeshes.push_back( pMesh );
		}
		else
		{
			return false;
		}
	}

	m_bReady = true;

	return true;
}

bool Skybox::IsReady()
{
	return m_bReady;
}

bool Skybox::Draw()
{
	if ( !m_bReady )
	{
		return false;
	}

	glDepthMask( GL_FALSE );

	Zeno::Matrix4 ModelMatrix;

	m_pProgram->GetVariable( "ModelMatrix" )->UpdateMatrix( ModelMatrix );

	for ( GLuint nIdx = 0; nIdx < 6; nIdx++ )
	{
		Zeno::Mesh::Ptr pMesh = m_vecMeshes[ nIdx ];

		if ( !pMesh->Draw( GL_TRIANGLE_STRIP ) )
		{
			return false;
		}
	}

	glDepthMask( GL_TRUE );

	return true;
}

void Skybox::Clear()
{
	m_bReady = false;

	m_pProgram.reset();

	m_vecMeshes.clear();

	m_vecFiles.clear();
}

Skybox::Ptr Skybox::Create()
{
	return std::make_shared< Skybox >();
}

Skybox::Ptr Skybox::Create( Zeno::Program::Ptr pProgram, std::string* pFiles, GLfloat nBoxSize )
{
	Skybox::Ptr pSkybox = Create();

	if ( !pSkybox->SetProgram( pProgram ) )
	{
		return s_kDefault;
	}

	if ( !pSkybox->SetSkybox( pFiles, nBoxSize ) )
	{
		return s_kDefault;
	}

	if ( !pSkybox->Load() )
	{
		return s_kDefault;
	}

	return pSkybox;
}
