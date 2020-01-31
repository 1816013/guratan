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
	static cocos2d::Sprite* createEnemy(EnemyType enemyType, int floor);
	EnemyType GetEnemyType();
	EnemyMoveAI GetEnemyAI();
	void SetEnemyAI(EnemyType enemyType,int floor);

	// ŠÖ”
	Enemy();
	~Enemy();

	int GetExp();
	bool ColisionObj(Obj& hitObj, cocos2d::Scene& scene)override;
	
	CREATE_FUNC(Enemy);
private:
	cocos2d::Animation* SetAnim(DIR dir);	// •ûŒü‚É‰‚¶‚½±ÆÒ°¼®İ‚Ìİ’è
	cocos2d::Animation* _oldAnim;
	cocos2d::Sprite* texSprite;
	EnemyType _enemyType;
	EnemyMoveAI _enemyMoveAI;
	EnemyAttackAI _enemyAttackAI;
	float _attackIntarval;
	bool _attackFlag;
	float time;

	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;	// ÌßÚ²Ô°‚ÌˆÚ“®‚Æ±ÆÒ°¼®İˆ—	
};


