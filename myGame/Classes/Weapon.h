#pragma once
#include <Unit/Obj.h>
#include "Unit/Player.h"

enum class OptionType
{
	NOMAL,
	CHARGE,
	MAX
};

class Weapon : public Obj
{
public:
	static cocos2d::Sprite* createWeapon(Sprite& sp, const OptionType option, int chargeLevel = 0);
	Weapon();
	~Weapon();
	CREATE_FUNC(Weapon);
private:
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;
	void SetColSize(cocos2d::Sprite& sp);
	void SetState();

	OptionType _optionType;
	ChargeType _chargeType;	// 保存用
	cocos2d::Vec2 _offset;
	int _remainCnt;
};

