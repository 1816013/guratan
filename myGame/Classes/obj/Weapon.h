#pragma once
#include <obj/Obj.h>
#include <obj/Player.h>

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
	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;
	void SetWeaponType(Sprite& sp, int chargeLevel);
	void SetColSize(cocos2d::Sprite& sp);
	void SetState();

	OptionType _optionType;
	ChargeType _chargeType;	// •Û‘¶—p
	cocos2d::Vec2 _offset;
	float _remainCnt;
};

