#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"
#include "Zeno/Render/Mesh.h"

class AABB
{
public:
	typedef std::shared_ptr< AABB > Ptr;

	static const Ptr s_kDefault;

	AABB();

	~AABB();

	bool SetProgram( Zeno::Program::Ptr pProgram );

	bool SetSize( float nLength, float nWidth, float nHeight );

	bool Load();

	bool IsReady();

	bool Draw();

	void Clear();

	void Move( float nSpeed, Zeno::Vector3 pntAxis );

	bool CheckCollision( Ptr Other );

	float GetLength();

	float GetWidth();

	float GetHeight();

	Zeno::Vector3 GetPosition();

	Zeno::Vector3 GetCenter();

	static Ptr Create( Zeno::Program::Ptr pProgram, 
		float nLength, float nWidth, float nHeight );

private:
	bool m_bReady;

	Zeno::Program::Ptr m_pProgram;

	Zeno::Mesh::Ptr m_pMesh;

	Zeno::Vector3 m_Position;

	Zeno::Vector3 m_LowPoint;

	Zeno::Vector3 m_HighPoint;

};