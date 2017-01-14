#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Interface/Window.h"

#include "Zeno/Render/Program.h"
#include "Zeno/Render/Variable.h"

#include "Misc/Model.h"

#include "irrKlang.h"

#include "Misc/AABB.h"

class GameObject
{
public:
	typedef std::shared_ptr< GameObject > Ptr;

	static const Ptr s_kDefault;

	GameObject();

	virtual ~GameObject();

	bool SetProgram( Zeno::Program::Ptr pProgram );

	bool SetModel( Zeno::Model::Ptr pModel );

	bool SetAABB( AABB::Ptr pBox );

	bool SetSound( irrklang::ISound* pSound );

	virtual bool Load();

	bool IsReady();

	virtual bool Draw();

	virtual void Update( float nDeltaTime );

	virtual void Event( Zeno::WindowMessage* pMessage );

	bool Move( float nSpeed, Zeno::Vector3 Axis );

	void Clear();

	void ToggleAABB();

	virtual std::string GetName();

	Zeno::Vector3 GetPosition();

	bool CheckCollision( GameObject::Ptr pOther );

	template< class T >
	static Ptr Create( Zeno::Program::Ptr pProgram, Zeno::Model::Ptr pModel, Zeno::Vector3 Position )
	{
		Ptr pObject( new T );

		if ( !pObject->SetProgram( pProgram ) )
		{
			return s_kDefault;
		}

		if ( !pObject->SetModel( pModel ) )
		{
			return s_kDefault;
		}

		if ( !pObject->Load() )
		{
			return s_kDefault;
		}

		pObject->Move( Position.m_S.X, Zeno::Vector3( 1.0f, 0.0f, 0.0f ) );
		pObject->Move( Position.m_S.Y, Zeno::Vector3( 0.0f, 1.0f, 0.0f ) );
		pObject->Move( Position.m_S.Z, Zeno::Vector3( 0.0f, 0.0f, 1.0f ) );

		return pObject;
	}

protected:
	bool m_bReady;

	bool m_bDrawAABB;

	Zeno::Program::Ptr m_pProgram;

	Zeno::Model::Ptr m_pModel;

	irrklang::ISound* m_pSound;

	Zeno::Matrix4 m_ModelMatrix;

	AABB::Ptr m_pBox;

};
