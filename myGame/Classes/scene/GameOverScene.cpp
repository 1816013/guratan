#include "GameOverScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SoundMng.h"
#pragma execution_character_set("utf-8")
USING_NS_CC;

cocos2d::Scene * GameOverScene::createScene()
{
	return GameOverScene::create();
}

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	// シーン名前設定
	this->setName("GameOverScene");
	// ひとつ前のｼｰﾝが取れる
	auto scene = (GameScene*)Director::getInstance()->getRunningScene();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32	
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		this->ChangeScene();
	};
	auto label3 = Label::createWithTTF("Return Title By Press Any Key ", "fonts/PixelMplus12-Regular.ttf", 32);
	label3->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 3 - label3->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label3, 0);
#else
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		this->ChangeScene();
		return true;
	};
	auto label3 = Label::createWithTTF("Tap To Return Title ", "fonts/PixelMplus12-Regular.ttf", 32);
	label3->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 3 - label3->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label3, 0);
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	auto label2 = Label::createWithTTF("到達階層　" + StringUtils::toString(scene->_floorNum) + " F", "fonts/PixelMplus12-Regular.ttf", 48);
	// position the label on the center of the screen
	label2->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 4 * 3 - label2->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label2, 0);

	this->scheduleOnce(schedule_selector(GameOverScene::StartBGM), 2.0f);
	return true;
}

void GameOverScene::ChangeScene()
{
	lpSoundMng.StopBySoundName("gameOverBGM2");
	Scene *scene = TitleScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene, Color3B::WHITE));
}

void GameOverScene::StartBGM(float delta)
{
	lpSoundMng.PlayBySoundName("gameOverBGM2");
}
