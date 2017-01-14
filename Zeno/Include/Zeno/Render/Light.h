#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Math/Vector3.h"
#include "Zeno/Math/Vector4.h"

namespace Zeno
{
	class Program;

	class ZENO_DLL Light
	{
	public:
		typedef std::shared_ptr< Light > Ptr;

		static const Ptr s_kDefault;

		Light();

		~Light();

		GLvoid SetProgram( std::shared_ptr< Program > pProgram );

		GLvoid SetAmbient( Vector4 Color );

		GLvoid SetDiffuse( Vector4 Color );

		GLvoid SetSpecular( Vector4 Color );

		// Update the data in shader program
		GLboolean Load();

		GLvoid Clear();

		GLboolean IsReady();

		static Ptr Create( std::shared_ptr< Program > pProgram, 
			Vector4 Ambient, Vector4 Diffuse, Vector4 Specular );

	private:
		GLboolean m_bReady;

		std::shared_ptr< Program > m_pProgram;

		Vector4 m_Ambient;

		Vector4 m_Diffuse;

		Vector4 m_Specular;

	};
}
