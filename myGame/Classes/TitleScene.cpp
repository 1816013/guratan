#include "TitleScene.h"
#include "GameScene.h"

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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Title Scene", "fonts/Marker Felt.ttf", 24);

	
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 0);
	
	count = 0;
	this->scheduleOnce(schedule_selector(TitleScene::ChangeScene), 1.0f);
	return true;
}

void TitleScene::ChangeScene(float delta)
{	
	Scene *scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, scene));
}
