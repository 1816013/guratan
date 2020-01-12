#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>
#include <action/ActionMng.h>

enum class objTag
{
	PLAYER,
	ENEMY,
	ATTACK,
	E_ATTACK,
	MAX
};

enum class EnemyMoveAI
{
	IDLE,
	FORROW,
	MAX
};

enum class EnemyAttackAI
{
	NONE,
	AIMING,
	MAX
};


class Obj : public cocos2d::Sprite
{
public:
	Obj();
	virtual ~Obj();

	virtual DIR GetDIR() = 0;
	virtual void SetDIR(DIR dir) = 0;
	virtual bool ColisionObj(Obj* hitObj, cocos2d::Layer* layer);
	virtual int GetHP();
	virtual void SetHP(int hp);
	virtual int GetPower() = 0;

	bool IsCheckedHP();



protected:
	// ïœêî
	cocos2d::Vec2 _pos;				// ç¿ïW	
	cocos2d::Size _size;				//ëÂÇ´Ç≥
	int _hp;
	int _power;
	DIR _dir;

	std::shared_ptr<ActionMng>_actMng;
};

