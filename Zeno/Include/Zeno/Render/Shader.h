#pragma once

#include "Zeno/OpenGL.h"

namespace Zeno
{
	class ZENO_DLL Shader
	{
	public:
		typedef std::shared_ptr< Shader > Ptr;

		static const Ptr s_kDefault;

		Shader();

		~Shader();

		GLboolean SetType( GLenum Type );

		GLboolean SetFile( std::string FileName );

		GLboolean Load();

		GLvoid Clear();

		GLboolean IsReady();

		GLuint GetHandle();

		std::string GetName();

		static Ptr Create();

		static Ptr Create( GLenum Type, std::string FileName );

	private:
		GLboolean m_bReady;

		GLuint m_nHandle;

		GLenum m_Type;

		std::string m_FileName;

	};
}
