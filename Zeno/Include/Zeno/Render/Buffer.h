#pragma once

#include "Zeno/OpenGL.h"

namespace Zeno
{
	class ZENO_DLL Buffer
	{
	public:
		typedef std::shared_ptr< Buffer > Ptr;

		static const Ptr s_kDefault;

		Buffer();

		~Buffer();

		// Bind a buffer object to the specified buffer binding point.
		GLboolean Enable();

		// Unbind any buffer object previously bound.
		GLboolean Disable();

		GLboolean SetTarget( GLenum Target );

		GLboolean SetUsage( GLenum Usage );

		GLboolean SetAttribute( std::string Name, GLuint nSize );

		GLboolean SetData( GLvoid* pData, GLuint nSize );

		// Create and initialize the buffer object's data store.
		GLboolean Load();

		GLvoid Clear();

		GLboolean IsReady();

		GLuint GetName();

		GLuint GetSize();

		std::string GetAttribName();

		GLuint GetAttribSize();

		static Ptr Create( std::string AttribName, GLuint nAttribSize, 
			GLvoid* pData, GLuint nSize, GLenum Target, GLenum Usage );

	private:
		GLboolean m_bReady;

		GLuint m_nName;

		std::string m_AttribName;

		GLuint m_nAttribSize;

		GLenum m_Target;

		GLenum m_Usage;

		GLvoid* m_pData;

		GLuint m_nSize;

	};
}
