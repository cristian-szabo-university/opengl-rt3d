#pragma once

#include "GameObject.h"

class Building : public GameObject
{
public:
	Building();

	virtual ~Building();

	virtual bool Load();

	virtual void Update( float nDeltaTime );

	virtual std::string GetName();

};
