#pragma once
#include"Obj.h"

enum class Ability
{
	PowerUp,
	SpeedUp,
	Heal,
	ChargeLevel,
	ChargeSpeed,
	MAX
};

enum class ChargeType
{
	SHOT,
	TWISTER,
	FLONTAL,
	MAX
};

using AbilityPair = std::pair<std::string, Ability>;	//名前, アビリティ種類

class Player : public Obj
{
public:
	// 関数
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	void addExp(const int exp);
	float GetMovePower();
	float GetPowerRate();
	void SetAbility(AbilityPair ability);
	void SetStrong(bool flag);
	bool IsCharged();
	bool GetStrong();
	void SetChargeType(ChargeType chargeType);
	ChargeType GetChargeType();
	std::vector<AbilityPair> GetUnacquiredAbility();

	bool ColisionObj(Obj& hitObj, cocos2d::Scene& scene)override;

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理
	void LevelUp(void);
	cocos2d::Animation* SetAnim(DIR dir);	// 方向に応じたｱﾆﾒｰｼｮﾝの設定

	// 変数
	cocos2d::DrawNode* line;
	int _hpMax;
	int _expMax;			// これ以上になるとレベルアップ
	int _level;				// レベル
	float _charge;			// チャージしている時間
	float _chargeMax;		// チャージがたまる時間
	int _chargeLevel;		// チャージの強さ
	int _chargeLevelMax;	// チャージの最大強さ
	bool _strongF;			// 無敵
	float _strongCnt;		// 無敵時間ｶｳﾝﾀ

	float _powerRate;		// 攻撃力アビリティ用
	float _movePower;		// 移動速度アビリティ補正用

	ChargeType _chargeType;

	cocos2d::Sprite* texSprite;
	cocos2d::Animation* _oldAnim;
	
	std::vector<AbilityPair>_ability;		// 取得しているアビリティ
	std::vector<AbilityPair>_unacquiredAbility;	// 未取得アビリティ
};

