#pragma once

#include "GameObject.h"

class Treasure : public GameObject
{
public:
	Treasure();

	virtual ~Treasure();

	virtual bool Load();

	virtual void Update( float nDeltaTime );

	virtual std::string GetName();

private:
	float m_nAngle;

};
