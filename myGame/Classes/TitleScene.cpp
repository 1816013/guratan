#include "TitleScene.h"
#include "GameScene.h"
#include "input/OPRT_key.h"

USING_NS_CC;

cocos2d::Scene * TitleScene::createScene()
{
	return TitleScene::create();
}

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

bool TitleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	// シーン名前設定
	this->setName("TitleScene");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Title Scene", "fonts/Marker Felt.ttf", 24);

	auto titleLayer = Layer::create();

	
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	titleLayer->addChild(label, 0);

	// カメラ設定
	auto camera1 = Camera::create();
	camera1->setCameraFlag(CameraFlag::DEFAULT);
	camera1->setPosition3D({ 500, 0, 50 });
	camera1->lookAt({ 500, 0, 0 });
	titleLayer->addChild(camera1);
	titleLayer->setCameraMask((unsigned short)CameraFlag::DEFAULT);
	
	count = 0;
	this->addChild(titleLayer);
	this->scheduleOnce(schedule_selector(TitleScene::ChangeScene), 1.0f);
	return true;
}

void TitleScene::ChangeScene(float delta)
{	
	Scene *scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, scene));
}
