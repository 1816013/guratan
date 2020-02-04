#include "LoadingScene.h"
#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene * LoadingScene::createScene()
{
	return LoadingScene::create();
}

LoadingScene::LoadingScene()
{
}


LoadingScene::~LoadingScene()
{
	_scene->release();
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	// シーン名前設定
	this->setName("LoadingScene");
	// ひとつ前のｼｰﾝが取れる
	_scene = Director::getInstance()->getRunningScene();
	_scene->retain();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 階数表示
	Label* label;
	if (_scene->getName() == "GameScene")
	{
		auto gameScene = (GameScene*)Director::getInstance()->getRunningScene();
		int floorNum = gameScene->_floorNum;
		label = Label::createWithTTF(StringUtils::toString(floorNum + 1) + " F", "fonts/PixelMplus12-Regular.ttf", 48);
	}
	else
	{
		label = Label::createWithTTF("1 F", "fonts/PixelMplus12-Regular.ttf", 48);
	}
	label->setPosition(Vec2( visibleSize.width / 2, visibleSize.height / 2));
	label->setCameraMask(static_cast<int>(CameraFlag::DEFAULT));
	this->addChild(label, 0);
	this->scheduleOnce(schedule_selector(LoadingScene::ChangeScene), 3.0f);
	return true;
}

void LoadingScene::ChangeScene(float delta)
{
	//Scene *scene = LoadingScene::createScene();
	if (_scene->getName() == "GameScene")
	{
		Director::getInstance()->popScene();
	}
	else
	{
		Director::getInstance()->replaceScene(GameScene::createScene());
	}
	
}
