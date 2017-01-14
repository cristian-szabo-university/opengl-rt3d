#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Mesh.h"
#include "Zeno/Render/Material.h"
#include "Misc/Texture.h"

#include "Zeno/Math/Matrix4.h"

class Skybox
{
public:
	typedef std::shared_ptr< Skybox > Ptr;

	static const Ptr s_kDefault;

	Skybox();

	~Skybox();

	bool SetProgram( Zeno::Program::Ptr pProgram );

	bool SetSkybox( std::string* pFiles, GLfloat nSize );

	bool Load();

	bool IsReady();

	bool Draw();

	void Clear();

	static Ptr Create();

	static Ptr Create( Zeno::Program::Ptr pProgram, std::string* pFiles, GLfloat nBoxSize );

private:
	bool m_bReady;

	Zeno::Program::Ptr m_pProgram;

	std::vector< Zeno::Mesh::Ptr > m_vecMeshes;

	std::vector< std::string > m_vecFiles;

	GLfloat m_nBoxSize;

};
