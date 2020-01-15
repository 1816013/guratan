#include"Obj.h"
#include "input/OPRT_state.h"



class Enemy : public Obj
{
public:
	static cocos2d::Sprite* createEnemy(EnemyMoveAI enemyAI);
	EnemyMoveAI GetEnemyAI();
	void SetEnemyAI(EnemyMoveAI enemyAI);

	// ŠÖ”
	Enemy();
	~Enemy();

	int GetExp();
	int GetHP();
	void SetHP(const int hp);
	int GetPower();
	DIR GetDIR();
	void SetDIR(DIR dir);

	bool ColisionObj(Obj* hitObj, cocos2d::Layer* layer);
	
	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Enemy);
private:
	EnemyMoveAI _enemyMoveAI;
	EnemyAttackAI _enemyAttackAI;
	int _attackIntarval;
	float time;

	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;	// ÌßÚ²Ô°‚ÌˆÚ“®‚Æ±ÆÒ°¼®İˆ—	
};

