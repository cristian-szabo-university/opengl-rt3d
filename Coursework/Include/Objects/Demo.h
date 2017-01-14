#pragma once

#include "GameObject.h"

class Demo : public GameObject
{
public:
	Demo();

	virtual ~Demo();

	virtual bool Load();

	virtual void Update( float nDeltaTime );

	virtual std::string GetName();

private:
	float m_nViewAngle;

};
