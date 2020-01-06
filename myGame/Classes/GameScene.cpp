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
#include <action/CheckKey.h>
#include <Unit/Player.h>
#include <Unit/Enemy.h>
#include <GameMap.h>
#include "GameOverScene.h"

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
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32	
	_inputState = std::make_unique<OPRT_key>(this);
#else
	_inputState.reset(new OPRT_touch(this));
	//_inputState = std::make_unique<OPRT_touch>();
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)


	_zOrderUI = static_cast<int>(Z_ORDER_TYPE::UI);	
	_zOrderFlont = static_cast<int>(Z_ORDER_TYPE::FLONT);
	_zOrderChar = static_cast<int>(Z_ORDER_TYPE::CHAR);	
	_zOrderBack = static_cast<int>(Z_ORDER_TYPE::BACK);
	
	uiBglayer = Layer::create();
	uiBglayer->setName("uiLayer");
	charBglayer = Layer::create();
	charBglayer->setName("charLayer");
	flontBglayer = Layer::create();
	flontBglayer->setName("flontLayer");
	backBglayer = Layer::create();
	backBglayer->setName("backLayer");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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

	/*//auto _scrollView = ui::ScrollView::create();
	//_scrollView->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//_scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	//_scrollView->setBounceEnabled(true);
	//this->addChild(_scrollView);


	////スクロールする中身を追加（LayerやSpriteなど）
	//_scrollView->addChild(uiBglayer);

	////中身のサイズを指定
	//_scrollView->setInnerContainerSize(Size(uiBglayer->getContentSize().width, uiBglayer->getContentSize().height));

	////実際に表示される領域（これ以外は隠れる)
	//auto inveSize = Size(uiBglayer->getContentSize().width, visibleSize.height / 2);
	//_scrollView->setContentSize(inveSize);*/
	this->runAction(Follow::create(uiBglayer, Rect(0, 0, visibleSize.width * 4, visibleSize.height * 4)));
	// プレイヤー
	auto player = Player::createPlayer();
	player->setTag(static_cast<int>(objTag::PLAYER));
	this->runAction(Follow::create(player, Rect(0, 0, visibleSize.width * 4, visibleSize.height * 4)));
	charBglayer->addChild(player);

	auto enemy = Enemy::createEnemy(EnemyAI::IDLE);
	enemy->setTag(static_cast<int>(objTag::ENEMY));
	enemy->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	charBglayer->addChild(enemy);

	
	// ﾏｯﾌﾟ(仮) @ﾏﾈｰｼﾞｬｰ予定
	auto map = GameMap::createMap();
	map->setTag(3);
	backBglayer->addChild(map);
	/*mapChipSize = Size( 32.0f, 32.0f );
	for (int y = 0; y < 18; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			mapData[y][x] = 0;
			if (y == 0 || y == 17 || x == 0 || x == 31)
			{
				mapData[y][x] = 1;
				Rect rect = Rect(0, 0, 32, 32);
				Sprite* square = Sprite::create();
				square->setTextureRect(rect);
				square->setPosition(x * 32 + 16, y * 32 + 16);
				
				backBglayer->addChild(square);
				square->setGlobalZOrder(10);
			}
		}
	}*/
	
	// ｼｰﾝにぶら下げる
	this->addChild(uiBglayer, _zOrderUI);
	this->addChild(backBglayer, _zOrderBack);
	this->addChild(charBglayer, _zOrderChar);
	this->addChild(flontBglayer, _zOrderFlont);

	this->scheduleUpdate();
    return true;
}

void GameScene::update(float delta)
{
	_inputState->update();

	//ScrollUI();
	ColTest();
	
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::ATACK) &~ _inputState->GetInput(TRG_STATE::OLD, INPUT_ID::ATACK))
	{
		count++;
		auto enemy = Enemy::createEnemy(EnemyAI::IDLE);
		enemy->setTag(1);
		enemy->setPosition(Vec2(count * 32 + 32, 32 + 32));
		charBglayer->addChild(enemy);
	}
	obj->IsCheckedHP();
	int count = 0;
	for (auto eRect : this->charBglayer->getChildren())
	{
		int tag = eRect->getTag();
		if (static_cast<int>(objTag::PLAYER) == tag)
		{
			count++;
		}
	}
	if (count <= 0)
	{
		Scene *scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.3f, scene));
	}
}


void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void GameScene::ScrollUI()
{
	//auto player = this->getChildByName("charLayer")->getChildByTag(static_cast<int>(objTag::PLAYER));
	//uiBglayer->setPosition({0, 0});
}

void GameScene::ColTest()
{
	bool flag = false;
	Rect rectA;
	Rect rectE;
	for (auto eRect : this->charBglayer->getChildren())
	{
		int tag = eRect->getTag();
		/*if (tag == 1)
		{*/
		Obj* obj = (Obj*)eRect;
		for (auto pRect : this->charBglayer->getChildren())
		{
			if (eRect == pRect)
			{
				continue;
			}
			Obj* obj2 = (Obj*)pRect;

			int tag2 = pRect->getTag();
			if (tag2 != tag)
			{
				rectA = eRect->getBoundingBox();
				rectE = pRect->getBoundingBox();

				if (rectA.intersectsRect(rectE))
				{
					obj->SetHP(obj->GetHP() - 1);
					obj2->SetHP(obj2->GetHP() - 1);

					//eRect->removeFromParent();
					flag = true;
					return;
				}
			}		
		}
	}
}
