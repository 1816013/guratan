#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>
#include <action/ActionMng.h>

enum class objTag
{
	PLAYER,
	ENEMY,
	ATTACK,
	MAX
};


class Obj : public cocos2d::Sprite
{
public:
	Obj();
	virtual ~Obj();

	virtual DIR GetDIR();
	virtual void SetDIR(DIR dir);
	virtual int GetHP() = 0;
	virtual void SetHP(int hp) = 0;

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

