#pragma once

#include "GameObject.h"

enum PlayerStateType
{
	PLAYER_STATE_INVALID,
	PLAYER_STATE_STAND,
	PLAYER_STATE_WALK,
	PLAYER_STATE_MAX_COUNT
};

class Player : public GameObject
{
public:
	Player();

	virtual ~Player();

	virtual bool Load();

	virtual void Update( float nDeltaTime );

	void ChangeState( PlayerStateType NewState );

	virtual std::string GetName();
	
	void StepBack();

private:
	PlayerStateType m_State;

	float m_nHorizontalAngle;

	float m_nVerticalAngle;

	float m_nViewAngle;

	float m_nSpeed;

	Zeno::Vector3 m_Velocity;

};
