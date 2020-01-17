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
	auto camera1 = Camera::createOrthographic(visibleSize.width, visibleSize.height, -768, 768);
	this->addChild(camera1);
	camera1->setPosition3D({ 0, 0, 0 });
	camera1->setRotation3D({ 0, 0, 0 });
	camera1->setDepth(0.0f);
	camera1->setCameraFlag(CameraFlag::DEFAULT);

	titleLayer->setCameraMask(static_cast<int>(CameraFlag::DEFAULT));

	
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		this->ChangeScene();
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	/*auto button = MenuItemImage::create(
		"sprite/button_start.png",
		"sprite/button_start.png",
		CC_CALLBACK_1(TitleScene::ChangeScene, this));
	Menu* menu = Menu::create(button, NULL);
	menu->setPosition(visibleSize / 2);
	this->addChild(menu);*/

	count = 0;
	this->addChild(titleLayer);
	//this->scheduleOnce(schedule_selector(TitleScene::ChangeScene), 1.0f);
	return true;
}

//void TitleScene::ChangeScene(float delta)
//{	
//	Scene *scene = GameScene::createScene();
//	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, scene));
//}

void TitleScene::ChangeScene()
{
	Scene *scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, scene));
}
