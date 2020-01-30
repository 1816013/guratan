#pragma execution_character_set("utf-8")
#include "Bar.h"
USING_NS_CC;

Sprite* Bar::createHpBar(const unsigned int max, BarType barType, Size size)
{
	auto hpBar = Bar::create();
	hpBar->initValue(max, barType, size);
	return hpBar;
}

Bar::Bar()
{
}

Bar::~Bar()
{
	_green->release();
	_red->release();
}

bool Bar::initValue( const unsigned int max, BarType barType, cocos2d::Size size)
{
	_barType = barType;
	_max = max;
	int initValue = 0;
	_frame = Sprite::create("image/hpBar/hpBg2.png");
	
	_frame->setOpacity(122);
	_frame->setContentSize(size);
	this->addChild(_frame);

	_blue = this->loadSprite("image/hpBar/hpBlue.png");
	_blue->retain();

	_green = this->loadSprite("image/hpBar/hpGreen.png");
	_green->retain();

	_red = this->loadSprite("image/hpBar/hpRed.png");
	_red->retain();
	// 最初のバーを設定しておく
	if (_barType == BarType::HP)
	{
		initValue = 10;
		auto icon = this->loadSprite("image/hpBar/hpIcon.png");
		icon->setOpacity(255);
		icon->setPosition(0, 0);
		_frame->addChild(icon);
		_currentbar = _green;
		_frame->addChild(_green);
	}
	else
	{
		_currentbar = _blue;
		_frame->addChild(_blue);
	}
	_number = Label::createWithTTF(StringUtils::toString(initValue) + "/" + StringUtils::toString(_max), "fonts/PixelMplus12-Regular.ttf", 12);
	_number->setPosition(Point(_frame->getContentSize().width + 10, 0));
	_number->setAnchorPoint({ 0, 0 });
	_number->setTag(10);
	_frame->addChild(_number);
	// 初期値を設定
	changeValue(_max);
	return true;
}


void Bar::changeValue(const unsigned int value)
{
	if (_current == value)
	{
		return;
	}
	
	// 色が変わったときはバーの入れ替え
	Sprite* newSprite = this->getSprite(value);
	if (this->_currentbar != newSprite)
	{
		_currentbar->removeFromParent();
		_currentbar = newSprite;
		_frame->addChild(_currentbar);
	}

	// 管理値の最大値に対する現在値の比率を計算
	float ratio = (float)value / _max;

	// 新しいゲージの横幅
	float newWidth = (_frame->getBoundingBox().size.width - 4 - 22) * ratio;
	float newHeight = _frame->getBoundingBox().size.height - 4;

	// 現在のバーサイズを変更
	this->_currentbar->setContentSize(Size(newWidth, newHeight));

	this->_current = value;
	ChangeNumber(_max, value);
}

void Bar::changeMax(const unsigned int max, const unsigned int value)
{
	_max = max;
	//ChangeNumber(max, value);
	changeValue(value);
}

unsigned int Bar::getNowMax()
{
	return _max;
}

Sprite* Bar::loadSprite(const std::string& name)
{
	auto sp = Sprite::create(name);

	sp->setAnchorPoint(Vec2(0.0, 0.0));
	sp->setOpacity(122);
	if (_barType == BarType::HP)
	{
		sp->setPosition(Vec2(22, 4));
	}

	return sp;
}

cocos2d::Sprite * Bar::getSprite(const unsigned int value)
{
	auto color = _green;
	if (_barType == BarType::HP)
	{
		if (value >= _max)
		{
			return _green; // 最大値
		}

		float nowValue = (float)value / this->_max;

		if (nowValue < 0.25f)
		{
			return _red;
		}
	}
	else
	{
		color = _blue;
	}
	
	return color;
}

void Bar::ChangeNumber(unsigned int max, unsigned int value)
{
	_number->setString(StringUtils::toString(value) + "/" + StringUtils::toString(max));
}
