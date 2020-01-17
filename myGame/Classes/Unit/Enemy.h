#include"Obj.h"
#include "input/OPRT_state.h"



class Enemy : public Obj
{
public:
	static cocos2d::Sprite* createEnemy(EnemyMoveAI moveAI ,EnemyAttackAI attackAI);
	EnemyMoveAI GetEnemyAI();
	void SetEnemyAI(EnemyMoveAI enemyAI);

	// 関数
	Enemy();
	~Enemy();

	int GetExp();
	int GetHP()override;
	void SetHP(const int hp)override;
	int GetPower()override;
	DIR GetDIR()override;
	void SetDIR(DIR dir)override;

	bool ColisionObj(Obj& hitObj, cocos2d::Scene& scene)override;
	
	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Enemy);
private:
	EnemyMoveAI _enemyMoveAI;
	EnemyAttackAI _enemyAttackAI;
	int _attackIntarval;
	float time;

	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理	
};

