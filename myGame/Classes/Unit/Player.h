#pragma once
#include"Obj.h"
#include <array>

class Player : public Obj
{
public:
	// 関数
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	int GetHP();
	void SetHP(int hp);

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理

	DIR GetDIR();
	void SetDIR(DIR dir);

	// 変数
	cocos2d::DrawNode* line;
	bool changeF;
};

