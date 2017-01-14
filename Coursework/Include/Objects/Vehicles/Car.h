#pragma once

#include "GameObject.h"

class Car : public GameObject
{
public:
	Car();

	virtual ~Car();

	virtual bool Load();

	virtual void Update( float nDeltaTime );

	virtual std::string GetName();

private:
	float m_nElapsedTime;

};
