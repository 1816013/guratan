#pragma once
#include"Obj.h"

class Player : public Obj
{
public:
	// 関数
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	DIR GetDIR();
	void SetDIR(DIR dir);
	int GetHP();
	void SetHP(int hp);
	int GetPower();
	float GetMovePower();

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理
	void LevelUp(void);

	// 変数
	cocos2d::DrawNode* line;
	bool changeF;
	int _exp;
	int _expMax;
	int _level;

	float _movePower;	// 移動速度アビリティ補正用

	std::vector<int>_ability;
};

