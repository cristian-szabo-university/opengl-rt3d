#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Mesh.h"
#include "Zeno/Render/Model.h"
#include "Zeno/Render/Material.h"

#include "Zeno/Math/Vector3.h"

#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

class Model : public Zeno::Model
{
public:
	typedef std::shared_ptr< Model > Ptr;

	static const Ptr s_kDefault;

	Model();

	virtual ~Model();

	virtual GLvoid Clear();

	virtual GLboolean Draw();

	virtual GLvoid Update( float nDeltaTime );

	static Ptr Create( std::shared_ptr< Zeno::Program > pProgram, 
		std::string ModelFile );

protected:
	virtual bool LoadModel();

private:
	const aiScene* m_pAIScene;

	std::vector< Zeno::Material::Ptr > m_vecMaterials;

	std::vector< Zeno::Mesh::Ptr > m_vecMeshes;

};
