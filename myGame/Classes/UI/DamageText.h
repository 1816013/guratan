#pragma once
#include "cocos2d.h"

class DamageText : public cocos2d::Sprite
{
public:
	static cocos2d::Sprite* createDamageT(unsigned int value, cocos2d::Sprite& sp);
	DamageText();
	~DamageText();

	CREATE_FUNC(DamageText);
private:
	bool InitText(unsigned int value, cocos2d::Sprite& sp);
	void update(float delta)override;

	float _retainCnt;
};

