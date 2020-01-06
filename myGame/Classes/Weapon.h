#pragma once
#include <Unit/Obj.h>
class Weapon : public Obj
{
public:
	static cocos2d::Sprite* createWeapon();
	Weapon();
	~Weapon();
	int GetHP();
	void SetHP(int hp);
	void update(float delta)override;

	CREATE_FUNC(Weapon);
private:
	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	cocos2d::Vec2 _pos;
	int _remainCnt;
};

