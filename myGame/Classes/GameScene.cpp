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

#include "GameScene.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>
#include "Weapon.h"
#include <E_Attack.h>
#include "GameOverScene.h"
#include "mapObject.h"
//#include <proj.win32/_debug/_DebugConOut.h>

USING_NS_CC;

Scene* GameScene::createScene()
{
	Scene *ret = new (std::nothrow)GameScene();
	if (ret && ret->initWithPhysics() && ret->init()) {
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
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
	auto world = getPhysicsWorld();
	world->setGravity(Vec2(0, 0));
	world->setSpeed(1.0f);
	world->setSubsteps(1);
	//world->setDebugDrawMask(0xffff);
	// シーン設定
	this->setName("GameScene");
	_sceneType = SceneType::MENU;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32	
	_inputState = std::make_unique<OPRT_key>(this);
	_gameMap = std::make_unique<GameMap>();
#else
	_inputState.reset(new OPRT_touch(this));
	//_inputState = std::make_unique<OPRT_touch>();
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	// レイヤー設定
	_zOrderMenu = static_cast<int>(Z_ORDER_TYPE::MENU);
	_zOrderUI = static_cast<int>(Z_ORDER_TYPE::UI);	
	_zOrderFlont = static_cast<int>(Z_ORDER_TYPE::FLONT);
	_zOrderChar = static_cast<int>(Z_ORDER_TYPE::CHAR);	
	_zOrderBack = static_cast<int>(Z_ORDER_TYPE::BACK);
	
	MenuBglayer = Layer::create();
	/*auto _bg = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
	MenuBglayer->addChild(_bg);*/
	MenuBglayer->setName("menuLayer");
	uiBglayer = Layer::create();
	uiBglayer->setName("uiLayer");
	charBglayer = Layer::create();
	charBglayer->setName("charLayer");
	flontBglayer = Layer::create();
	flontBglayer->setName("flontLayer");
	backBglayer = Layer::create();
	backBglayer->setName("backLayer");

	
	// UI
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
	uiBglayer->addChild(menu, 0);

    /////////////////////////////
    // 3. add your codes below...
	// キャラクター
	auto player = Player::createPlayer();
	player->setTag(static_cast<int>(objTag::PLAYER));
	charBglayer->addChild(player);
	
	for (int i = 0; i < 5; i++)
	{
		int randAi = rand() % static_cast<int>(EnemyType::MAX);
		SetEnemy(static_cast<EnemyType>(randAi));
	}

	// ﾏｯﾌﾟ(仮) @ﾏﾈｰｼﾞｬｰ予定
	_gameMap->createMap(*backBglayer);
	mapObj = nullptr;

	// 仮ｽﾌﾟﾗｲﾄ メニュー用
	cocos2d::Rect rect = cocos2d::Rect(0, 0, 50, 50);
	cocos2d::Rect selectRect = cocos2d::Rect(0, 0, 20, 20);
	sprite[0] = Sprite::create();
	sprite[0]->setPosition(400, 300);
	sprite[0]->setTextureRect(rect);

	sprite[1] = Sprite::create();
	sprite[1]->setPosition(500, 300);
	sprite[1]->setTextureRect(rect);

	sprite[2] = Sprite::create();
	sprite[2]->setPosition(600, 300);
	sprite[2]->setTextureRect(rect);

	sprite[3] = Sprite::create();
	sprite[3]->setPosition(500, 300);
	sprite[3]->setColor({ 255, 255, 255 });
	sprite[3]->setTextureRect(selectRect);
	sprite[3]->setName("select");

	MenuBglayer->addChild(sprite[0]);
	MenuBglayer->addChild(sprite[1]);
	MenuBglayer->addChild(sprite[2]);
	MenuBglayer->addChild(sprite[3]);

	// カメラ
	auto camera = Camera::createOrthographic(visibleSize.width, visibleSize.height, -768, 768);
	this->addChild(camera);
	camera->setPosition3D({ 0, 0, 0 });
	camera->setRotation3D({ 0, 0, 0 });
	camera->setDepth(1.0f);
	camera->setCameraFlag(CameraFlag::DEFAULT);

	auto camera1 = Camera::createOrthographic(visibleSize.width, visibleSize.height, -768, 768);
	camera1->setName("playerCamera");
	this->addChild(camera1);
	camera1->setPosition3D({ 0, 0, 0 });
	camera1->setRotation3D({ 0, 0, 0 });
	camera1->setDepth(0.0f);
	camera1->setCameraFlag(CameraFlag::USER1);	
	
	auto camera2 = Camera::createOrthographic(1024, 576, -768, 768);
	camera2->setName("menuCamera");
	this->addChild(camera2);
	camera2->setPosition3D({ -1024,-576, 0 });
	camera2->setRotation3D({ 0, 0, 0 });
	camera2->setDepth(3.0f);
	camera2->setCameraFlag(CameraFlag::USER2);

	MenuBglayer->setCameraMask(static_cast<int>(CameraFlag::USER2));
	this->setCameraMask(static_cast<int>(CameraFlag::DEFAULT));
	charBglayer->setCameraMask(static_cast<int>(CameraFlag::USER1));
	

	// 変数
	flag = false;
	_floorNum = 0;
	_nextFloor = false;


	// ｼｰﾝにぶら下げる
	this->addChild(MenuBglayer, _zOrderMenu);
	this->addChild(uiBglayer, _zOrderUI);
	this->addChild(charBglayer, _zOrderChar);
	this->addChild(backBglayer, _zOrderBack);
	this->addChild(flontBglayer, _zOrderFlont);

	charBglayer->pause();
	for (cocos2d::Node* _node : charBglayer->getChildren())
	{
		_node->pause();
	}
	this->scheduleUpdate();
	return true;
}

void GameScene::update(float delta)
{
	_inputState->update();

	if (_sceneType == SceneType::GAME)
	{
		ColTest();		
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
			Director::getInstance()->replaceScene(TransitionFade::create(0.3f, scene));
		}
		if (eCount <= 0 && mapObj == nullptr)
		{
			mapObj = mapObject::createMapObj();
			mapObj->setTag(static_cast<int>(objTag::MAPOBJ));
			mapObj->setCameraMask(static_cast<int>(CameraFlag::USER1));
			charBglayer->addChild(mapObj);
		}
		
		if (_nextFloor)
		{
			ChangeFloor();
		}
	}
	else if (_sceneType == SceneType::MENU)
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
			if (_floorNum != 0)
			{
				auto unAbility = player->GetUnacquiredAbility();
				std::random_device seed;
				std::mt19937 engine(seed());
				std::shuffle(unAbility.begin(), unAbility.end(), engine);

				for (int i = 0; i < 3; i++)
				{
					// メニュ－
					auto levelupText = Label::createWithTTF("LEVELUP!!", "fonts/Marker Felt.ttf", 24);
					levelupText->setPosition(Vec2( 1024 / 2,
						576 / 4 * 3 - levelupText->getContentSize().height));
					levelupText->setCameraMask(static_cast<int>(CameraFlag::USER2));
					levelupText->setName("Text");
					MenuBglayer->addChild(levelupText, 0);
					switch (unAbility.back())
					{
					case Ability::PowerUp:
						sprite[i]->setColor(cocos2d::Color3B(255, 0, 0));
						break;
					case Ability::SpeedUp:
						sprite[i]->setColor(cocos2d::Color3B(0, 255, 0));
						break; 
					case Ability::Heal:
						sprite[i]->setColor(cocos2d::Color3B(0, 0, 255));
						break;
					case Ability::ChargeLevel:
						sprite[i]->setColor(cocos2d::Color3B(255, 212, 0));
						break;
					case Ability::ChargeSpeed:
						sprite[i]->setColor(cocos2d::Color3B(0, 174, 239));
						break;
					}
					retAbility[i] = unAbility.back();
					unAbility.pop_back();
				}
			}
			else // 階層が一の時はじめ
			{			
				// メニュ－
				auto ChargeSelect = Label::createWithTTF("ChargeSelect", "fonts/Marker Felt.ttf", 24);
				ChargeSelect->setPosition(Vec2(1024 / 2,
					576 / 4 * 3 - ChargeSelect->getContentSize().height));
				ChargeSelect->setName("Text");
				ChargeSelect->setCameraMask(static_cast<int>(CameraFlag::USER2));
				MenuBglayer->addChild(ChargeSelect, 0);
				sprite[0]->setColor(cocos2d::Color3B(255, 0, 0));
				sprite[1]->setColor(cocos2d::Color3B(0, 255, 0));	
				sprite[2]->setColor(cocos2d::Color3B(0, 0, 255));
			}
			this->getChildByName("menuCamera")->setPosition3D({ 0, 0, 0 });
			//
		}
		// PCのみ
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
			selectRect->setPosition(400, 300);
			break;
		case 1:
			selectRect->setPosition(500, 300);
			break;
		case 2:
			selectRect->setPosition(600, 300);
			break;
		default:
			break;
		}

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
			_sceneType = SceneType::GAME;
			flag = false;
			charBglayer->resume();
			for (cocos2d::Node* _node : charBglayer->getChildren())
			{
				_node->resume();
			}
			MenuBglayer->getChildByName("Text")->removeFromParent();
			this->getChildByName("menuCamera")->setPosition3D({ -1024, -576, 0 });
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
	enemy->setPosition(Vec2(rand() % 800 + 48, rand() % 400 + 48 + 64));
	charBglayer->addChild(enemy);
}

void GameScene::ColTest()
{
	for (auto eRect : this->charBglayer->getChildren())
	{
		for (auto pRect : this->charBglayer->getChildren())
		{
			if (eRect == pRect)
			{
				continue;
			}
			if (eRect->getTag() != pRect->getTag())
			{
				Obj* obj = (Obj*)eRect;
				Obj* hitObj = (Obj*)pRect;
				obj->ColisionObj(*hitObj, *this);
			}
		}
	}
}

bool GameScene::ChangeFloor()
{
	_nextFloor = false;
	mapObj = nullptr;
	_floorNum++;
	for (int i = 0; i < 5; i++)
	{
		int randAi = rand() % static_cast<int>(EnemyType::MAX);
		SetEnemy(static_cast<EnemyType>(randAi));
	}
	charBglayer->getChildByTag(static_cast<int>(objTag::MAPOBJ))->removeFromParent();
//	TRACE("floor %d", _floorNum);
	return true;
}

