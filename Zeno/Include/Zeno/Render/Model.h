/* Zeno Real Time 3D Graphics (ZenoRT3D)
---------------------------------------------------------------------------------------------------
Copyright (c) 2014, Ioan Cristian Szabo - cristian.szabo@videogamelab.co.uk. All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the 
following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions 
  and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this list of conditions
  and the following disclaimer in the documentation and/or other materials provided with the 
  distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-------------------------------------------------------------------------------------------------*/
#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Math/Matrix4.h"

namespace Zeno
{
	class Program;
	class Mesh;

	class ZENO_DLL Model
	{
	public:
		typedef std::shared_ptr< Model > Ptr;

		static const Ptr s_kDefault;

		Model();

		virtual ~Model();

		GLboolean SetProgram( std::shared_ptr< Program > pProgram );

		GLboolean SetFile( std::string FileModel, 
			std::string FileOption = "Unknown" );

		GLboolean SetAnim( GLint nAnimIdx );

		virtual GLboolean Load();

		virtual GLvoid Clear();

		GLboolean IsReady();

		virtual GLboolean Draw();

		virtual GLvoid Update( float nDeltaTime );

		static Ptr Create( std::shared_ptr< Program > pProgram, 
			std::string FileModel, std::string FileTexture );

	protected:
		GLboolean m_bReady;

		std::shared_ptr< Program > m_pProgram;

		std::shared_ptr< Mesh > m_pMesh;

		std::string m_FileModel;

		std::string m_FileOption;

		virtual bool LoadModel();

	private:
		struct Animation
		{
			std::string m_Name;

			GLint m_nStartFrame;

			GLint m_nEndFrame;
		};

		GLint m_nCurrentFrame;

		GLint m_nNextFrame;

		GLint m_nStartFrame;

		GLint m_nEndFrame;

		GLfloat m_nInterp;

		std::vector< Animation > m_vecAnimations;

		std::vector< std::vector< GLfloat > > m_vecFrameVerts;

		std::vector< GLfloat > m_vecAnimVerts;

		GLuint m_nNumVertices;

	};
}
