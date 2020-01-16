#include "Player.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
#include "GameScene.h"
#include "action/Colision.h"
#include "Weapon.h"

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

void Player::addExp(const int exp )
{
	_exp += exp;
}

bool Player::GetRangeFlag()
{
	return _rangeF;
}

int Player::GetHP()
{
	return _hp;
}

void Player::SetHP(const int hp)
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

void Player::SetAbility(Ability& ability)
{
	_ability.emplace_back(ability);
	switch (ability)
	{
	case Ability::PowerUp:
		_power += 1;
		break;
	case Ability::SpeedUp:
		_movePower += 0.5f;
		break;
	case Ability::RangeAttack:
		_rangeF = true;
		break;
	}
}

std::vector<Ability> Player::GetUnacquiredAbility()
{
	return _unacquiredAbility;
}

bool Player::FindAbility(Ability ability)
{
	bool find = false;
	for (auto abilityItr : _ability)
	{
		if (abilityItr == ability)
		{
			find = true;
		}
	}
	return find;
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
	this->setPosition(visibleSize.width / 2, 64);
	this->setColor(cocos2d::Color3B(0, 0, 255));

	line = DrawNode::create();
	line->setIgnoreAnchorPointForPosition(false);
	line->setAnchorPoint({ 1.0f , 1.0f });
	line->drawLine(Vec2(0, 0), Vec2(0,48 ), Color4F::RED);
	line->setPosition(Vec2(16.0f, 16.0f));
	
	this->addChild(line);

	// ﾌﾟﾚｲﾔｰｽﾃｰﾀｽ
	_level = 1;
	_power = 1;
	_exp = 0;
	_expMax = 3;
	_dir = DIR::UP;
	_hp = 10;
	_movePower = 1.0f;
	_rangeF = false;

	auto size = this->getContentSize() / 2;
	_colSize[static_cast<int>(DIR::UP)] = { Size(-size.width, size.height), Size(size.width, size.height) };
	_colSize[static_cast<int>(DIR::RIGHT)] = { Size(size.width, size.height), Size(size.width, -size.height) };
	_colSize[static_cast<int>(DIR::DOWN)] = { Size(size.width, -size.height), Size(-size.width, -size.height) };
	_colSize[static_cast<int>(DIR::LEFT)] = { Size(-size.width, size.height), Size(-size.width, -size.height) };

	// アビリティ設定
	_unacquiredAbility.emplace_back(Ability::RangeAttack);
	_unacquiredAbility.emplace_back(Ability::PowerUp);
	_unacquiredAbility.emplace_back(Ability::SpeedUp);

	_charge = 0;

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
		module.colSize = { Size(-16, 16), Size(16, 16) };
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
		module.colSize = { Size(-16, -16), Size(16, -16) };
		module.inputID = INPUT_ID::DOWN;
		module.keyTiming = Timing::ON;
		module.dir = DIR::DOWN;
		_actMng->AddActModule("下移動", module);
	}
	// 左向き
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.inputID = INPUT_ID::LEFT;
		module.keyTiming = Timing::ON;
		module.dir = DIR::LEFT;
		_actMng->AddActModule("左向き", module);
	}
	// 右向き
	{
		actModule module;
		module.actID = ACT_STATE::RUN;		
		module.inputID = INPUT_ID::RIGHT;
		module.keyTiming = Timing::ON;
		module.dir = DIR::RIGHT;
		_actMng->AddActModule("右向き", module);
	}
	// 上向き
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.inputID = INPUT_ID::UP;
		module.keyTiming = Timing::ON;
		module.dir = DIR::UP;
		_actMng->AddActModule("上向き", module);
	}
	// 下向き
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.inputID = INPUT_ID::DOWN;
		module.keyTiming = Timing::ON;
		module.dir = DIR::DOWN;
		_actMng->AddActModule("下向き", module);
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
	gameScene->removeChildByTag(14);
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
	auto text5 = Label::createWithSystemFont("charge" + StringUtils::toString(_charge), "ueten-1c-medium.ttf", 24);
	text5->setPosition(Point(100, 280));
	text5->setTag(14);
	gameScene->addChild(text5);
	_inputState->update();
	_actMng->update(*this);

	// 攻撃
	// 武器作成
	auto SetWeapon = [](Scene& scene, Sprite& sp, Size size, OptionType optionType)
	{
		auto weapon = Weapon::createWeapon(sp, optionType);
		weapon->setTag(static_cast<int>(objTag::ATTACK));
		weapon->setContentSize(size);
		weapon->setCameraMask(static_cast<int>(CameraFlag::USER1));
		//nowScene->addChild(weapon);
		scene.getChildByName("charLayer")->addChild(weapon);
	};

	// チャージ中
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::ATTACK))
	{
        _charge += delta;

	}
	// 押した瞬間攻撃
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::ATTACK) && !_inputState->GetInput(TRG_STATE::OLD, INPUT_ID::ATTACK))
	{
		SetWeapon(*gameScene, *this, { 32, 32 }, OptionType::NOMAL);
	}

	// チャージが最大だったらチャージ攻撃
	if (!_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::ATTACK) && _inputState->GetInput(TRG_STATE::OLD, INPUT_ID::ATTACK))
	{
  		if (_charge >= 1.0f)
		{
			SetWeapon(*gameScene, *this, { 16, 16 }, OptionType::RANGE);
			//nowScene->addChild(weapon);
		}
		_charge = 0.0f;
	}
	// レベルアップ
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
	auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
	gameScene->SetSceneType(SceneType::MENU);
	_level++;
	_hp += 2;
	_exp = 0;
	_expMax *= 2;
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
			if (_gameMap->mapColision(*this, _speedTbl[static_cast<int>(hitObj->GetDIR())] * 50, this->_colSize[static_cast<int>(_dir)]))
			{
				this->setPosition(this->getPosition() + (_speedTbl[static_cast<int>(hitObj->GetDIR())]) * 32);		// ノックバック処理
			}
			hitObj->removeFromParent();
		}
		if (hitTag == static_cast<int>(objTag::MAPOBJ))
		{
			col = true;
			this->removeFromParent();
		}
	}
	return col;
}