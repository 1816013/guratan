#include "Player.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>

USING_NS_CC;

cocos2d::Sprite* Player::createPlayer()
{
	return Player::create();
}

Player::Player()
{

}

Player::~Player()
{
}

int Player::GetHP()
{
	return _hp;
}

void Player::SetHP(int hp)
{
	_hp = hp;
}

int Player::GetPower()
{
	return _power;
}

float Player::GetMovePower()
{
	return _movePower;
}

void Player::SetAbility(Ability ability)
{
	_abilityList.emplace_back(ability);
}

std::vector<Ability> Player::GetAbilityList()
{
	return _abilityList;
}

bool Player::FindAbility(Ability ability)
{
	bool find = false;
	for (auto abilityItr : _abilityList)
	{
		if (abilityItr == ability)
		{
			find = true;
		}
	}
	return find;
}

bool Player::ColisionObj(Obj * hitObj, cocos2d::Layer * layer)
{
	bool col = false;

	Rect myRect = this->getBoundingBox();
	Rect hitRect = hitObj->getBoundingBox();
	int hitTag = hitObj->getTag();

	if (myRect.intersectsRect(hitRect))
	{
		int hitTag = hitObj->getTag();
		if (hitTag == static_cast<int>(objTag::E_ATTACK))
		{
			col = true;
			_hp -= hitObj->GetPower();
			//if (/*後ろが移動できるなら*/)
			{
				this->setPosition(this->getPosition() + (_speedTbl[static_cast<int>(hitObj->GetDIR())]) * 16);		// ノックバック処理
			}
			hitObj->removeFromParent();
		}
	}
	return col;
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

	// ﾌﾟﾚｲﾔｰｽﾃｰﾀｽ
	_level = 1;
	_exp = 0;
	_expMax = 5;
	_dir = DIR::UP;
	_hp = 5;
	changeF = false;
	_movePower = 1.0f;

	// ｱｸｼｮﾝｾｯﾄ @csv出力にしたい
	// 左移動
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.speed = Vec2(-5, 0);
		module.colSize = { Size(-16, 16), Size(-16, -16) };
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
		module.colSize = { Size(16, 16), Size(16, -16) };
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
		module.colSize = { Size(-16, 16), Size(-16, -16) };
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
		module.colSize = { Size(-16, 16), Size(-16, -16) };
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
		module.keyTiming = Timing::ON_MOM;
		_actMng->AddActModule("剣攻撃", module);
	}
	
	this->scheduleUpdate();
	return true;
}

void Player::update(float delta)
{
	// HP表記(仮)
	auto gameScene = Director::getInstance()->getRunningScene();
	if (gameScene->getName() != "GameScene")
	{
		return;
	}
	gameScene->removeChildByTag(10);
	gameScene->removeChildByTag(11);
	gameScene->removeChildByTag(12);
	gameScene->removeChildByTag(13);
	auto text = Label::createWithSystemFont("HP" + StringUtils::toString(this->GetHP()), "ueten-1c-medium.ttf", 24);
	text->setPosition(Point(100, 400));
	text->setTag(10);
	gameScene->addChild(text);
	auto text2 = Label::createWithSystemFont("exp" + StringUtils::toString(_exp), "ueten-1c-medium.ttf", 24);
	text2->setPosition(Point(100, 370));
	text2->setTag(11);
	gameScene->addChild(text2);
	auto text3 = Label::createWithSystemFont("expMax" + StringUtils::toString(_expMax), "ueten-1c-medium.ttf", 24);
	text3->setPosition(Point(100, 340));
	text3->setTag(12);
	gameScene->addChild(text3);
	auto text4 = Label::createWithSystemFont("level"+ StringUtils::toString(_level), "ueten-1c-medium.ttf", 24);
	text4->setPosition(Point(100, 310));
	text4->setTag(13);
	gameScene->addChild(text4);
	_inputState->update();
	_actMng->update(*this);
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::UP))
	{
		_exp++;
	}
	if (_exp >= _expMax)
	{
		LevelUp();
	}
	
	gameScene->getChildByName("playerCamera")->setPosition3D(Vec3( this->getPositionX() - 1024 / 2,this->getPositionY() - 576 / 2, 0 ));

}

DIR Player::GetDIR()
{
	return _dir;
}

void Player::SetDIR(DIR dir)
{
	_dir = dir;
}

void Player::LevelUp(void)
{
	_level++;
	_hp += 2;
	_exp = 0;
	_expMax *= 2;
}
