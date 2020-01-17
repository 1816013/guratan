#pragma once
#include <Unit/Obj.h>

enum class OptionType
{
	NOMAL,
	CHARGE,
	MAX
};
enum class ChargeType
{
	SHOT,
	MAX
};

class Weapon : public Obj
{
public:
	static cocos2d::Sprite* createWeapon(Sprite& sp, OptionType option);
	Weapon();
	~Weapon();
	DIR GetDIR()override;
	void SetDIR(DIR dir)override;
	int GetPower()override;
	
	CREATE_FUNC(Weapon);
private:
	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;
	OptionType _optionType;
	cocos2d::Vec2 _pos;
	int _remainCnt;
};

