#include "Player.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>

USING_NS_CC;

cocos2d::Sprite * Player::createSprite()
{
	return Player::create();
}

Player::Player()
{

}

Player::~Player()
{
}

bool Player::init()
{
	// ｽﾌﾟﾗｲﾄｸﾗｽの初期化@initを自作したため必要
	if (!Sprite::init())
	{
		return false;
	}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32	
	_inputState = std::make_unique<OPRT_key>(this);
#else
	_inputState.reset(new OPRT_touch(this));
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	auto visibleSize = Director::getInstance()->getVisibleSize();		// ｳｲﾝﾄﾞｳｻｲｽﾞ	

	auto uiBglayer = Layer::create();
	uiBglayer->setName("uiLayer");
	auto charBglayer = Layer::create();
	charBglayer->setName("charLayer");
	auto flontBglayer = Layer::create();
	flontBglayer->setName("flontLayer");
	auto backBglayer = Layer::create();
	backBglayer->setName("backLayer");
	
	Rect rect = Rect(0, 0, 32, 32);
	this->setTextureRect(rect);
	this->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->setColor(cocos2d::Color3B(0, 0, 255));

	line = DrawNode::create();
	line->setIgnoreAnchorPointForPosition(false);
	line->setAnchorPoint({ 1.0f , 1.0f });
	line->drawLine(Vec2(0, 0), Vec2(0,48 ), Color4F::RED);
	line->setPosition(Vec2(16.0f, 16.0f));
	
	this->addChild(line);

	_dir = DIR::UP;
	changeF = false;

	// ｱｸｼｮﾝｾｯﾄ @csv出力にしたい
	// 左移動
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.speed = Vec2(-5, 0);
		module.colSize = { Size(-30, 45), Size(-30, -60) };
		module.inputID = INPUT_ID::LEFT;
		module.keyTiming = Timing::ON;
		module.dir = DIR::LEFT;
		_actMng->AddActModule("左移動", module);
	}
	// 右移動
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.speed = Vec2(5, 0);
		module.colSize = { Size(30, 45), Size(30, -60) };
		module.inputID = INPUT_ID::RIGHT;
		module.keyTiming = Timing::ON;
		module.dir = DIR::RIGHT;
		_actMng->AddActModule("右移動", module);
	}
	// 上移動
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.speed = Vec2(0, 5);
		module.colSize = { Size(-30, 45), Size(-30, -60) };
		module.inputID = INPUT_ID::UP;
		module.keyTiming = Timing::ON;
		module.dir = DIR::UP;
		_actMng->AddActModule("上移動", module);
	}
	// 下移動
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.speed = Vec2(0, -5);
		module.colSize = { Size(-30, 45), Size(-30, -60) };
		module.inputID = INPUT_ID::DOWN;
		module.keyTiming = Timing::ON;
		module.dir = DIR::DOWN;
		_actMng->AddActModule("下移動", module);
	}
	// atack
	{
		actModule module;
		module.actID = ACT_STATE::ATACK;
		module.white.emplace_back(ACT_STATE::IDLE);
		module.inputID = INPUT_ID::ATACK;
		module.keyTiming = Timing::ON;
		_actMng->AddActModule("剣攻撃", module);
	}
	
	this->scheduleUpdate();
	return true;
}

void Player::update(float delta)
{
	
	_inputState->update();
	_actMng->update(*this);
	/*if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::UP))
	{
		this->setPositionY(this->getPositionY() + 5);
		if (checkinput(INPUT_ID::UP))
		{
			_dir = DIR::UP;
		}
	}
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::RIGHT))
	{
		this->setPositionX(this->getPositionX() + 5);
		if (checkinput(INPUT_ID::RIGHT))
		{
			_dir = DIR::RIGHT;
		}
	}
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::DOWN))
	{
		this->setPositionY(this->getPositionY() - 5);
		if (checkinput(INPUT_ID::DOWN))
		{
			_dir = DIR::DOWN;
		}
	}
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::LEFT))
	{
		this->setPositionX(this->getPositionX() - 5);
		if (checkinput(INPUT_ID::LEFT))
		{
			_dir = DIR::LEFT;
		}
	}*/
	
}

DIR Player::GetDIR()
{
	return _dir;
}
