#include "DamageText.h"
#include <obj/Obj.h>
USING_NS_CC;

cocos2d::Sprite * DamageText::createDamageT(unsigned int value, Sprite& sp)
{
	auto damageText = DamageText::create();
	damageText->InitText(value, sp);
	int CameraMask = static_cast<int>(CameraFlag::DEFAULT) | static_cast<int>(CameraFlag::USER1);
	damageText->setCameraMask(static_cast<int>(CameraFlag::USER1));
	return damageText;
}

DamageText::DamageText()
{
}

DamageText::~DamageText()
{
}

bool DamageText::InitText(unsigned int value, Sprite& sp)
{
	_retainCnt = 0;
	auto number = Label::createWithTTF(StringUtils::toString(value), "fonts/PixelMplus12-Regular.ttf", 24);
	number->setPosition(sp.getPosition());
	number->setAnchorPoint({ 0, 0 });

	if (sp.getTag() == static_cast<int>(objTag::PLAYER))
	{
		number->setColor(Color3B(0, 0, 255));
	}
	else
	{
		number->setColor(Color3B(255, 0, 0));
	}
	this->addChild(number);
	this->scheduleUpdate();
	return true;
}

void DamageText::update(float delta)
{
	_retainCnt += delta;
	this->setPositionY(this->getPositionY() + delta * 32);
	if (_retainCnt > 0.5f)
	{
		this->removeFromParent();
	}
}

