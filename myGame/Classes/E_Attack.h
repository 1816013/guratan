#pragma once
#include "Unit/Obj.h"
class E_Attack : public Obj
{
public:
	static cocos2d::Sprite* createE_Attack(Sprite& sp);
	E_Attack();
	~E_Attack();
	DIR GetDIR()override;
	void SetDIR(DIR dir)override;
	int GetPower()override;
	void SetTargetMove(Sprite& sp); 

	CREATE_FUNC(E_Attack);
private:
	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;
	float _remainCnt;
	cocos2d::Vec2 _targetPos;
	cocos2d::Vec2 _move;
	float _radian;
};

