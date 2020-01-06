#include "GameOverScene.h"
#include "TitleScene.h"

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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("GameOver Scene", "fonts/Marker Felt.ttf", 24);
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 0);
	count = 0;
	this->scheduleOnce(schedule_selector(GameOverScene::ChangeScene), 3.0f);
	return true;
}

void GameOverScene::ChangeScene(float delta)
{
	Scene *scene = TitleScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, scene));

}
