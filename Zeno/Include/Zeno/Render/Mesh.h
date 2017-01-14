#pragma once

#include "Zeno/OpenGL.h"

namespace Zeno
{
	class Program;
	class Buffer;
	class Material;

	class ZENO_DLL Mesh
	{
	public:
		typedef std::shared_ptr< Mesh > Ptr;

		static const Ptr s_kDefault;

		Mesh();

		~Mesh();

		// Bind a buffer array to the specified buffer binding point.
		GLboolean Enable();

		// Unbind any buffer array previously bound.
		GLboolean Disable();

		GLboolean SetProgram( std::shared_ptr< Program > pProgram );

		GLboolean SetMaterial( std::shared_ptr< Material > pMaterial );

		GLboolean AttachBuffer( std::shared_ptr< Buffer > pBuffer );

		// Create and initialize the buffer array's data as well as enabling
		// the attributes index to the corresponding vertex attribute.
		GLboolean Load();

		GLboolean UpdateBuffer( std::shared_ptr< Buffer > pBuffer );

		// Draw the vertices with or without index buffer.
		GLboolean Draw( GLenum Primitive );

		GLvoid Clear();

		GLboolean IsReady();

		GLuint GetName();

		static Ptr Create( std::shared_ptr< Program > pProgram,
			GLuint nNumVertices, GLfloat* pVertices, GLfloat* pColours, GLfloat* pNormals, GLfloat* pTexCoords,
			GLuint nNumIndices, GLuint* pIndices );

		static Ptr Create( std::shared_ptr< Program > pProgram,
			GLuint nNumVertices, GLfloat* pVertices, GLfloat* pNormals, GLfloat* pTexCoords );

		static Ptr Create( std::shared_ptr< Program > pProgram,
			GLuint nNumVertices, GLfloat* pVertices, GLfloat* pColours );

		static Ptr Create( std::shared_ptr< Program > pProgram,
			GLuint nNumVertices, GLfloat* pVertices );

	private:
		GLboolean m_bReady;

		GLuint m_nName;

		std::shared_ptr< Program > m_pProgram;

		std::shared_ptr< Material > m_pMaterial;

		std::map< std::string, std::shared_ptr< Buffer > > m_mapBuffers;

	};
}
