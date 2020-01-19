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

	// �֐�
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

	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;	// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���	
};


