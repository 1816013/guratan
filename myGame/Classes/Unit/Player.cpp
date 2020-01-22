#include "Player.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
#include "GameScene.h"
#include "action/Colision.h"
#include "Weapon.h"
#include "AnimMng.h"

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

float Player::GetMovePower()
{
	return _movePower;
}

std::vector<Ability> Player::GetUnacquiredAbility()
{
	return _unacquiredAbility;
}

void Player::SetAbility(Ability& ability)
{
	_ability.emplace_back(ability);
	switch (ability)
	{
	case Ability::PowerUp:
		_powerRate += 0.5;
		break;
	case Ability::SpeedUp:
		_movePower += 0.5f;
		break;
	case Ability::Heal:
		_hp = _hpMax / 2;
		if (_hp > _hpMax)
		{
			_hp = _hpMax;
		}
		break;
	case Ability::ChargeLevel:
		_chargeLevel++;
		if (_chargeLevel >= 3)
		{
			_unacquiredAbility.erase(_unacquiredAbility.begin() + static_cast<int>(Ability::ChargeLevel));
		}
		break;
	case Ability::ChargeSpeed:
		_chargeMax -= 0.1f;
		if (_chargeMax <= 0.5f)
		{
			_unacquiredAbility.erase(_unacquiredAbility.begin() + static_cast<int>(Ability::ChargeSpeed));
		}
		break;
	default:
		break;
	}
}

void Player::SetStrong(bool flag)
{
	_strongF = true;
}

bool Player::IsCharged()
{
	if (_charge > 0)
	{
		return true;
	}
	return false;
}

bool Player::GetStrong()
{
	return _strongF;
}

void Player::SetChargeType(ChargeType chargeType)
{
	_chargeType = chargeType;
}

ChargeType Player::GetChargeType()
{
	return _chargeType;
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
	// 画像
	lpAnimMng.AnimCreate("player", "idleF", 4, 0.5);
	lpAnimMng.AnimCreate("player", "idleB", 4, 0.5);
	lpAnimMng.AnimCreate("player", "idleR", 4, 0.5);
	lpAnimMng.AnimCreate("player", "idleL", 4, 0.5);


	this->setPosition(visibleSize.width / 2, 64);
	this->setContentSize({32, 32});

	Rect rect = Rect(0, 0, 32, 32);
	this->setTextureRect(rect);
	
	texSprite = Sprite::create();
	texSprite->setAnchorPoint({ 0.3f, 0.1f });
	this->addChild(texSprite);

	//sp->setPosition(visibleSize.width / 2, 64);
	//this->setColor(cocos2d::Color3B(0, 0, 255));

	// ﾌﾟﾚｲﾔｰｽﾃｰﾀｽ
	_level = 1;
	_power = 1;
	_exp = 0;
	_expMax = 3;
	_dir = DIR::UP;
	_hpMax = 10;
	_hp = 10;
	_movePower = 1.0f;
	_strongF = false;
	_strongCnt = 0;
	_powerRate = 1.0f;
	_charge = 0;
	_chargeMax = 1.0f;
	_chargeLevel = 0;
	_chargeLevelMax = 3;

	auto size = this->getContentSize() / 2;
	_colSize[static_cast<int>(DIR::UP)] = { Size(-size.width, size.height), Size(size.width, size.height) };
	_colSize[static_cast<int>(DIR::RIGHT)] = { Size(size.width, size.height), Size(size.width, -size.height) };
	_colSize[static_cast<int>(DIR::DOWN)] = { Size(size.width, -size.height), Size(-size.width, -size.height) };
	_colSize[static_cast<int>(DIR::LEFT)] = { Size(-size.width, size.height), Size(-size.width, -size.height) };

	// アビリティ設定
	
	_unacquiredAbility.emplace_back(Ability::PowerUp);
	_unacquiredAbility.emplace_back(Ability::SpeedUp);
	_unacquiredAbility.emplace_back(Ability::Heal);
	_unacquiredAbility.emplace_back(Ability::ChargeLevel);
	_unacquiredAbility.emplace_back(Ability::ChargeSpeed);
	
	// ｱｸｼｮﾝｾｯﾄ
	// 左移動
	{
		actModule module;
		module.actID = ACT_STATE::RUN;
		module.speed = Vec2(-3.5, 0);
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
		module.speed = Vec2(3.5, 0);
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
		module.speed = Vec2(0, 3.5);
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
		module.speed = Vec2(0, -3.5);
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
	auto text = Label::createWithSystemFont("プレイヤーHP" + StringUtils::toString(this->GetHP()), "fonts/arial.ttf", 24);
	text->setPosition(Point(100, 400));
	text->setTag(10);
	gameScene->addChild(text);
	auto text2 = Label::createWithSystemFont("exp" + StringUtils::toString(_exp), "fonts/arial.ttf", 24);
	text2->setPosition(Point(100, 370));
	text2->setTag(11);
	gameScene->addChild(text2);
	auto text3 = Label::createWithSystemFont("expMax" + StringUtils::toString(_expMax), "fonts/arial.ttf", 24);
	text3->setPosition(Point(100, 340));
	text3->setTag(12);
	gameScene->addChild(text3);
	auto text4 = Label::createWithSystemFont("level"+ StringUtils::toString(_level), "fonts/arial.ttf", 24);
	text4->setPosition(Point(100, 310));
	text4->setTag(13);
	gameScene->addChild(text4);
	auto text5 = Label::createWithSystemFont("charge" + StringUtils::toString(_charge), "fonts/arial.ttf", 24);
	text5->setPosition(Point(100, 280));
	text5->setTag(14);
	gameScene->addChild(text5);
	_inputState->update();
	_actMng->update(*this);

	// 攻撃
	// 武器作成
	auto SetWeapon = [](Scene& scene, Sprite& sp, const OptionType optionType, int chargeLevel = 0)
	{
		auto weapon = Weapon::createWeapon(sp, optionType, chargeLevel);
		weapon->setCameraMask(static_cast<int>(CameraFlag::USER1));
		scene.getChildByName("charLayer")->addChild(weapon);
	};
	// 押した瞬間攻撃
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::ATTACK) && !_inputState->GetInput(TRG_STATE::OLD, INPUT_ID::ATTACK))
	{
		SetWeapon(*gameScene, *this, OptionType::NOMAL);
	}
	// チャージ中
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::ATTACK))
	{
		_charge += delta;
		if (_charge > _chargeMax)
		{
			_chargeLevel = 1;
		}
		if (_charge > _chargeMax * 2 && _chargeLevelMax >= 2)
		{
			_chargeLevel = 2;
		}
		if (_charge > _chargeMax * 2 && _chargeLevelMax >= 3)
		{
			_chargeLevel = 3;
		}
	}
	// チャージが最大だったらチャージ攻撃
	if (!_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::ATTACK) )
	{
		if (_inputState->GetInput(TRG_STATE::OLD, INPUT_ID::ATTACK))
		{
			if (_chargeLevel >= 1)
			{
				SetWeapon(*gameScene, *this, OptionType::CHARGE, _chargeLevel);
			}
		}
		_charge = 0.0f;
		_chargeLevel = 0;
	}
	// レベルアップ
	if (_exp >= _expMax)
	{
		LevelUp();
	}	
	if (_strongF)
	{
		_strongCnt += delta;
		if (_strongCnt >= 0.5f)
		{
			_strongF = false;
			_strongCnt = 0;
		}
	}
	// ｱﾆﾒｰｼｮﾝ
	auto anim = SetAnim(_dir);	// repeatNumの設定をSetAnimで設定しているため先読み必須@変更予定
	lpAnimMng.runAnim(*texSprite, *anim, 0);
	//gameScene->getChildByName("playerCamera")->setPosition3D(Vec3( 0,this->getPositionY() - 576 / 2, 0 ));

}

void Player::LevelUp(void)
{
	auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
	gameScene->SetSceneType(SceneType::MENU);
	_level++;
	_power += 1;
	_hpMax += 2;
	_hp += 2;
	_exp = 0;
	_expMax *= 2;
}

cocos2d::Animation * Player::SetAnim(DIR dir)
{
	auto animCache = AnimationCache::getInstance();
	Animation* anim = nullptr;
	switch (dir)
	{
	case DIR::UP:
		anim = animCache->getAnimation("idleB");
		break;
	case DIR::RIGHT:
		anim = animCache->getAnimation("idleR");
		break;
	case DIR::DOWN:
		anim = animCache->getAnimation("idleF");
		break;
	case DIR::LEFT:
		anim = animCache->getAnimation("idleL");
		break;
	default:
		break;
	}
	return anim;
}

bool Player::ColisionObj(Obj& hitObj, cocos2d::Scene& scene)
{
	bool col = false;

	Rect myRect = this->getBoundingBox();
	Rect hitRect = hitObj.getBoundingBox();
	int hitTag = hitObj.getTag();

	if (myRect.intersectsRect(hitRect))
	{
		int hitTag = hitObj.getTag();
		if (hitTag == static_cast<int>(objTag::ENEMY))
		{
			if (!_strongF)
			{
				col = true;
				_hp -= hitObj.GetPower();
				_strongF = true;
				if (_gameMap->mapColision(*this, _speedTbl[static_cast<int>(hitObj.GetDIR())] * 32, this->_colSize[static_cast<int>(hitObj.GetDIR())]))
				{
					this->setPosition(this->getPosition() + (_speedTbl[static_cast<int>(hitObj.GetDIR())]) * 32);		// ノックバック処理
				}
			}
		}
		if (hitTag == static_cast<int>(objTag::E_ATTACK))
		{
			if (!_strongF)
			{
				col = true;
				_hp -= hitObj.GetPower();
				hitObj.SetHP(hitObj.GetHP() - 1);
				_strongF = true;
				hitObj.SetKnockFlag(true);
				if (_gameMap->mapColision(*this, _speedTbl[static_cast<int>(hitObj.GetDIR())] * 32, this->_colSize[static_cast<int>(hitObj.GetDIR())]))
				{
					this->setPosition(this->getPosition() + (_speedTbl[static_cast<int>(hitObj.GetDIR())]) * 32);		// ノックバック処理
				}
			}
		}
		if (hitTag == static_cast<int>(objTag::MAPOBJ))
		{
			col = true;
			auto visibleSize = Director::getInstance()->getVisibleSize();		// ｳｲﾝﾄﾞｳｻｲｽﾞ	
			this->setPosition(visibleSize.width / 2, 64);
			auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
			gameScene->SetNextFloor(true);
			_hp = 3;
			if (_hp > _hpMax)
			{
				_hp = _hpMax;
			}
			_charge = 0;
			_inputState->Init();
		}
	}
	return col;
}