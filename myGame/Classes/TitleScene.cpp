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

	auto titleLayer = Layer::create();

	auto titleRogo = Sprite::create("image/title.png");
	titleRogo->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - titleRogo->getContentSize().height));
	titleLayer->addChild(titleRogo, 0);


	// カメラ設定
	auto camera1 = Camera::createOrthographic(visibleSize.width, visibleSize.height, -768, 768);
	this->addChild(camera1);
	camera1->setPosition3D({ 0, 0, 0 });
	camera1->setRotation3D({ 0, 0, 0 });
	camera1->setDepth(0.0f);
	camera1->setCameraFlag(CameraFlag::DEFAULT);

	titleLayer->setCameraMask(static_cast<int>(CameraFlag::DEFAULT));

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32	
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		this->ChangeScene();
	};
	auto label = Label::createWithTTF("To Start Press Any Key ", "fonts/PixelMplus12-Regular.ttf", 96);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 3 - label->getContentSize().height));

	// add the label as a child to this layer
	titleLayer->addChild(label, 0);
#else
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		this->ChangeScene();
		return true;
	};
	auto label = Label::createWithTTF("Tap To Start ", "fonts/Marker Felt.ttf", 48);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 3 - label->getContentSize().height));

	// add the label as a child to this layer
	titleLayer->addChild(label, 0);
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	count = 0;
	this->addChild(titleLayer);
	//this->scheduleOnce(schedule_selector(TitleScene::ChangeScene), 1.0f);
	return true;
}

void TitleScene::ChangeScene()
{
	Scene *scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, scene));
}
