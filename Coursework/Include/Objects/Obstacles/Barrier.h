#pragma once

#include "GameObject.h"

class Barrier : public GameObject
{
public:
	Barrier();

	virtual ~Barrier();

	virtual bool Load();

	virtual void Update( float nDeltaTime );

	virtual std::string GetName();

};
