/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#pragma execution_character_set("utf-8")
#include "GameScene.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
#include <obj/Weapon.h>
#include <obj/E_Attack.h>
#include "GameOverScene.h"
#include <obj/mapObject.h>
#include "AnimMng.h"
#include <UI/Bar.h>
#include "LoadingScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}


GameScene::~GameScene()
{
	if (_running)
	{
		onExit();
	}
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	// シーン設定
	this->setName("GameScene");
	_sceneType = SceneType::MENU;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// レイヤー設定
	_zOrderMenu = static_cast<int>(Z_ORDER_TYPE::MENU);
	_zOrderUI = static_cast<int>(Z_ORDER_TYPE::UI);
	_zOrderChar = static_cast<int>(Z_ORDER_TYPE::CHAR);
	_zOrderBack = static_cast<int>(Z_ORDER_TYPE::BACK);

	MenuBglayer = Layer::create();
	auto _bg = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
	_bg->setOpacity(122);
	MenuBglayer->addChild(_bg);
	MenuBglayer->setName("menuLayer");
	uiBglayer = Layer::create();
	uiBglayer->setName("uiLayer");
	charBglayer = Layer::create();
	charBglayer->setName("charLayer");
	backBglayer = Layer::create();
	backBglayer->setName("backLayer");

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32	
	_inputState = std::make_unique<OPRT_key>(this);
	_gameMap = std::make_unique<GameMap>();
	// 仮ｽﾌﾟﾗｲﾄ メニュー用 ※矢印予定
	cocos2d::Rect selectRect = cocos2d::Rect(0, 0, 20, 20);
	selectSp = Sprite::create();
	selectSp->setPosition(500, 200);
	selectSp->setColor({ 255, 255, 255 });
	selectSp->setTextureRect(selectRect);
	selectSp->setName("select");
	MenuBglayer->addChild(selectSp);
#else
	_inputState.reset(new OPRT_touch(this));
	// バーチャルパッド
	// 現在タッチしている場所を表す画像
	Sprite* psp = Sprite::create("image/pad/circle.png");
	psp->setName("nowTouch");
	psp->setOpacity(122);
	psp->setPosition({ 150, 150 });
	uiBglayer->addChild(psp);

	// タッチ開始位置を表す画像
	Sprite* hsp = Sprite::create("image/pad/hishi.png");
	hsp->setName("startTouch");
	hsp->setPosition({ 150, 150 });
	uiBglayer->addChild(hsp);

	// タッチ開始位置と現在位置をつなぐ線
	auto line = DrawNode::create();
	line->setVisible(false);
	line->setOpacity(128);
	line->setName("line");
	uiBglayer->addChild(line);
	//_inputState = std::make_unique<OPRT_touch>();

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	// UI
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
    float y = origin.y + closeItem->getContentSize().height/2;
    closeItem->setPosition(Vec2(x,y));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
	uiBglayer->addChild(menu, 0);
	auto hpBar = Bar::createHpBar(10, BarType::HP, Size(288, 24));
	hpBar->setName("playerHPBar");
	hpBar->setPosition(330, 520);
	uiBglayer->addChild(hpBar, 0);
	auto expBar = Bar::createHpBar(10, BarType::EXP, Size(288, 12));
	expBar->setName("playerExpBar");
	expBar->setPosition(330, 500);
	uiBglayer->addChild(expBar, 0);
	_floorT = Label::createWithTTF(StringUtils::toString(_floorNum) + " F", "fonts/PixelMplus12-Regular.ttf", 24);
	_floorT->setPosition(80, 520);
	_floorT->setName("階数");
	uiBglayer->addChild(_floorT, 0);

	// 画像
	lpAnimMng.AnimCreate("charge", "base", 8, 0.1);
	lpAnimMng.AnimCreate("player", "attackF", 3, 0.05);
	lpAnimMng.AnimCreate("player", "attackB", 3, 0.05);
	lpAnimMng.AnimCreate("player", "attackR", 3, 0.05);
	lpAnimMng.AnimCreate("player", "attackL", 3, 0.05);
	lpAnimMng.AnimCreate("player", "runF", 6, 0.1);
	lpAnimMng.AnimCreate("player", "runB", 6, 0.1);
	lpAnimMng.AnimCreate("player", "runR", 6, 0.1);
	lpAnimMng.AnimCreate("player", "runL", 6, 0.1);
	lpAnimMng.AnimCreate("player", "idleF", 4, 0.4);
	lpAnimMng.AnimCreate("player", "idleB", 4, 0.4);
	lpAnimMng.AnimCreate("player", "idleR", 4, 0.4);
	lpAnimMng.AnimCreate("player", "idleL", 4, 0.4);
	lpAnimMng.AnimCreate("weapon", "twist", 2, 0.05);
	lpAnimMng.AnimCreate("skeleton", "runR", 3, 0.2);
	lpAnimMng.AnimCreate("skeleton", "runB", 3, 0.2);
	lpAnimMng.AnimCreate("skeleton", "runF", 3, 0.2);
	lpAnimMng.AnimCreate("orb", "idle", 5, 0.1);
	lpAnimMng.AnimCreate("slime", "runR", 3, 0.1);
	lpAnimMng.AnimCreate("slime", "runB", 3, 0.1);
	lpAnimMng.AnimCreate("slime", "runF", 3, 0.1);
	lpAnimMng.AnimCreate("e_attack", "fire", 2, 0.1);
	// キャラクター
	auto player = Player::createPlayer();
	player->setTag(static_cast<int>(objTag::PLAYER));
	charBglayer->addChild(player);
	
	for (int i = 0; i < 5; i++)
	{
		int randAi = rand() % static_cast<int>(EnemyType::MAX);
		SetEnemy(static_cast<EnemyType>(0));
	}

	// ﾏｯﾌﾟ(仮) @ﾏﾈｰｼﾞｬｰ予定
	_gameMap->createMap(*backBglayer);
	mapObj = nullptr;

	for (int i = 0; i < 3; i++)
	{
		selectButton[i] = ui::Button::create("image/select/selectFrame.png");
		selectButton[i]->setPosition(Vec2(300 + 200 * i, 300));
		selectButton[i]->setTitleFontName("fonts/PixelMplus12-Regular.ttf");
		selectButton[i]->setTitleFontSize(16);
		selectButton[i]->setTitleColor(Color3B::WHITE);
		MenuBglayer->addChild(selectButton[i]);
	}
	// カメラ
	auto dCamera = SetCamera("default", CameraFlag::DEFAULT, 1);
	auto pCamera = SetCamera("playerCamera", CameraFlag::USER1, 0);	
	auto mCamera = SetCamera("menuCamera", CameraFlag::USER2, 2);

	// カメラマスク
	int cameraMask = static_cast<int>(CameraFlag::DEFAULT) | static_cast<int>(CameraFlag::USER1) | static_cast<int>(CameraFlag::USER2);
	this->setCameraMask(cameraMask);
	MenuBglayer->setCameraMask(static_cast<int>(CameraFlag::USER2));
	uiBglayer->setCameraMask(static_cast<int>(CameraFlag::DEFAULT));
	charBglayer->setCameraMask(static_cast<int>(CameraFlag::USER1));
	backBglayer->setCameraMask(static_cast<int>(CameraFlag::USER1));

	// 変数
	flag = false;
	_floorNum = 0;
	_nextFloor = false;
	// ｼｰﾝにぶら下げる
	this->addChild(MenuBglayer, _zOrderMenu);
	this->addChild(uiBglayer, _zOrderUI);
	this->addChild(charBglayer, _zOrderChar);
	this->addChild(backBglayer, _zOrderBack);
	this->scheduleUpdate();
	return true;
}

void GameScene::update(float delta)
{
	
	auto scene = Director::getInstance()->getRunningScene();
	if (scene->getName() != "GameScene")
	{
		return;
	}
	_inputState->update();
	_floorT->setString(StringUtils::toString(_floorNum) + " F");
	if (_sceneType == SceneType::GAME)
	{
		Colition();		
		int pCount = 0;
		int eCount = 0;
		for (auto objItr : this->charBglayer->getChildren())
		{
			auto obj = (Obj*)objItr;
			
			int tag = obj->getTag();
			if (static_cast<int>(objTag::PLAYER) == tag)
			{
				pCount++;
			}
			if (static_cast<int>(objTag::ENEMY) == tag)
			{
				eCount++;
			}
			if (obj->IsCheckedHP(*obj))
			{
				break;
			}
		}
		if (pCount <= 0)
		{
			Scene *scene = GameOverScene::createScene();
			Director::getInstance()->replaceScene(TransitionRotoZoom::create(2.0f, scene));
		}
		else if (eCount <= 0 && mapObj == nullptr)
		{
			mapObj = mapObject::createMapObj();
			mapObj->setTag(static_cast<int>(objTag::MAPOBJ));
			mapObj->setCameraMask(static_cast<int>(CameraFlag::USER1));
			charBglayer->addChild(mapObj, -1);
		}
		
		if (_nextFloor)
		{
			auto transition = TransitionTurnOffTiles::create(0.5f, LoadingScene::createScene());
			Director::getInstance()->pushScene(transition);
			ChangeFloor();
		}
	}
	if (_sceneType == SceneType::MENU) // メニューレイヤークラスに分ける予定
	{
		auto gameScene = Director::getInstance()->getRunningScene();
		if (gameScene->getName() != "GameScene")
		{
			return;
		}
		auto player = (Player*)gameScene->getChildByName("charLayer")->getChildByTag(static_cast<int>(objTag::PLAYER));
		
		if (!flag)	// 一回しかやらない処理
		{
			player->_inputState->Init();
			flag = true;
			// ポーズ処理
			charBglayer->pause();
			
			selectCnt = 0;
			for (cocos2d::Node* _node : charBglayer->getChildren())
			{
				_node->pause();
			}	
			// レベルアップ
			if (_floorNum != 0)
			{
				auto unAbility = player->GetUnacquiredAbility();
				std::random_device seed;
				std::mt19937 engine(seed());
				std::shuffle(unAbility.begin(), unAbility.end(), engine);

				for (int i = 0; i < 3; i++)
				{
					// メニュ－
					auto levelupText = Label::createWithTTF("LEVELUP!!", "fonts/PixelMplus12-Regular.ttf", 24);
					levelupText->setPosition(Vec2( 1024 / 2,
						576 / 4 * 3 - levelupText->getContentSize().height));
					levelupText->setCameraMask(static_cast<int>(CameraFlag::USER2));
					levelupText->setName("Text");
					MenuBglayer->addChild(levelupText, 0);
					retAbility[i] = unAbility.back();
					unAbility.pop_back();
				}
				auto left = selectButton[0];
				left->setTitleText(retAbility[0].first);
				left->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
					switch (type)
					{
					case ui::Widget::TouchEventType::ENDED:
						SelectEnded(0);
						break;
					}
				});
				auto midle = selectButton[1];
				midle->setTitleText(retAbility[1].first);
				midle->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
					switch (type)
					{
						SelectEnded(1);
						break;
					}
				});
				auto right = selectButton[2];
				right->setTitleText(retAbility[2].first);
				right->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
					switch (type)
					{
					case ui::Widget::TouchEventType::ENDED:
						SelectEnded(2);
					}
				});				
			}
			else // 階層が一の時// チャージセレクト
			{			
				// メニュ－
				auto ChargeSelect = Label::createWithTTF("ChargeSelect", "fonts/PixelMplus12-Regular.ttf", 24);
				ChargeSelect->setPosition(Vec2(1024 / 2, 576 / 4 * 3 - ChargeSelect->getContentSize().height));
				ChargeSelect->setName("Text");
				ChargeSelect->setCameraMask(static_cast<int>(CameraFlag::USER2));
				MenuBglayer->addChild(ChargeSelect, 0);
				auto left = selectButton[0];
				left->setTitleText("shot");
				left->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
					switch (type)
					{
					case ui::Widget::TouchEventType::ENDED:
						SelectEnded(0);
						break;
					}
				});
				auto midle = selectButton[1];
				midle->setTitleText("twist");
				midle->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
					switch (type)
					{
					case ui::Widget::TouchEventType::ENDED:
						SelectEnded(1);			
						break;
					}
				});
				auto right = selectButton[2];
				right->setTitleText("flontal");
				right->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
					switch (type)
					{
					case ui::Widget::TouchEventType::ENDED:
						SelectEnded(2);		
						break;
					}
				});			
			}
			this->getChildByName("menuCamera")->setPosition3D({ 0, 0, 0 });
		}
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32	
		if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::LEFT) &~_inputState->GetInput(TRG_STATE::OLD, INPUT_ID::LEFT))
 		{
			selectCnt--;
		}
		if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::RIGHT) &~_inputState->GetInput(TRG_STATE::OLD, INPUT_ID::RIGHT))
		{
			selectCnt++;
		}
		if (selectCnt < 0)
		{
			selectCnt = 2;
		}
		if (selectCnt >= 3)
		{
			selectCnt = 0;
		}
		auto selectRect = MenuBglayer->getChildByName("select");
		switch (selectCnt)
		{
		case 0:
			selectRect->setPosition(300, 200);
			break;
		case 1:
			selectRect->setPosition(500, 200);
			break;
		case 2:
			selectRect->setPosition(700, 200);
			break;
		default:
			break;
		}
#endif
		if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::SELECT) &~_inputState->GetInput(TRG_STATE::OLD, INPUT_ID::SELECT))
		{
			if (_floorNum == 0)
			{
				player->SetChargeType(static_cast<ChargeType>(selectCnt));
				_floorNum = 1;
			}
			else
			{
				player->SetAbility(retAbility[selectCnt]);
			}
			
			ChangeSceneType(SceneType::GAME);
		}
	}   
}

void GameScene::SetSceneType(SceneType sceneType)
{
	_sceneType = sceneType;
}

void GameScene::SetNextFloor(bool flag)
{
	_nextFloor = flag;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void GameScene::SetEnemy(EnemyType enemyType)
{
	auto enemy = Enemy::createEnemy(enemyType, _floorNum);
	enemy->setPosition(Vec2(rand() % 800 + 48, rand() % 400 + 48 + 96));
	charBglayer->addChild(enemy);
}

void GameScene::Colition()
{
	for (auto eRect : this->charBglayer->getChildren())
	{
		for (auto pRect : this->charBglayer->getChildren())
		{
			if (eRect == pRect)
			{
				continue;
			}
			Obj* obj = (Obj*)eRect;
			Obj* hitObj = (Obj*)pRect;
			obj->ColisionObj(*hitObj, *this);

		}
	}
}

bool GameScene::ChangeFloor()
{
	_nextFloor = false;
	mapObj = nullptr;
	_floorNum++;
	int randNum = rand() % 5 + 4;
	for (int i = 0; i < randNum; i++)
	{
		int randAi = rand() % static_cast<int>(EnemyType::MAX);
		SetEnemy(static_cast<EnemyType>(randAi));
	}
	charBglayer->getChildByTag(static_cast<int>(objTag::MAPOBJ))->removeFromParent();
//	TRACE("floor %d", _floorNum);
	return true;
}

void GameScene::ChangeSceneType(SceneType sceneType)
{
	_sceneType = sceneType;
	flag = false;
	charBglayer->resume();
	for (cocos2d::Node* _node : charBglayer->getChildren())
	{
		_node->resume();
	}
	
	MenuBglayer->getChildByName("Text")->removeFromParent();
	this->getChildByName("menuCamera")->setPosition3D({ -1024, -576, 0 });
}

Camera* GameScene::SetCamera(std::string name, CameraFlag cameraF,float depth)
{
	auto camera = Camera::createOrthographic(1024, 576, -768, 768);
	camera->setName(name);
	this->addChild(camera);
	camera->setPosition3D({ 0, 0, 0 });
	camera->setRotation3D({ 0, 0, 0 });
	camera->setDepth(depth);
	camera->setCameraFlag(cameraF);
	return camera;
}

void GameScene::SelectEnded(int select)
{
	auto gameScene = Director::getInstance()->getRunningScene();
	if (gameScene->getName() != "GameScene")
	{
		return;
	}
	auto player = (Player*)gameScene->getChildByName("charLayer")->getChildByTag(static_cast<int>(objTag::PLAYER));
	// 階層が0だったらチャージ
	if (_floorNum == 0)
	{		
		ChargeType chargeType;
		switch (select)
		{
		case 0:
			chargeType = ChargeType::SHOT;
			break;
		case 1:
			chargeType = ChargeType::TWISTER;
			break;
		case 2:
			chargeType = ChargeType::FLONTAL;
			break;
		default:
			break;
		}
		player->SetChargeType(chargeType);
		_floorNum = 1;
		ChangeSceneType(SceneType::GAME);
	}
	else
	{
		player->SetAbility(retAbility[select]);
		ChangeSceneType(SceneType::GAME);
	}
}

