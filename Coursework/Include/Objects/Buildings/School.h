#pragma once

#include "GameObject.h"

class School : public GameObject
{
public:
	School();

	virtual ~School();

	virtual bool Load();

	virtual void Update( float nDeltaTime );

	virtual std::string GetName();

};
