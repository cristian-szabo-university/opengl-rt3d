#pragma once

#include "Zeno/OpenGL.h"

namespace Zeno
{
	class Shader;
	class Variable;

	class ZENO_DLL Program
	{
	public:
		typedef std::shared_ptr< Program > Ptr;

		static const Ptr s_kDefault;

		Program();

		~Program();

		// Bind the shader program
		GLboolean Enable();

		// Unbind teh shader program
		GLboolean Disable();

		GLboolean AttachShader( std::shared_ptr< Shader > pShader );

		GLboolean AttachVariable( std::shared_ptr< Variable > pVariable );

		GLboolean Load();

		GLvoid Clear();

		GLboolean IsReady();

		GLuint GetHandle();

		std::string GetName();

		std::shared_ptr< Variable > GetVariable( std::string Name );

		static Ptr Create( std::string VertexShaderFile, std::string FragmentShaderFile );

	private:
		GLboolean m_bReady;

		GLuint m_nHandle;

		std::string m_Name;

		std::vector< std::shared_ptr< Shader > > m_vecShaders;

		std::vector< std::shared_ptr< Variable > > m_vecVariables;

	};
}
