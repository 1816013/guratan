#pragma once
#include"Obj.h"

class Player : public Obj
{
public:
	// ŠÖ”
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	DIR GetDIR();
	void SetDIR(DIR dir);
	int GetHP();
	void SetHP(int hp);
	int GetPower();

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;	// ÌßÚ²Ô°‚ÌˆÚ“®‚Æ±ÆÒ°¼®İˆ—

	

	void LevelUp(void);

	// •Ï”
	cocos2d::DrawNode* line;
	bool changeF;
	int _exp;
	int _expMax;
	int _level;

	std::vector<int>_ability;
};

