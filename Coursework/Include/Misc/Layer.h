#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Mesh.h"
#include "Zeno/Render/Texture.h"

#include "Misc/Texture.h"
#include "Misc/Font.h"

class Layer
{
public:
	typedef std::shared_ptr< Layer > Ptr;

	static const Ptr s_kDefault;

	Layer();

	virtual ~Layer();

	bool SetProgram( Zeno::Program::Ptr pProgram );

	bool SetMesh( Zeno::Mesh::Ptr pMesh );

	bool SetTexture( Zeno::Texture::Ptr pTexture );

	virtual bool Load();

	virtual bool Draw( Zeno::Vector3 Position, float nScale = 1.0f );

	bool IsReady();

	virtual void Clear();

	static Ptr Create( Zeno::Program::Ptr pProgram, 
		Zeno::Texture::Ptr pTexture );

protected:
	bool m_bReady;

	Zeno::Program::Ptr m_pProgram;

	Zeno::Mesh::Ptr m_pMesh;

	Zeno::Texture::Ptr m_pTexture;

	Zeno::Matrix4 m_ModelMatrix;

};
