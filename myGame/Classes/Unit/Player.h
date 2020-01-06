#pragma once
#include"Obj.h"
#include <array>

class Player : public Obj
{
public:
	// ŠÖ”
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	int GetHP();
	void SetHP(int hp);

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;	// ÌßÚ²Ô°‚ÌˆÚ“®‚Æ±ÆÒ°¼®İˆ—

	DIR GetDIR();
	void SetDIR(DIR dir);

	// •Ï”
	cocos2d::DrawNode* line;
	bool changeF;
};

