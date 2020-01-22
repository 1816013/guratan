#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>
#include <action/ActionMng.h>
#include "GameMap.h"
#include <array>

enum class objTag
{
	PLAYER,
	ENEMY,
	ATTACK,
	E_ATTACK,
	MAPOBJ,
	MAX
};


class Obj : public cocos2d::Sprite
{
public:
	Obj();
	virtual ~Obj();

	DIR GetDIR();
	void SetDIR(DIR dir);
	virtual bool ColisionObj(Obj& hitObj, cocos2d::Scene& scene);
	int GetHP();
	void SetHP(const int hp);
	void SetKnockFlag(bool flag);
	bool GetKnockFlag(void);
	float GetPower();

	bool IsCheckedHP(Obj& obj);
	std::array<std::array<cocos2d::Size, 2>, static_cast<int>(DIR::MAX)>_colSize;

protected:
	void KnockBack(Obj& obj, cocos2d::Vec2 vec);
	// ïœêî
	cocos2d::Vec2 _pos;				// ç¿ïW	
	cocos2d::Size _size;				//ëÂÇ´Ç≥
	int _exp;
	int _hp;
	float _power;
	DIR _dir;

	bool _knockF;
	int _knockCnt;

	std::array<cocos2d::Vec2, static_cast<int>(DIR::MAX)> _speedTbl;

	std::unique_ptr<ActionMng>_actMng;
	std::unique_ptr<GameMap>_gameMap;
};

