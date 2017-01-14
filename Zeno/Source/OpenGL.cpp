#include <iostream>

#include "Zeno/OpenGL.h"

namespace Zeno
{
	//-------------------------------------------------------------------------------------------------
	GLboolean CheckShaderState( GLint nHandle )
	{
		int nStatus;

		glGetShaderiv( nHandle, GL_COMPILE_STATUS, &nStatus );

		if ( nStatus == GL_TRUE )
		{
			return true;
		}
	
		int max_length = 2048;
		int actual_length = 0;
		char log[2048];
	
		glGetShaderInfoLog ( nHandle, max_length, &actual_length, log );
	
		std::cout << "Log for shader: " << nHandle << std::endl;
		std::cout << log << std::endl;
	
		return false;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean CheckProgramState( GLint nHandle )
	{
		int nStatus;

		glGetProgramiv( nHandle, GL_LINK_STATUS, &nStatus );

		if ( nStatus == GL_TRUE )
		{
			return true;
		}

		int max_length = 2048;
		int actual_length = 0;
		char log[2048];

		glGetProgramInfoLog (nHandle, max_length, &actual_length, log);
	
		std::cout << "Log for program: " << nHandle << std::endl;
		std::cout << log << std::endl;

		return false;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean CheckProgramValid( GLint nHandle )
	{
		glValidateProgram ( nHandle );
	
		int nParams = -1;
  
		glGetProgramiv( nHandle, GL_VALIDATE_STATUS, &nParams );
	
		if ( GL_TRUE != nParams ) 
		{
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	GLboolean CheckOpenGLState()
	{
		GLenum Error = glGetError();

		if ( Error == GL_NO_ERROR ) 
		{
			return false;
		}

		switch ( Error ) 
		{
		// An unacceptable value is specified for an enumerated argument.
		case GL_INVALID_ENUM:
			{
				std::cout << "GL_INVALID_ENUM" << std::endl;         
			}
			break;

		// A numeric argument is out of range.
		case GL_INVALID_VALUE:
			{
				std::cout << "GL_INVALID_VALUE" << std::endl; 
			}
			break;

		// The specified operation is not allowed in the current state.
		case GL_INVALID_OPERATION:
			{
				std::cout << "GL_INVALID_OPERATION" << std::endl; 
			}
			break;

		// There is not enough memory left to execute the command.
		case GL_OUT_OF_MEMORY:
			{
				std::cout << "GL_OUT_OF_MEMORY" << std::endl; 
			}
			break;

		}

		return true;
	}
}
