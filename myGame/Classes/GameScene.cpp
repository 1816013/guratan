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
#include <Unit/Player.h>
#include <Unit/Enemy.h>
#include <E_Attack.h>
#include <GameMap.h>
#include "GameOverScene.h"
#include "mapObject.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
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
	_sceneType = SceneType::GAME;
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

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
		uiBglayer->addChild(label, 0);
    }

	// キャラクター
	auto player = Player::createPlayer();
	player->setTag(static_cast<int>(objTag::PLAYER));
	
	//followLayer->runAction(Follow::create(player, Rect(0, 0, visibleSize.width * 4, visibleSize.height * 4)));
	charBglayer->addChild(player);
	SetEnemy(EnemyMoveAI::IDLE, EnemyAttackAI::AIMING);
	SetEnemy(EnemyMoveAI::IDLE, EnemyAttackAI::AIMING);
	SetEnemy(EnemyMoveAI::FORROW, EnemyAttackAI::NONE);
	SetEnemy(EnemyMoveAI::FORROW, EnemyAttackAI::NONE);
	SetEnemy(EnemyMoveAI::FORROW, EnemyAttackAI::NONE);

	// ﾏｯﾌﾟ(仮) @ﾏﾈｰｼﾞｬｰ予定
	_gameMap->createMap(*backBglayer);
	/*map->setName("mapMng");
	map->setCameraMask(static_cast<int>(CameraFlag::USER1));
	backBglayer->addChild(map);*/
	mapObj = nullptr;

	// メニュ－
	auto levelupText = Label::createWithTTF("LEVELUP!!", "fonts/Marker Felt.ttf", 24);
	levelupText->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 4 * 3 - levelupText->getContentSize().height));
	MenuBglayer->addChild(levelupText, 0);

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
	camera1->setPosition3D({ player->getPositionX() - visibleSize.width / 2, player->getPositionY() - visibleSize.height / 2, 0 });
	camera1->setRotation3D({ 0, 0, 0 });
	camera1->setDepth(0.0f);
	camera1->setCameraFlag(CameraFlag::USER1);	

	this->setCameraMask(static_cast<int>(CameraFlag::DEFAULT));
	charBglayer->setCameraMask(static_cast<int>(CameraFlag::USER1));
	MenuBglayer->setCameraMask(static_cast<int>(CameraFlag::USER2));

	// ｼｰﾝにぶら下げる
	this->addChild(MenuBglayer, _zOrderMenu);
	this->addChild(uiBglayer, _zOrderUI);
	this->addChild(charBglayer, _zOrderChar);
	this->addChild(backBglayer, _zOrderBack);
	this->addChild(flontBglayer, _zOrderFlont);


	this->scheduleUpdate();
	flag = false;
    return true;
}

void GameScene::update(float delta)
{
	_inputState->update();

	if (_sceneType == SceneType::GAME)
	{
		ColTest();

		/*if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::SELECT) &~_inputState->GetInput(TRG_STATE::OLD, INPUT_ID::SELECT))
		{
			int Rand = rand() % static_cast<int>(EnemyMoveAI::MAX);
			SetEnemy(static_cast<EnemyMoveAI>(Rand));
		}*/
		
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
	}
	else if (_sceneType == SceneType::MENU)
	{
		auto player = (Player*)Director::getInstance()->getRunningScene()->getChildByName("charLayer")->getChildByTag(static_cast<int>(objTag::PLAYER));
		
		if (!flag)	// 一回しかやらない処理
		{
			flag = true;
			// ポーズ処理
			charBglayer->pause();
			for (cocos2d::Node* _node : charBglayer->getChildren())
			{
				_node->pause();
			}
			// カメラセット※上にもっていって使わないときは変な方向に向けたほうが良いかも
			auto camera2 = Camera::createOrthographic(1024, 576, -768, 768);
			camera2->setName("menuCamera");
			this->addChild(camera2);
			camera2->setPosition3D({ 0, 0, 0 });
			camera2->setRotation3D({ 0, 0, 0 });
			camera2->setDepth(3.0f);
			camera2->setCameraFlag(CameraFlag::USER2);
					
			// 仮ｽﾌﾟﾗｲﾄ
			Sprite* sprite[4];
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
					
			auto unAbility = player->GetUnacquiredAbility();
			std::random_device seed;
			std::mt19937 engine(seed());
			std::shuffle(unAbility.begin(), unAbility.end(), engine);
			
			for (int i = 0; i < 3; i++)
			{
				switch (unAbility.back())
				{
				case Ability::PowerUp:
					sprite[i]->setColor(cocos2d::Color3B(255, 0, 0));
					break;
				case Ability::SpeedUp:
					sprite[i]->setColor(cocos2d::Color3B(0, 255, 0));
					break;
				case Ability::RangeAttack:
					sprite[i]->setColor(cocos2d::Color3B(0, 0, 255));
					break;
				}
				retAbility[i] = unAbility.back();
				unAbility.pop_back();
			}
			MenuBglayer->addChild(sprite[0]);
			MenuBglayer->addChild(sprite[1]);
			MenuBglayer->addChild(sprite[2]);
			MenuBglayer->addChild(sprite[3]);
			MenuBglayer->setCameraMask(static_cast<int>(CameraFlag::USER2));
			selectCnt = 0;
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
			player->SetAbility(retAbility[selectCnt]);
			_sceneType = SceneType::GAME;
			flag = false;
			charBglayer->resume();
			for (cocos2d::Node* _node : charBglayer->getChildren())
			{
				_node->resume();
			}
			this->getChildByName("menuCamera")->removeFromParent();
		}
	}
	count++;
}

void GameScene::SetSceneType(SceneType sceneType)
{
	_sceneType = sceneType;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}


void GameScene::SetEnemy(EnemyMoveAI moveAI, EnemyAttackAI attackAI)
{
	auto enemy = Enemy::createEnemy(moveAI, attackAI);
	enemy->setTag(static_cast<int>(objTag::ENEMY));
	enemy->setCameraMask(static_cast<int>(CameraFlag::USER1));
	enemy->setPosition(Vec2(rand() % 800 + 48, rand() % 800 + 48 + 64));
	charBglayer->addChild(enemy);
}

void GameScene::ColTest()
{
	for (auto eRect : this->charBglayer->getChildren())
	{
		int tag = eRect->getTag();
		// enemy当たり判定
		if (tag == static_cast<int>(objTag::ENEMY))
		{
			Enemy* enemy = (Enemy*)eRect;
			for (auto pRect : this->charBglayer->getChildren())
			{
				if (eRect == pRect)
				{
					continue;
				}
				Obj* hitObj = (Obj*)pRect;
				int tag2 = pRect->getTag();
				if (tag2 != tag)
				{
					if (enemy->ColisionObj(hitObj, this->charBglayer))
					{
						return;
					}
				}
			}
		}
		if (tag == static_cast<int>(objTag::PLAYER))
		{
			Player* player = (Player*)eRect;
			for (auto pRect : this->charBglayer->getChildren())
			{
				if (eRect == pRect)
				{
					continue;
				}
				int tag2 = pRect->getTag();
				if (tag2 != tag)
				{
					Obj* hitObj = (Obj*)pRect;
					int tag2 = pRect->getTag();
					if (tag2 != tag)
					{
						if (player->ColisionObj(hitObj, this->charBglayer))
						{
							return;
						}
					}
				}
			}
		}
	}
}
