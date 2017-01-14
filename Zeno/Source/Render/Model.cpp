#include "Zeno/Render/Model.h"
#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Buffer.h"
#include "Zeno/Render/Mesh.h"
#include "Zeno/Render/Material.h"
#include "Zeno/Render/Texture.h"

GLfloat NormalTable[162][3] = 
{
	{ -0.525731f,  0.000000f,  0.850651f }, 
	{ -0.442863f,  0.238856f,  0.864188f }, 
	{ -0.295242f,  0.000000f,  0.955423f }, 
	{ -0.309017f,  0.500000f,  0.809017f }, 
	{ -0.162460f,  0.262866f,  0.951056f }, 
	{  0.000000f,  0.000000f,  1.000000f }, 
	{  0.000000f,  0.850651f,  0.525731f }, 
	{ -0.147621f,  0.716567f,  0.681718f }, 
	{  0.147621f,  0.716567f,  0.681718f }, 
	{  0.000000f,  0.525731f,  0.850651f }, 
	{  0.309017f,  0.500000f,  0.809017f }, 
	{  0.525731f,  0.000000f,  0.850651f }, 
	{  0.295242f,  0.000000f,  0.955423f }, 
	{  0.442863f,  0.238856f,  0.864188f }, 
	{  0.162460f,  0.262866f,  0.951056f }, 
	{ -0.681718f,  0.147621f,  0.716567f }, 
	{ -0.809017f,  0.309017f,  0.500000f }, 
	{ -0.587785f,  0.425325f,  0.688191f }, 
	{ -0.850651f,  0.525731f,  0.000000f }, 
	{ -0.864188f,  0.442863f,  0.238856f }, 
	{ -0.716567f,  0.681718f,  0.147621f }, 
	{ -0.688191f,  0.587785f,  0.425325f }, 
	{ -0.500000f,  0.809017f,  0.309017f }, 
	{ -0.238856f,  0.864188f,  0.442863f }, 
	{ -0.425325f,  0.688191f,  0.587785f }, 
	{ -0.716567f,  0.681718f, -0.147621f }, 
	{ -0.500000f,  0.809017f, -0.309017f }, 
	{ -0.525731f,  0.850651f,  0.000000f }, 
	{  0.000000f,  0.850651f, -0.525731f }, 
	{ -0.238856f,  0.864188f, -0.442863f }, 
	{  0.000000f,  0.955423f, -0.295242f }, 
	{ -0.262866f,  0.951056f, -0.162460f }, 
	{  0.000000f,  1.000000f,  0.000000f }, 
	{  0.000000f,  0.955423f,  0.295242f }, 
	{ -0.262866f,  0.951056f,  0.162460f }, 
	{  0.238856f,  0.864188f,  0.442863f }, 
	{  0.262866f,  0.951056f,  0.162460f }, 
	{  0.500000f,  0.809017f,  0.309017f }, 
	{  0.238856f,  0.864188f, -0.442863f }, 
	{  0.262866f,  0.951056f, -0.162460f }, 
	{  0.500000f,  0.809017f, -0.309017f }, 
	{  0.850651f,  0.525731f,  0.000000f }, 
	{  0.716567f,  0.681718f,  0.147621f }, 
	{  0.716567f,  0.681718f, -0.147621f }, 
	{  0.525731f,  0.850651f,  0.000000f }, 
	{  0.425325f,  0.688191f,  0.587785f }, 
	{  0.864188f,  0.442863f,  0.238856f }, 
	{  0.688191f,  0.587785f,  0.425325f }, 
	{  0.809017f,  0.309017f,  0.500000f }, 
	{  0.681718f,  0.147621f,  0.716567f }, 
	{  0.587785f,  0.425325f,  0.688191f }, 
	{  0.955423f,  0.295242f,  0.000000f }, 
	{  1.000000f,  0.000000f,  0.000000f }, 
	{  0.951056f,  0.162460f,  0.262866f }, 
	{  0.850651f, -0.525731f,  0.000000f }, 
	{  0.955423f, -0.295242f,  0.000000f }, 
	{  0.864188f, -0.442863f,  0.238856f }, 
	{  0.951056f, -0.162460f,  0.262866f }, 
	{  0.809017f, -0.309017f,  0.500000f }, 
	{  0.681718f, -0.147621f,  0.716567f }, 
	{  0.850651f,  0.000000f,  0.525731f }, 
	{  0.864188f,  0.442863f, -0.238856f }, 
	{  0.809017f,  0.309017f, -0.500000f }, 
	{  0.951056f,  0.162460f, -0.262866f }, 
	{  0.525731f,  0.000000f, -0.850651f }, 
	{  0.681718f,  0.147621f, -0.716567f }, 
	{  0.681718f, -0.147621f, -0.716567f }, 
	{  0.850651f,  0.000000f, -0.525731f }, 
	{  0.809017f, -0.309017f, -0.500000f }, 
	{  0.864188f, -0.442863f, -0.238856f }, 
	{  0.951056f, -0.162460f, -0.262866f }, 
	{  0.147621f,  0.716567f, -0.681718f }, 
	{  0.309017f,  0.500000f, -0.809017f }, 
	{  0.425325f,  0.688191f, -0.587785f }, 
	{  0.442863f,  0.238856f, -0.864188f }, 
	{  0.587785f,  0.425325f, -0.688191f }, 
	{  0.688191f,  0.587785f, -0.425325f }, 
	{ -0.147621f,  0.716567f, -0.681718f }, 
	{ -0.309017f,  0.500000f, -0.809017f }, 
	{  0.000000f,  0.525731f, -0.850651f }, 
	{ -0.525731f,  0.000000f, -0.850651f }, 
	{ -0.442863f,  0.238856f, -0.864188f }, 
	{ -0.295242f,  0.000000f, -0.955423f }, 
	{ -0.162460f,  0.262866f, -0.951056f }, 
	{  0.000000f,  0.000000f, -1.000000f }, 
	{  0.295242f,  0.000000f, -0.955423f }, 
	{  0.162460f,  0.262866f, -0.951056f }, 
	{ -0.442863f, -0.238856f, -0.864188f }, 
	{ -0.309017f, -0.500000f, -0.809017f }, 
	{ -0.162460f, -0.262866f, -0.951056f }, 
	{  0.000000f, -0.850651f, -0.525731f }, 
	{ -0.147621f, -0.716567f, -0.681718f }, 
	{  0.147621f, -0.716567f, -0.681718f }, 
	{  0.000000f, -0.525731f, -0.850651f }, 
	{  0.309017f, -0.500000f, -0.809017f }, 
	{  0.442863f, -0.238856f, -0.864188f }, 
	{  0.162460f, -0.262866f, -0.951056f }, 
	{  0.238856f, -0.864188f, -0.442863f }, 
	{  0.500000f, -0.809017f, -0.309017f }, 
	{  0.425325f, -0.688191f, -0.587785f }, 
	{  0.716567f, -0.681718f, -0.147621f }, 
	{  0.688191f, -0.587785f, -0.425325f }, 
	{  0.587785f, -0.425325f, -0.688191f }, 
	{  0.000000f, -0.955423f, -0.295242f }, 
	{  0.000000f, -1.000000f,  0.000000f }, 
	{  0.262866f, -0.951056f, -0.162460f }, 
	{  0.000000f, -0.850651f,  0.525731f }, 
	{  0.000000f, -0.955423f,  0.295242f }, 
	{  0.238856f, -0.864188f,  0.442863f }, 
	{  0.262866f, -0.951056f,  0.162460f }, 
	{  0.500000f, -0.809017f,  0.309017f }, 
	{  0.716567f, -0.681718f,  0.147621f }, 
	{  0.525731f, -0.850651f,  0.000000f }, 
	{ -0.238856f, -0.864188f, -0.442863f }, 
	{ -0.500000f, -0.809017f, -0.309017f }, 
	{ -0.262866f, -0.951056f, -0.162460f }, 
	{ -0.850651f, -0.525731f,  0.000000f }, 
	{ -0.716567f, -0.681718f, -0.147621f }, 
	{ -0.716567f, -0.681718f,  0.147621f }, 
	{ -0.525731f, -0.850651f,  0.000000f }, 
	{ -0.500000f, -0.809017f,  0.309017f }, 
	{ -0.238856f, -0.864188f,  0.442863f }, 
	{ -0.262866f, -0.951056f,  0.162460f }, 
	{ -0.864188f, -0.442863f,  0.238856f }, 
	{ -0.809017f, -0.309017f,  0.500000f }, 
	{ -0.688191f, -0.587785f,  0.425325f }, 
	{ -0.681718f, -0.147621f,  0.716567f }, 
	{ -0.442863f, -0.238856f,  0.864188f }, 
	{ -0.587785f, -0.425325f,  0.688191f }, 
	{ -0.309017f, -0.500000f,  0.809017f }, 
	{ -0.147621f, -0.716567f,  0.681718f }, 
	{ -0.425325f, -0.688191f,  0.587785f }, 
	{ -0.162460f, -0.262866f,  0.951056f }, 
	{  0.442863f, -0.238856f,  0.864188f }, 
	{  0.162460f, -0.262866f,  0.951056f }, 
	{  0.309017f, -0.500000f,  0.809017f }, 
	{  0.147621f, -0.716567f,  0.681718f }, 
	{  0.000000f, -0.525731f,  0.850651f }, 
	{  0.425325f, -0.688191f,  0.587785f }, 
	{  0.587785f, -0.425325f,  0.688191f }, 
	{  0.688191f, -0.587785f,  0.425325f }, 
	{ -0.955423f,  0.295242f,  0.000000f }, 
	{ -0.951056f,  0.162460f,  0.262866f }, 
	{ -1.000000f,  0.000000f,  0.000000f }, 
	{ -0.850651f,  0.000000f,  0.525731f }, 
	{ -0.955423f, -0.295242f,  0.000000f }, 
	{ -0.951056f, -0.162460f,  0.262866f }, 
	{ -0.864188f,  0.442863f, -0.238856f }, 
	{ -0.951056f,  0.162460f, -0.262866f }, 
	{ -0.809017f,  0.309017f, -0.500000f }, 
	{ -0.864188f, -0.442863f, -0.238856f }, 
	{ -0.951056f, -0.162460f, -0.262866f }, 
	{ -0.809017f, -0.309017f, -0.500000f }, 
	{ -0.681718f,  0.147621f, -0.716567f }, 
	{ -0.681718f, -0.147621f, -0.716567f }, 
	{ -0.850651f,  0.000000f, -0.525731f }, 
	{ -0.688191f,  0.587785f, -0.425325f }, 
	{ -0.587785f,  0.425325f, -0.688191f }, 
	{ -0.425325f,  0.688191f, -0.587785f }, 
	{ -0.425325f, -0.688191f, -0.587785f }, 
	{ -0.587785f, -0.425325f, -0.688191f }, 
	{ -0.688191f, -0.587785f, -0.425325f }
};

struct MD2_Header
{
	int nNumber;
	int nVersion;

	int nSkinWidth; 
	int nSkinHeight;

	int nFrameSize;

	int nNumSkins; 
	int nNumVertices;
	int nNumTexCoords;
	int nNumTriangles;
	int nNumGLcmds;
	int nNumFrames;

	int nOffsetSkins;
	int nOffsetTexCoords;
	int nOffsetTriangles;
	int nOffsetFrames;
	int nOffsetGLcmds;
	int nOffsetEnd;
};

struct MD2_Skin
{
	char name[ 64 ];
};

struct MD2_TexCoord
{
	short s;

	short t;
};

struct MD2_Triangle
{
	unsigned short nVertex[ 3 ];

	unsigned short nTexCoord[ 3 ];
};

struct MD2_Vertex
{
	unsigned char VertexIndex[ 3 ];

	unsigned char NormalIndex;
};

struct MD2_Frame
{
	GLfloat nScale[ 3 ];

	GLfloat nTranslate[ 3 ];

	char Name[ 16 ];

	MD2_Vertex* pVertices;
};

const int MD2_Number = 'I' + ('D'<<8) + ('P'<<16) + ('2'<<24);

const int MD2_Version = 8;

namespace Zeno
{
	const Model::Ptr Model::s_kDefault = Model::Ptr( new Model );
	
	//-------------------------------------------------------------------------------------------------
	Model::Model()
	{
		Clear();
	}
	
	//-------------------------------------------------------------------------------------------------
	Model::~Model()
	{
		Clear();
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Model::SetProgram( std::shared_ptr< Program > pProgram )
	{
		if ( !pProgram.get() || m_pProgram->IsReady() )
		{
			return false;
		}

		m_pProgram = pProgram;

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Model::SetFile( std::string ModelFile, std::string TextureFile )
	{
		if ( ModelFile.empty() || m_FileModel != std::string( "Unknown" ) )
		{
			return false;
		}

		m_FileModel = ModelFile;

		if ( TextureFile.empty() || m_FileOption != std::string( "Unknown" ) )
		{
			return false;
		}

		m_FileOption = TextureFile;

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Model::SetAnim( GLint nAnimIdx )
	{
		if ( nAnimIdx < 0 || nAnimIdx >= (int)m_vecAnimations.size() )
		{
			return false;
		}

		Animation* pAnim = &m_vecAnimations.at( nAnimIdx );

		m_nCurrentFrame = pAnim->m_nStartFrame;

		m_nNextFrame = m_nCurrentFrame + 1;

		m_nStartFrame = pAnim->m_nStartFrame;

		m_nEndFrame = pAnim->m_nEndFrame;

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Model::Load()
	{
		if ( m_bReady )
		{
			return false;
		}

		if ( !m_pProgram->IsReady() )
		{
			return false;
		}

		if ( !LoadModel() )
		{
			return false;
		}

		m_bReady = true;
	
		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLvoid Model::Clear()
	{
		m_bReady = false;

		m_nInterp = 0.0f;

		m_nNumVertices = 0;

		m_pProgram = Zeno::Program::s_kDefault;

		m_pMesh = Zeno::Mesh::s_kDefault;

		m_FileModel = m_FileOption = "Unknown";

		m_vecAnimations.clear();

		m_vecAnimVerts.clear();

		m_vecFrameVerts.clear();
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Model::IsReady()
	{
		return m_bReady;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Model::Draw()
	{
		if ( !m_bReady )
		{
			return false;
		}

		if ( !m_pMesh->Draw( GL_TRIANGLES ) )
		{
			return false;
		}

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	void Model::Update( float nDeltaTime )
	{
		// _currFrame must range between startFrame and endFrame
		if( m_nCurrentFrame < m_nStartFrame || m_nCurrentFrame > m_nEndFrame )
		{
			m_nCurrentFrame = m_nStartFrame;

			m_nNextFrame = m_nStartFrame + 1;
		}

		m_nInterp += nDeltaTime;

		// Compute current and next frames.
		if ( m_nInterp >= ( 60.0f / 1000.0f ) )
		{
			m_nInterp = 0.0f;
		
			m_nCurrentFrame = m_nNextFrame;
		
			m_nNextFrame++;

			if ( m_nNextFrame >= m_nEndFrame + 1 )
			{
				m_nNextFrame = m_nStartFrame;
			}
		}

		if ( m_nInterp == 0.0f )
		{
			std::copy( m_vecFrameVerts[ m_nCurrentFrame ].begin(), m_vecFrameVerts[ m_nCurrentFrame ].end(), m_vecAnimVerts.begin() );

			Buffer::Ptr pBuffer = Buffer::Create( "Position", 3, m_vecAnimVerts.data(), m_nNumVertices * 3, GL_ARRAY_BUFFER, GL_STATIC_DRAW );

			m_pMesh->UpdateBuffer( pBuffer );	
		}
		else 
		{
			for ( GLuint i = 0; i < m_nNumVertices * 3; i++ )
			{
				m_vecAnimVerts[i] = m_vecFrameVerts[ m_nCurrentFrame ][ i ] + 
					m_nInterp * ( m_vecFrameVerts[ m_nNextFrame ][ i ] - 
					m_vecFrameVerts[ m_nCurrentFrame ][ i ] );
			}
		}
	}
	
	//-------------------------------------------------------------------------------------------------
	Model::Ptr Model::Create( std::shared_ptr< Program > pProgram, 
		std::string FileModel, std::string FileTexture )
	{
		Model::Ptr pModel( new Model );

		if ( !pModel->SetProgram( pProgram ) )
		{
			return false;
		}

		if ( !pModel->SetFile( FileModel, FileTexture ) )
		{
			return false;
		}

		if ( !pModel->Load() )
		{
			return s_kDefault;
		}

		return pModel;
	}

	bool Model::LoadModel()
	{
		MD2_Header Header;
		MD2_Skin* pSkins;
		MD2_TexCoord* pTexCoords;
		MD2_Triangle* pTriangles;
		MD2_Frame* pFrames;

		Material::Ptr pMaterial = Material::Create( m_pProgram, 
			Vector4( 1.0f ), Vector4( 1.0f ), Vector4( 1.0f ), 1.0f, m_FileOption );

		if ( !pMaterial->IsReady() )
		{
			return false;
		}

		// Open the file
		std::ifstream File( m_FileModel.c_str (), std::ios::binary);

		if ( File.fail() )
		{
			return false;
		}

		// Read header
		File.read( reinterpret_cast< char* >( &Header ), sizeof(MD2_Header) );

		// Check if ident and version are valid
		if ( Header.nNumber != MD2_Number )
		{
			return false;
		}

		if ( Header.nVersion != MD2_Version )
		{
			return false;
		}

		// Memory allocation for model data
		pSkins = new MD2_Skin[ Header.nNumSkins ];
		pTexCoords = new MD2_TexCoord[ Header.nNumTexCoords ];
		pTriangles = new MD2_Triangle[ Header.nNumTriangles ];
		pFrames = new MD2_Frame[ Header.nNumFrames ];

		// Read skin names
		File.seekg( Header.nOffsetSkins, std::ios::beg );
		File.read( reinterpret_cast< char* >( pSkins ), sizeof( MD2_Skin ) * Header.nNumSkins );

		// Read texture coords.
		File.seekg( Header.nOffsetTexCoords, std::ios::beg );
		File.read( reinterpret_cast< char* >( pTexCoords ), sizeof( MD2_TexCoord ) * Header.nNumTexCoords );

		// Read triangle data
		File.seekg( Header.nOffsetTriangles, std::ios::beg );
		File.read( reinterpret_cast< char* >( pTriangles ), sizeof( MD2_Triangle ) * Header.nNumTriangles );

		// Read frames
		File.seekg( Header.nOffsetFrames, std::ios::beg );

		for ( int i = 0; i < Header.nNumFrames; ++i )
		{
			// Memory allocation for the vertices of this frame
			pFrames[ i ].pVertices = new MD2_Vertex[ Header.nNumVertices ];

			// Read frame data
			File.read( reinterpret_cast< char* >( &pFrames[ i ].nScale ), sizeof( GLfloat ) * 3 );
			File.read( reinterpret_cast< char* >( &pFrames[ i ].nTranslate ), sizeof( GLfloat ) * 3 );
			File.read( reinterpret_cast< char* >( &pFrames[ i ].Name ), sizeof( char ) * 16 );
			File.read( reinterpret_cast< char* >( pFrames[ i ].pVertices ), sizeof( MD2_Vertex ) * Header.nNumVertices );
		}

		// Close file
		File.close();

		std::string CurrentAnim;
		Animation Anim;

		for (int i = 0; i < Header.nNumFrames; ++i)
		{
			std::string FrameName = pFrames[i].Name;
			std::string FrameAnim;

			// Extract animation name from frame name
			std::string::size_type len = FrameName.find_first_of("0123456789");
		
			if ((len == FrameName.length () - 3) && (FrameName[len] != '0'))
			{
				len++;
			}

			FrameAnim.assign(FrameName, 0, len);

			if ( CurrentAnim != FrameAnim )
			{
				if (i > 0)
				{
					Anim.m_Name.assign( CurrentAnim );

					m_vecAnimations.push_back( Anim );
				}

				Anim.m_nStartFrame = i;

				Anim.m_nEndFrame = i;

				CurrentAnim = FrameAnim;
			}
			else
			{
				Anim.m_nEndFrame = i;
			}
		}

		Anim.m_Name.assign( CurrentAnim );

		m_vecAnimations.push_back( Anim );

		m_nNumVertices = Header.nNumTriangles * 3;
		
		std::vector< GLfloat > vecNormals;
		std::vector< GLfloat > vecTexCoords;

		MD2_Frame* pFrame = &pFrames[ 0 ];

		for ( GLint i = 0; i < Header.nNumTriangles; ++i )
		{
			for ( GLint j = 0; j < 3; ++j )
			{
				MD2_Vertex* pVertex = &pFrame->pVertices[ pTriangles[ i ].nVertex[ j ] ];
				MD2_TexCoord* pTexCoord = &pTexCoords[ pTriangles[ i ].nTexCoord[ j ] ];

				vecTexCoords.push_back( GLfloat( pTexCoord->s ) / Header.nSkinWidth );
				vecTexCoords.push_back( GLfloat( pTexCoord->t ) / Header.nSkinHeight );

				vecNormals.push_back( NormalTable[ pVertex->NormalIndex ][ 0 ] );
				vecNormals.push_back( NormalTable[ pVertex->NormalIndex ][ 1 ] );
				vecNormals.push_back( NormalTable[ pVertex->NormalIndex ][ 2 ] );
			}
		}

		std::vector< GLfloat > vecVertices;

		for ( GLint k = 0; k < Header.nNumFrames; ++k ) 
		{
			pFrame = &pFrames[ k ];

			vecVertices.clear();

			for ( GLint i = 0; i < Header.nNumTriangles; ++i )
			{
				for ( GLint j = 0; j < 3; ++j )
				{
					MD2_Vertex* pVertex = &pFrame->pVertices[ pTriangles[ i ].nVertex[ j ] ];

					vecVertices.push_back( pFrame->nScale[ 0 ] * pVertex->VertexIndex[ 0 ] + pFrame->nTranslate[ 0 ] );
					vecVertices.push_back( pFrame->nScale[ 1 ] * pVertex->VertexIndex[ 1 ] + pFrame->nTranslate[ 1 ] );
					vecVertices.push_back( pFrame->nScale[ 2 ] * pVertex->VertexIndex[ 2 ] + pFrame->nTranslate[ 2 ]);
				}
			}

			m_vecFrameVerts.push_back( vecVertices );
		}

		m_vecAnimVerts.resize( m_vecFrameVerts[0].size() );

		std::copy( m_vecFrameVerts[0].begin(), m_vecFrameVerts[0].end(), m_vecAnimVerts.begin() );
	
		m_pMesh = Mesh::Create( m_pProgram, m_nNumVertices, m_vecAnimVerts.data(), vecNormals.data(), vecTexCoords.data() );

		if ( !m_pMesh->IsReady() )
		{
			return false;
		}

		m_pMesh->SetMaterial( pMaterial );

		if ( !SetAnim( 0 ) )
		{
			return false;
		}
		
		return true;
	}
}
