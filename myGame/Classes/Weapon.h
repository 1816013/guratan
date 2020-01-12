#pragma once
#include <Unit/Obj.h>
class Weapon : public Obj
{
public:
	static cocos2d::Sprite* createWeapon(Sprite& sp);
	Weapon();
	~Weapon();
	int GetHP();
	void SetHP(int hp);
	DIR GetDIR();
	void SetDIR(DIR dir);
	int GetPower();
	

	CREATE_FUNC(Weapon);
private:
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;
	cocos2d::Vec2 _pos;
	int _remainCnt;
};

