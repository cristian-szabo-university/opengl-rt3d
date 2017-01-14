#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Math/Vector3.h"
#include "Zeno/Math/Vector4.h"
#include "Zeno/Math/Matrix4.h"

namespace Zeno
{
	class Program;

	class ZENO_DLL Variable
	{
	public:
		typedef std::shared_ptr< Variable > Ptr;

		static const Ptr s_kDefault;

		Variable();

		~Variable();

		GLboolean SetProgram( std::shared_ptr< Program > pProgram );

		GLboolean SetName( std::string Name );

		GLboolean Load();

		GLboolean UpdateValue( float nValue );

		GLboolean UpdateVector( Vector3 Vector );

		GLboolean UpdateVector( Vector4 Vector );

		GLboolean UpdateMatrix( Matrix4 Matrix );

		GLvoid Clear();

		GLboolean IsReady();

		GLboolean GetValue( float& rValue );

		GLboolean GetVector( Vector3& rVector );

		GLboolean GetVector( Vector4& rVector );

		GLboolean GetMatrix( Matrix4& rMatrix );

		GLint GetLocation();

		std::string GetName();

		static Ptr Create( std::shared_ptr< Program > pShader, std::string Name );

	private:
		GLboolean m_bReady;

		std::shared_ptr< Program > m_pProgram;
	
		std::string m_Name;

		GLint m_nLocation;

	};
}
