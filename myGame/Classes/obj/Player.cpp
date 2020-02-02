#include "Player.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
#include <scene/GameScene.h>
#include "Weapon.h"
#include "AnimMng.h"
#include <UI/Bar.h>
#include <UI/DamageText.h>
//#pragma execution_character_set("utf-8")
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

float Player::GetPowerRate()
{
	return _powerRate;
}

std::vector<AbilityPair> Player::GetUnacquiredAbility()
{
	return _unacquiredAbility;
}

void Player::SetAbility(AbilityPair abilityPair)
{
	//_ability.emplace_back(abilityPair);
	switch (abilityPair.second)
	{
	case Ability::PowerUp:
		_powerRate += 0.5;
		break;
	case Ability::SpeedUp:
		_movePower += 0.2f;
		break;
	case Ability::Heal:
		_hp += _hpMax / 2;
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
		_chargeMax -= 0.2f;
		if (_chargeMax <= 0.4f)
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
	// 一番最初の絵
	this->setPosition(visibleSize.width / 2, 64);
	this->setContentSize({32, 32});

	Rect rect = Rect(0, 0, 32, 32);
	this->setContentSize({ 32, 32 });

	texSprite = Sprite::create();
	texSprite->setAnchorPoint({ 0.37f, 0.1f });
	texSprite->setScale(1.5f, 1.5f);
	this->addChild(texSprite);
	auto anim = AnimationCache::getInstance()->getAnimation("player-idleF");
	lpAnimMng.runAnim(*texSprite, *anim, *_oldAnim);
	_oldAnim = anim;


	// ﾌﾟﾚｲﾔｰｽﾃｰﾀｽ
	_level = 1;
	_power = 1;
	_exp = 0;
	_expMax = 3;
	_dir = DIR::UP;
	_hpMax = 10;
	_hp = _hpMax;
	_movePower = 1.0f;
	_strongF = false;
	_strongCnt = 0;
	_powerRate = 1.0f;
	_charge = 0;
	_chargeMax = 1.0f;
	_chargeLevel = 0;
	_chargeLevelMax = 3;
	_knockCnt = 0.0f;
	_knockF = false;
	_knockDir = DIR::MAX;

	auto size = this->getContentSize() / 2;
	_colSize[static_cast<int>(DIR::UP)] = { Size(-size.width, size.height), Size(size.width, size.height) };
	_colSize[static_cast<int>(DIR::RIGHT)] = { Size(size.width, size.height), Size(size.width, -size.height) };
	_colSize[static_cast<int>(DIR::DOWN)] = { Size(size.width, -size.height), Size(-size.width, -size.height) };
	_colSize[static_cast<int>(DIR::LEFT)] = { Size(-size.width, size.height), Size(-size.width, -size.height) };

	// アビリティ設定
	//_ability.emplace_back(std::make_pair("Power UP", Ability::PowerUp));
	_unacquiredAbility.emplace_back(std::make_pair("Power UP",Ability::PowerUp));
	_unacquiredAbility.emplace_back(std::make_pair("Speed UP",Ability::SpeedUp));
	_unacquiredAbility.emplace_back(std::make_pair("Heal",Ability::Heal));
	_unacquiredAbility.emplace_back(std::make_pair("ChargeLevel UP",Ability::ChargeLevel));
	_unacquiredAbility.emplace_back(std::make_pair("ChargeSpeed UP",Ability::ChargeSpeed));

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
	// HP表記
	auto gameScene = Director::getInstance()->getRunningScene();
	if (gameScene->getName() != "GameScene")
	{
		return;
	}
	auto hpBar = (Bar*)gameScene->getChildByName("uiLayer")->getChildByName("playerHPBar");
	hpBar->changeMax(_hpMax, _hp);
	hpBar->changeValue(_hp);
	auto expBar = (Bar*)gameScene->getChildByName("uiLayer")->getChildByName("playerExpBar");
	expBar->changeMax(_expMax, _exp);
	expBar->changeValue(_exp);

	gameScene->getChildByName("uiLayer")->removeChildByTag(10);
	gameScene->getChildByName("uiLayer")->removeChildByTag(11);
	auto text4 = Label::createWithTTF("LV " + StringUtils::toString(_level), "fonts/PixelMplus12-Regular.ttf", 24);
	text4->setTag(10);
	text4->setPosition(Point(140, 520));
	auto text5 = Label::createWithTTF("charge" + StringUtils::toString(_charge), "fonts/PixelMplus12-Regular.ttf", 24);
	text5->setTag(11);
	text5->setPosition(Point(100, 280));

	gameScene->getChildByName("uiLayer")->addChild(text4);
	gameScene->getChildByName("uiLayer")->addChild(text5);
	_inputState->update();
	_actMng->update(*this);

	attack(delta, *gameScene);

	// ノックバック
	if (_knockF)
	{
		_knockCnt += delta;
		if (_gameMap->mapColision(*this, _move, _colSize[static_cast<int>(_knockDir)]))
		{
			this->setPosition(this->getPosition() + _move);
		}
		if (_knockCnt > 0.15f)
		{
			_knockCnt = 0;
			_knockF = false;
			_move = { 0 , 0 };
		}
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
	lpAnimMng.runAnim(*texSprite, *anim,*_oldAnim, 0);
	_oldAnim = anim;
	auto playerCam = gameScene->getChildByName("playerCamera");
	playerCam->setPosition3D(Vec3(this->getPositionX() - 1024 / 2,this->getPositionY() - 576 / 2, 0 ));

}

void Player::attack(float delta, cocos2d::Scene& scene)
{
	// 攻撃
// 武器作成
	auto SetWeapon = [](Scene& scene, Sprite& sp, const OptionType optionType, int chargeLevel = 0)
	{
		auto weapon = Weapon::createWeapon(sp, optionType, chargeLevel);
		scene.getChildByName("charLayer")->addChild(weapon);
	};
	// 押した瞬間攻撃
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::ATTACK) && !_inputState->GetInput(TRG_STATE::OLD, INPUT_ID::ATTACK))
	{
		SetWeapon(scene, *this, OptionType::NOMAL);
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
	if (!_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::ATTACK))
	{
		if (_inputState->GetInput(TRG_STATE::OLD, INPUT_ID::ATTACK))
		{
			if (_chargeLevel >= 1)
			{
				SetWeapon(scene, *this, OptionType::CHARGE, _chargeLevel);
			}
		}
		_charge = 0.0f;
		_chargeLevel = 0;
	}
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
		anim = animCache->getAnimation("player-idleB");
		break;
	case DIR::RIGHT:
		anim = animCache->getAnimation("player-idleR");
		break;
	case DIR::DOWN:
		anim = animCache->getAnimation("player-idleF");
		break;
	case DIR::LEFT:
		anim = animCache->getAnimation("player-idleL");
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
				_knockF = true;				
				_move = _speedTbl[static_cast<int>(hitObj.GetDIR())] * 8;
				_knockDir = hitObj.GetDIR();
				auto damageT = DamageText::createDamageT(hitObj.GetPower(), *this);
				scene.getChildByName("uiLayer")->addChild(damageT);
				scene.runAction(Blink::create(0.1f, 1));
			}
		}
		// 両方ダメージ受けるもの
		if (hitTag == static_cast<int>(objTag::E_ATTACK))
		{
			if (!_strongF)
			{
				col = true;
				_hp -= hitObj.GetPower();
				hitObj.SetHP(hitObj.GetHP() - 1);
				_strongF = true;
				_knockF = true;
				_move = _speedTbl[static_cast<int>(hitObj.GetDIR())] * 8;
				_knockDir = hitObj.GetDIR();
				auto damageT = DamageText::createDamageT(hitObj.GetPower(), *this);
				scene.getChildByName("uiLayer")->addChild(damageT);
			}
		}
		if (hitTag == static_cast<int>(objTag::MAPOBJ))
		{
			col = true;
			auto visibleSize = Director::getInstance()->getVisibleSize();		// ｳｲﾝﾄﾞｳｻｲｽﾞ	
			this->setPosition(visibleSize.width / 2, 64);
			auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
			gameScene->SetNextFloor(true);
			_hp += 3;
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