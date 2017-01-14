#pragma once

#include "gl/glew.h"
#include "gl/wglew.h"

#include <gl/GL.h>
#include <gl/GLU.h>

#include "Config.h"

namespace Zeno
{
	GLboolean ZENO_DLL CheckShaderState( GLint nHandle );

	GLboolean ZENO_DLL CheckProgramState( GLint nHandle );

	GLboolean ZENO_DLL CheckProgramValid( GLint nHandle );

	GLboolean ZENO_DLL CheckOpenGLState();
}
