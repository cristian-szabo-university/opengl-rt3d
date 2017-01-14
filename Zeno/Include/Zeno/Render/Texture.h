#pragma once

#include "Zeno/OpenGL.h"

namespace Zeno
{
	class ZENO_DLL Texture
	{
	public:
		typedef std::shared_ptr< Texture > Ptr;

		static const Ptr s_kDefault;

		Texture();

		virtual ~Texture();

		// Bind the texture
		GLboolean Enable();

		// Unbind the texture
		GLboolean Disable();

		GLboolean SetTarget( GLenum Target );

		virtual GLboolean SetFile( std::string FileName );

		virtual GLboolean SetPixels( GLvoid* pData,
			GLuint nWidth, GLuint nHeight, GLuint nBPP );

		GLboolean SetSampler( GLenum Sampler, GLenum Filter );

		// Load texture in OpenGL buffer
		virtual GLboolean Load();

		virtual GLvoid Clear();

		GLboolean IsReady();

		std::string GetName();

		GLuint GetWidth();

		GLuint GetHeight();

		static Ptr Create( GLenum Target, std::string FileName );

		static Ptr Create( GLenum Target, GLvoid* pData,
			GLuint nWidth, GLuint nHeight, GLuint nBPP );

	protected:
		GLboolean m_bReady;

		GLenum m_Target;

		GLuint m_nName;

		GLuint m_nSampler;

		std::string m_FileName;

		GLubyte* m_pData;

		GLuint m_nBPP;

		GLuint m_nWidth;

		GLuint m_nHeight;

		virtual GLboolean LoadTexture();

	};
}
