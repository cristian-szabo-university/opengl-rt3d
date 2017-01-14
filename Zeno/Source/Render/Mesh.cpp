#include "Zeno/Render/Mesh.h"
#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Buffer.h"
#include "Zeno/Render/Material.h"

namespace Zeno
{
	const Mesh::Ptr Mesh::s_kDefault = Mesh::Ptr( new Mesh );
	
	//-------------------------------------------------------------------------------------------------
	Mesh::Mesh()
	{
		m_nName = 0;

		Clear();
	}
	
	//-------------------------------------------------------------------------------------------------
	Mesh::~Mesh()
	{
		Clear();
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Mesh::Enable()
	{
		if ( !m_bReady )
		{
			return false;
		}

		glBindVertexArray( m_nName );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Mesh::Disable()
	{
		if ( !m_bReady )
		{
			return false;
		}

		glBindVertexArray( 0 );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Mesh::SetProgram( std::shared_ptr< Program > pProgram )
	{
		if ( !pProgram.get() || m_pProgram->IsReady() )
		{
			return false;
		}

		m_pProgram = pProgram;

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Mesh::SetMaterial( std::shared_ptr< Material > pMaterial )
	{
		if ( !pMaterial.get() || m_pMaterial->IsReady() )
		{
			return false;
		}

		m_pMaterial = pMaterial;

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Mesh::AttachBuffer( std::shared_ptr< Buffer > pBuffer )
	{
		if ( !pBuffer.get() || !pBuffer->IsReady() )
		{
			return false;
		}

		std::string BufferName = pBuffer->GetAttribName() + std::string( "Buffer" );

		auto iterBuffer = m_mapBuffers.find( BufferName );

		if ( iterBuffer != m_mapBuffers.end() )
		{
			return false;
		}

		m_mapBuffers.insert( std::make_pair( BufferName , pBuffer ) );

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Mesh::Load()
	{
		if ( m_bReady )
		{
			return false;
		}

		if ( !m_pProgram->IsReady() )
		{
			return false;
		}

		glGenVertexArrays( 1, &m_nName );

		if ( CheckOpenGLState() )
		{
			return false;
		}

		m_bReady = true;

		if ( !Enable() )
		{
			return false;
		}

		auto iterIndexBuffer = m_mapBuffers.find( "IndexBuffer" );

		if ( iterIndexBuffer != m_mapBuffers.end() )
		{
			iterIndexBuffer->second->Enable();
		}

		for ( auto iterBuffer = m_mapBuffers.begin();
			iterBuffer != m_mapBuffers.end();
			iterBuffer++ )
		{
			Buffer::Ptr pBuffer = iterBuffer->second;

			std::string AttribName = std::string( "in_" ) + pBuffer->GetAttribName();

			GLint nLocation = glGetAttribLocation( m_pProgram->GetHandle(), AttribName.c_str() );

			if ( nLocation < 0 )
			{
				continue;
			}

			pBuffer->Enable();

			glEnableVertexAttribArray( nLocation );

			glVertexAttribPointer( nLocation, pBuffer->GetAttribSize(), GL_FLOAT, GL_FALSE, 0, 0 );	

			pBuffer->Disable();
		}

		if ( !Disable() )
		{
			return false;
		}

		if ( iterIndexBuffer != m_mapBuffers.end() )
		{
			iterIndexBuffer->second->Disable();
		}

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Mesh::UpdateBuffer( std::shared_ptr< Buffer > pBuffer )
	{
		if ( !pBuffer.get() || !pBuffer->IsReady() )
		{
			return false;
		}

		std::string BufferName = pBuffer->GetAttribName() + std::string( "Buffer" );

		auto iterBuffer = m_mapBuffers.find( BufferName );

		if ( iterBuffer == m_mapBuffers.end() )
		{
			return false;
		}

		m_mapBuffers.erase( iterBuffer );

		if ( !Enable() )
		{
			return false;
		}

		m_mapBuffers.insert( std::make_pair( BufferName, pBuffer ) );

		std::string AttribName = std::string( "in_" ) + pBuffer->GetAttribName();

		GLint nLocation = glGetAttribLocation( m_pProgram->GetHandle(), AttribName.c_str() );

		if ( nLocation < 0 )
		{
			return false;
		}

		if ( !pBuffer->Enable() )
		{
			return false;
		}

		glEnableVertexAttribArray( nLocation );

		glVertexAttribPointer( nLocation, pBuffer->GetAttribSize(), GL_FLOAT, GL_FALSE, 0, 0 );	

		if ( !pBuffer->Disable() )
		{
			return false;
		}

		if ( !Disable() )
		{
			return false;
		}

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Mesh::Draw( GLenum Primitive )
	{
		if ( !m_bReady )
		{
			return false;
		}

		if ( !m_pProgram->Enable() )
		{
			return false;
		}

		if ( m_pMaterial->IsReady() )
		{
			if ( !m_pMaterial->Enable() )
			{
				return false;
			}
		}

		if ( !Enable() )
		{
			return false;
		}

		auto iterBuffer = m_mapBuffers.find( "IndexBuffer" );

		if ( iterBuffer == m_mapBuffers.end() )
		{
			iterBuffer = m_mapBuffers.find( "PositionBuffer" );

			if ( iterBuffer != m_mapBuffers.end() )
			{
				GLuint nBufferSize = iterBuffer->second->GetSize() / sizeof( GLfloat );

				GLuint nNumVertices = nBufferSize / iterBuffer->second->GetAttribSize();

				glDrawArrays( Primitive, 0, nNumVertices );

				if ( CheckOpenGLState() )
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			GLuint nIndices = iterBuffer->second->GetSize() / sizeof( GLuint );

			glDrawElements( Primitive, nIndices, GL_UNSIGNED_INT, 0 );

			if ( CheckOpenGLState() )
			{
				return false;
			}
		}
		
		if ( !Disable() )
		{
			return false;
		}

		if ( m_pMaterial->IsReady() )
		{
			if ( !m_pMaterial->Disable() )
			{
				return false;
			}
		}

		if ( !m_pProgram->Enable() )
		{
			return false;
		}

		return true;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLvoid Mesh::Clear()
	{
		m_bReady = false;

		m_pProgram = Zeno::Program::s_kDefault;

		m_pMaterial = Zeno::Material::s_kDefault;

		m_mapBuffers.clear();

		if ( m_nName )
		{
			glDeleteVertexArrays( 1, &m_nName );

			m_nName = 0;
		}
	}
	
	//-------------------------------------------------------------------------------------------------
	GLboolean Mesh::IsReady()
	{
		return m_bReady;
	}
	
	//-------------------------------------------------------------------------------------------------
	GLuint Mesh::GetName()
	{
		return m_nName;
	}
	
	//-------------------------------------------------------------------------------------------------
	Mesh::Ptr Mesh::Create( std::shared_ptr< Program > pProgram,
		GLuint nNumVertices, GLfloat* pVertices, GLfloat* pColours, GLfloat* pNormals, GLfloat* pTexCoords,
		GLuint nNumIndices, GLuint* pIndices )
	{
		Mesh::Ptr pMesh( new Mesh );

		if ( !pMesh->SetProgram( pProgram ) )
		{
			return s_kDefault;
		}

		Buffer::Ptr pVertexBuffer = Buffer::Create( "Position", 3, pVertices, nNumVertices * 3, GL_ARRAY_BUFFER, GL_STATIC_DRAW );

		if ( pVertexBuffer->IsReady() )
		{
			pMesh->AttachBuffer( pVertexBuffer );
		}

		Buffer::Ptr pColourBuffer = Buffer::Create( "Colour", 3, pColours, nNumVertices * 3, GL_ARRAY_BUFFER, GL_STATIC_DRAW );

		if ( pColourBuffer->IsReady() )
		{
			pMesh->AttachBuffer( pColourBuffer );
		}

		Buffer::Ptr pNormalBuffer = Buffer::Create( "Normal", 3, pNormals, nNumVertices * 3, GL_ARRAY_BUFFER, GL_STATIC_DRAW );

		if ( pNormalBuffer->IsReady() )
		{
			pMesh->AttachBuffer( pNormalBuffer );
		}

		Buffer::Ptr pTexCoordBuffer = Buffer::Create( "TexCoord", 2, pTexCoords, nNumVertices * 2, GL_ARRAY_BUFFER, GL_STATIC_DRAW );

		if ( pTexCoordBuffer->IsReady() )
		{
			pMesh->AttachBuffer( pTexCoordBuffer );
		}

		Buffer::Ptr pIndexBuffer = Buffer::Create( "Index", 1, pIndices, nNumIndices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW );

		if ( pIndexBuffer->IsReady() )
		{
			pMesh->AttachBuffer( pIndexBuffer );
		}

		if ( !pMesh->Load() )
		{
			return s_kDefault;
		}

		return pMesh;
	}
	
	//-------------------------------------------------------------------------------------------------
	Mesh::Ptr Mesh::Create( std::shared_ptr< Program > pProgram,
		GLuint nNumVertices, GLfloat* pVertices, GLfloat* pNormals, GLfloat* pTexCoords )
	{
		return Create( pProgram, nNumVertices, pVertices, nullptr, pNormals, pTexCoords, 0, nullptr );
	}

	//-------------------------------------------------------------------------------------------------
	Mesh::Ptr Mesh::Create( std::shared_ptr< Program > pProgram,
		GLuint nNumVertices, GLfloat* pVertices, GLfloat* pColours )
	{
		return Create( pProgram, nNumVertices, pVertices, pColours, nullptr, nullptr, 0, nullptr );
	}

	//-------------------------------------------------------------------------------------------------
	Mesh::Ptr Mesh::Create( std::shared_ptr< Program > pProgram,
		GLuint nNumVertices, GLfloat* pVertices )
	{
		return Create( pProgram, nNumVertices, pVertices, nullptr, nullptr, nullptr, 0, nullptr );
	}
}
