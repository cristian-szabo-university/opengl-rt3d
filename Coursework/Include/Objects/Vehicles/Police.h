#pragma once

#include "GameObject.h"

class Police : public GameObject
{
public:
	Police();

	virtual ~Police();

	virtual bool Load();

	virtual void Update( float nDeltaTime );

	virtual std::string GetName();

private:
	float m_nElapsedTime;

};
