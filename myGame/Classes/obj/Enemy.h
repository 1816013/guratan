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

	// 関数
	Enemy();
	~Enemy();

	int GetExp();
	bool ColisionObj(Obj& hitObj, cocos2d::Scene& scene)override;
	
	CREATE_FUNC(Enemy);
private:
	cocos2d::Animation* SetAnim(DIR dir);	// 方向に応じたｱﾆﾒｰｼｮﾝの設定
	cocos2d::Animation* _oldAnim;			// 前のｱﾆﾒｰｼｮﾝ※ｱﾆﾒｰｼｮﾝマネージャー更新でなくなる
	EnemyType _enemyType;
	EnemyMoveAI _enemyMoveAI;
	EnemyAttackAI _enemyAttackAI;
	float _attackIntarval;
	bool _attackFlag;
	float time;

	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理	
};


