#pragma once
#include "Obj.h"
#include "Enemy.h"

class E_Attack : public Obj
{
public:
	static cocos2d::Sprite* createE_Attack(Sprite& sp, EnemyAttackAI enemyAttackAI);
	E_Attack();
	~E_Attack();
	void SetTargetMove(Sprite& sp, EnemyAttackAI enemyAttackAI); 

	CREATE_FUNC(E_Attack);
private:
	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;
	float _remainCnt;
	cocos2d::Vec2 _targetPos;
	cocos2d::Vec2 _move;
	float _radian;
};

