#pragma once

#include"Obj.h"
enum class Ability
{
	PowerUp,
	SpeedUp,
	RangeAttack,
	MAX
};


class Player : public Obj
{
public:
	// 関数
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	void addExp(const int exp);
	float GetMovePower();
	void SetAbility(Ability& ability);
	void SetStrong(bool flag);
	bool IsCharged();
	bool GetStrong();
	std::vector<Ability> GetUnacquiredAbility();

	bool ColisionObj(Obj& hitObj, cocos2d::Scene& scene)override;

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理
	void LevelUp(void);

	// 変数
	cocos2d::DrawNode* line;
	int _expMax;	// これ以上になるとレベルアップ
	int _level;		// レベル
	float _charge;	// チャージしている時間

	bool _strongF;	// 無敵
	float _strongCnt;	// 無敵時間ｶｳﾝﾀ

	float _powerRate;	// 攻撃力アビリティ用
	float _movePower;	// 移動速度アビリティ補正用
	
	std::vector<Ability>_ability;		// 取得しているアビリティ
	std::vector<Ability>_unacquiredAbility;	// 未取得アビリティ
};

