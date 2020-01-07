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

	// ŠÖ”
	Enemy();
	~Enemy();

	int GetHP();
	void SetHP(int hp);
	int GetPower();

	bool ColisionObj(Obj* hitObj, cocos2d::Layer* layer);
	

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Enemy);
private:
	EnemyAI _enemyAI;

	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;	// ÌßÚ²Ô°‚ÌˆÚ“®‚Æ±ÆÒ°¼®İˆ—

	DIR GetDIR();
	void SetDIR(DIR dir);

	

	std::array<cocos2d::Vec2, static_cast<int>(DIR::MAX)> _speedTbl;
};

