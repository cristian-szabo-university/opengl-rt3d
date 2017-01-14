#pragma once

#include "GameObject.h"

class House : public GameObject
{
public:
	House();

	virtual ~House();

	virtual bool Load();

	virtual void Update( float nDeltaTime );

	virtual std::string GetName();

};
