#pragma once
#include"Obj.h"
#include "input/OPRT_state.h"

enum class EnemyType
{
	SLIME,
	CANNON,
	ARCHAR,
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
	SHOT,
	MAX
};

class Enemy : public Obj
{
public:
	static cocos2d::Sprite* createEnemy(EnemyType enemyType);
	EnemyMoveAI GetEnemyAI();
	void SetEnemyAI(EnemyType enemyType);

	// ŠÖ”
	Enemy();
	~Enemy();

	int GetExp();
	bool ColisionObj(Obj& hitObj, cocos2d::Scene& scene)override;
	
	CREATE_FUNC(Enemy);
private:
	cocos2d::PhysicsBody*  physicsBody;
	EnemyMoveAI _enemyMoveAI;
	EnemyAttackAI _enemyAttackAI;
	float _attackIntarval;
	bool _attackFlag;
	float time;

	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;	// ÌßÚ²Ô°‚ÌˆÚ“®‚Æ±ÆÒ°¼®İˆ—	
};


