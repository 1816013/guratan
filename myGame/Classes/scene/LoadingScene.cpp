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
	auto scene = (GameScene*)Director::getInstance()->getRunningScene();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 階数表示
	auto label = Label::createWithTTF(StringUtils::toString(scene->_floorNum + 1) + " F", "fonts/PixelMplus12-Regular.ttf", 48);
	label->setPosition(Vec2( visibleSize.width / 2, visibleSize.height / 2));
	label->setCameraMask(static_cast<int>(CameraFlag::DEFAULT));
	this->addChild(label, 0);
	this->scheduleOnce(schedule_selector(LoadingScene::ChangeScene), 3.0f);
	return true;
}

void LoadingScene::ChangeScene(float delta)
{
	//Scene *scene = LoadingScene::createScene();
	Director::getInstance()->popScene();
}
