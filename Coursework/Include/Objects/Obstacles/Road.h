#pragma once

#include "GameObject.h"

class Road : public GameObject
{
public:
	Road();

	virtual ~Road();

	virtual bool Load();

	virtual void Update( float nDeltaTime );

	virtual std::string GetName();

};
