#include <iostream>
#include <fstream>

#include "Misc/Model.h"
#include "Misc/Texture.h"

#include "Zeno/Render/Variable.h"

#include "Zeno/Math/Matrix4.h"

const Model::Ptr Model::s_kDefault = Model::Ptr( new Model );

Model::Model()
{
	
}

Model::~Model()
{
	
}

GLvoid Model::Clear()
{
	m_vecMeshes.clear();

	m_vecMaterials.clear();

	Zeno::Model::Clear();
}

GLboolean Model::Draw()
{
	if ( !IsReady() )
	{
		return false;
	}

	for ( auto iterMesh = m_vecMeshes.begin();
		iterMesh != m_vecMeshes.end();
		iterMesh++ )
	{
		Zeno::Mesh::Ptr pMesh = *iterMesh;

		if ( !pMesh->Draw( GL_TRIANGLES ) )
		{
			return false;
		}
	}

	return true;
}

GLvoid Model::Update( float nDeltaTime )
{

}

Model::Ptr Model::Create( std::shared_ptr< Zeno::Program > pProgram, 
	std::string ModelFile )
{
	Model::Ptr pModel( new Model );

	if ( !pModel->SetProgram( pProgram ) )
	{
		return s_kDefault;
	}

	if ( !pModel->SetFile( ModelFile, std::string( "Unknown" ) ) )
	{
		return s_kDefault;
	}

	if ( !pModel->Load() )
	{
		return s_kDefault;
	}

	return pModel;
}

bool Model::LoadModel()
{
	m_pAIScene = aiImportFile( m_FileModel.c_str(), aiProcessPreset_TargetRealtime_Quality );

	if ( !m_pAIScene )
	{
		return false;
	}

	std::string Directory = m_FileModel.substr( 0, m_FileModel.find_last_of( "/" ) + 1 );
	aiString Path;
	aiColor4D AmbientClr, DiffuseClr, SpecularClr;

	for ( GLuint nMatIdx = 0; nMatIdx < m_pAIScene->mNumMaterials; nMatIdx++ )
	{
		aiMaterial* pAIMaterial = m_pAIScene->mMaterials[ nMatIdx ];

		aiGetMaterialColor( pAIMaterial, AI_MATKEY_COLOR_AMBIENT, &AmbientClr );

		aiGetMaterialColor( pAIMaterial, AI_MATKEY_COLOR_DIFFUSE, &DiffuseClr );

		aiGetMaterialColor( pAIMaterial, AI_MATKEY_COLOR_SPECULAR, &SpecularClr );

		aiGetMaterialTexture( pAIMaterial, aiTextureType_DIFFUSE, 0, &Path );

		Zeno::Material::Ptr pMaterial = Zeno::Material::Create
		(
			m_pProgram,
			Zeno::Vector4( AmbientClr.r, AmbientClr.g, AmbientClr.b, AmbientClr.a ),
			Zeno::Vector4( DiffuseClr.r, DiffuseClr.g, DiffuseClr.b, DiffuseClr.a ),
			Zeno::Vector4( SpecularClr.r, SpecularClr.g, SpecularClr.b, SpecularClr.a ),
			1.0f
		);

		std::string PathStr = Path.data;
		std::string TextureName = PathStr.substr( PathStr.find_last_of( "/$" ) + 1 );
		Texture::Ptr pTexture = Texture::Create( GL_TEXTURE_2D, Directory + TextureName );

		if ( pTexture->IsReady() )
		{
			pMaterial->SetTexture( pTexture );
		}

		if ( pMaterial->IsReady() )
		{
			m_vecMaterials.push_back( pMaterial );
		}

		Path.Clear();
	}

	std::vector< GLfloat > vecVertices;
	std::vector< GLfloat > vecColours;
	std::vector< GLfloat > vecNormals;
	std::vector< GLfloat > vecTexCoords;
	std::vector< GLuint > vecIndices;

	for ( GLuint nMeshIdx = 0; nMeshIdx < m_pAIScene->mNumMeshes; nMeshIdx++ )
	{
		aiMesh* pAIMesh = m_pAIScene->mMeshes[ nMeshIdx ];

		vecVertices.clear();
		vecNormals.clear();
		vecTexCoords.clear();
		vecIndices.clear();

		for ( GLuint nFaceIdx = 0; nFaceIdx < pAIMesh->mNumFaces; nFaceIdx++ ) 
		{
			aiFace* pAIFace = &pAIMesh->mFaces[ nFaceIdx ];

			for ( GLuint nIndex = 0; nIndex < pAIFace->mNumIndices; nIndex++ )
			{
				vecIndices.push_back( pAIFace->mIndices[ nIndex ] );
			}
		}

		for ( GLuint nIndex = 0; nIndex < pAIMesh->mNumVertices; nIndex++ )
		{
			if ( pAIMesh->HasPositions() )
			{
				aiVector3D* pAIVertex = &pAIMesh->mVertices[ nIndex ];

				vecVertices.push_back( pAIVertex->x );
				vecVertices.push_back( pAIVertex->y );
				vecVertices.push_back( pAIVertex->z );
			}

			if ( pAIMesh->HasNormals() )
			{
				aiVector3D* pAINormal = &pAIMesh->mNormals[ nIndex ];

				vecNormals.push_back( pAINormal->x );
				vecNormals.push_back( pAINormal->y );
				vecNormals.push_back( pAINormal->z );
			}

			if ( pAIMesh->HasTextureCoords( 0 ) )
			{
				aiVector3D* pAITexCoords = &pAIMesh->mTextureCoords[ 0 ][ nIndex ];

				vecTexCoords.push_back( pAITexCoords->x );
				vecTexCoords.push_back( pAITexCoords->y );
			}

			if ( pAIMesh->HasVertexColors( 0 ) )
			{
				aiColor4D* pAIColours = &pAIMesh->mColors[ 0 ][ nIndex ];

				vecColours.push_back( pAIColours->r );
				vecColours.push_back( pAIColours->g );
				vecColours.push_back( pAIColours->b );
			}
		}

		Zeno::Mesh::Ptr pMesh = Zeno::Mesh::Create
		(
			m_pProgram,
			pAIMesh->mNumVertices,
			vecVertices.data(),
			vecColours.data(),
			vecNormals.data(),
			vecTexCoords.data(),
			pAIMesh->mNumFaces * 3,
			vecIndices.data()
		);

		if ( pMesh->IsReady() )
		{
			m_vecMeshes.push_back( pMesh );
		}
		
		Zeno::Material::Ptr pMaterial = m_vecMaterials.at( pAIMesh->mMaterialIndex );

		pMesh->SetMaterial( pMaterial );
	}

	m_bReady = true;

	return true;
}
