#include"Obj.h"
#include <array>
#include "input/OPRT_state.h"

enum class EnemyAI
{
	IDLE,
	FORROW,
	MAX
};

class Enemy : public Obj
{
public:
	static cocos2d::Sprite* createEnemy(EnemyAI enemyAI);
	void SetEnemyAI(EnemyAI enemyAI);

	// 関数
	Enemy();
	~Enemy();

	int GetHP();
	void SetHP(int hp);
	

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Enemy);
private:
	EnemyAI _enemyAI;

	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理

	DIR GetDIR();
	void SetDIR(DIR dir);

	

	std::array<cocos2d::Vec2, static_cast<int>(DIR::MAX)> _speedTbl;
};

