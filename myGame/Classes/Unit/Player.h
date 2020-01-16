#pragma once
#include"Obj.h"

enum class Ability
{
	PowerUp,
	SpeedUp,
	RangeAttack,
	MAX
};

enum class ChargeType
{

};


class Player : public Obj
{
public:
	// 関数
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	DIR GetDIR()override;
	void SetDIR(DIR dir)override;
	int GetHP()override;
	void SetHP(const int hp)override;
	int GetPower()override;

	void addExp(const int exp);
	bool GetRangeFlag();
	float GetMovePower();
	void SetAbility(Ability& ability);
	std::vector<Ability> GetUnacquiredAbility();
	bool FindAbility(Ability ability);

	bool ColisionObj(Obj* hitObj, cocos2d::Layer* layer);

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理
	void LevelUp(void);

	// 変数
	cocos2d::DrawNode* line;
	bool _rangeF;	// 遠距離攻撃ﾌﾗｸﾞ＠いらないかも
	int _expMax;	// これ以上になるとレベルアップ
	int _level;		// レベル

	float _movePower;	// 移動速度アビリティ補正用
	float _charge;

	std::vector<Ability>_ability;		// 取得しているアビリティ
	std::vector<Ability>_unacquiredAbility;	// 未取得アビリティ
};

