#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Math/Vector4.h"

namespace Zeno
{
	class Program;
	class Texture;

	class ZENO_DLL Material
	{
	public:
		typedef std::shared_ptr< Material > Ptr;

		static const Ptr s_kDefault;

		Material();

		~Material();

		// Update material data in shader program 
		// and bind the texture if is available
		GLboolean Enable();

		// Unbind the texture if avaialable
		GLboolean Disable();

		GLboolean SetProgram( std::shared_ptr< Program > pProgram );

		GLboolean SetTexture( std::shared_ptr< Texture > pTexture );

		GLvoid SetAmbient( Vector4 Color );

		GLvoid SetDiffuse( Vector4 Color );

		GLvoid SetSpecular( Vector4 Color );

		GLvoid SetShininess( GLfloat nValue );
		
		GLboolean Load();

		GLvoid Clear();

		GLboolean IsReady();

		std::shared_ptr< Texture > GetTexture();

		static Ptr Create( std::shared_ptr< Program > pProgram, 
			Vector4 Ambient, Vector4 Diffuse, Vector4 Specular, GLfloat nShininess,
			std::string TextureFile );

		static Ptr Create( std::shared_ptr< Program > pProgram, 
			Vector4 Ambient, Vector4 Diffuse, Vector4 Specular, GLfloat nShininess );

	private:
		GLboolean m_bReady;

		std::shared_ptr< Program > m_pProgram;

		std::shared_ptr< Texture > m_pTexture;

		Vector4 m_Ambient;

		Vector4 m_Diffuse;

		Vector4 m_Specular;

		GLfloat m_nShininess;

	};
}
