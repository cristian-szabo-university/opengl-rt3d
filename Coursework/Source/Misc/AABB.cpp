#include "Misc/AABB.h"

const AABB::Ptr AABB::s_kDefault = AABB::Ptr( new AABB );

AABB::AABB()
{
	Clear();
}

AABB::~AABB()
{
	Clear();
}

bool AABB::SetProgram( Zeno::Program::Ptr pProgram )
{
	if ( !pProgram.get() || m_pProgram->IsReady() )
	{
		return false;
	}

	m_pProgram = pProgram;

	return true;
}

bool AABB::SetSize( float nLength, float nWidth, float nHeight )
{
	m_LowPoint = Zeno::Vector3( 0.0f );
	m_HighPoint = Zeno::Vector3( nWidth, nHeight, nLength );

	return true;
}

bool AABB::Load()
{
	if ( m_bReady )
	{
		return false;
	}

	if ( !m_pProgram->IsReady() )
	{
		return false;
	}

	GLfloat Vertices[] = 
	{	
		// Bottom square
		m_LowPoint.m_S.X, m_LowPoint.m_S.Y, m_LowPoint.m_S.Z,		
		m_HighPoint.m_S.X, m_LowPoint.m_S.Y, m_LowPoint.m_S.Z,		
		m_LowPoint.m_S.X, m_HighPoint.m_S.Y, m_LowPoint.m_S.Z,		
		m_LowPoint.m_S.X, m_LowPoint.m_S.Y, m_HighPoint.m_S.Z,

			// Top square
		m_HighPoint.m_S.X, m_HighPoint.m_S.Y, m_LowPoint.m_S.Z,		
		m_HighPoint.m_S.X, m_LowPoint.m_S.Y, m_HighPoint.m_S.Z,		
		m_LowPoint.m_S.X, m_HighPoint.m_S.Y, m_HighPoint.m_S.Z,		
		m_HighPoint.m_S.X, m_HighPoint.m_S.Y, m_HighPoint.m_S.Z,		
	};

	GLuint Indices[] = 
	{	
		// Bottom
		0, 3, 1, 
		1, 3, 5,

		// Top
		2, 6, 4, 
		4, 6, 7,

		// Front
		0, 2, 1, 
		1, 2, 4,

		// Back
		3, 6, 5, 
		5, 6, 7,

		// Left
		0, 2, 3, 
		3, 2, 6,

		// Right
		1, 4, 5, 
		5, 4, 7 
	};

	m_pMesh = Zeno::Mesh::Create( m_pProgram,
		8, Vertices, nullptr, nullptr, nullptr, 
		36, Indices );

	if ( !m_pMesh->IsReady() )
	{
		return false;
	}

	m_bReady = true;

	return true;
}

bool AABB::IsReady()
{
	return m_bReady;
}

bool AABB::Draw()
{
	if ( !m_bReady )
	{
		return false;
	}

	Zeno::Matrix4 matModel;

	matModel.Translate( m_Position );

	m_pProgram->GetVariable( "ModelMatrix" )->UpdateMatrix( matModel );

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	if ( !m_pMesh->Draw( GL_TRIANGLES ) )
	{
		return false;
	}

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		
	return true;	
}

void AABB::Move( float nSpeed, Zeno::Vector3 pntAxis )
{
	m_Position += pntAxis * nSpeed;

	m_LowPoint += pntAxis * nSpeed;

	m_HighPoint += pntAxis * nSpeed;
}

float AABB::GetLength()
{
	Zeno::Vector3 vecLength = Zeno::Vector3( m_LowPoint.m_S.X, m_LowPoint.m_S.Y, m_HighPoint.m_S.Z ) - m_LowPoint;

	return vecLength.Length();
}

float AABB::GetWidth()
{
	Zeno::Vector3 vecWidth = Zeno::Vector3( m_HighPoint.m_S.X, m_LowPoint.m_S.Y, m_LowPoint.m_S.Z ) - m_LowPoint;

	return vecWidth.Length();
}

float AABB::GetHeight()
{
	Zeno::Vector3 vecHeight = Zeno::Vector3( m_LowPoint.m_S.X, m_HighPoint.m_S.Y, m_LowPoint.m_S.Z ) - m_LowPoint;

	return vecHeight.Length();
}

Zeno::Vector3 AABB::GetPosition()
{
	return m_Position;
}

Zeno::Vector3 AABB::GetCenter()
{
	return ( m_HighPoint - m_LowPoint ) * 0.5f;
}

bool AABB::CheckCollision( Ptr Other )
{
	// The sides of the rectangles
	float nLeftA, nLeftB;
	float nRightA, nRightB;
	float nTopA, nTopB;
	float nBottomA, nBottomB;

	// Calculate the sides of rect A
	nLeftA = m_Position.m_S.X;
	nRightA = m_Position.m_S.X + GetWidth();
	nTopA = m_Position.m_S.Z;
	nBottomA = m_Position.m_S.Z + GetLength();

	//Calculate the sides of rect B
	nLeftB = Other->m_Position.m_S.X;
	nRightB = Other->m_Position.m_S.X + Other->GetWidth();
	nTopB = Other->m_Position.m_S.Z;
	nBottomB = Other->m_Position.m_S.Z + Other->GetLength();

	//If any of the sides from A are outside of B
	if ( nBottomA <= nTopB )
	{
		return false;
	}

	if ( nTopA >= nBottomB )
	{
		return false;
	}

	if ( nRightA <= nLeftB )
	{
		return false;
	}

	if ( nLeftA >= nRightB )
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void AABB::Clear()
{
	m_bReady = false;

	m_pProgram = Zeno::Program::s_kDefault;

	m_pMesh = Zeno::Mesh::s_kDefault;

	m_Position.Set( 0.0f, 0.0f, 0.0f );

	m_LowPoint.Set( 0.0f, 0.0f, 0.0f );

	m_HighPoint.Set( 0.0f, 0.0f, 0.0f );
}

AABB::Ptr AABB::Create( Zeno::Program::Ptr pProgram, 
		float nLength, float nWidth, float nHeight )
{
	AABB::Ptr pBox( new AABB );

	if ( !pBox->SetProgram( pProgram ) )
	{
		return s_kDefault;
	}

	pBox->SetSize( nLength, nWidth, nHeight );

	if ( !pBox->Load() )
	{
		return s_kDefault;
	}

	return pBox;
}