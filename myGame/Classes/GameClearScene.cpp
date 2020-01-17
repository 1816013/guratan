#include "GameClearScene.h"
#include "TitleScene.h"

USING_NS_CC;

cocos2d::Scene * GameClearScene::createScene()
{
	return GameClearScene::create();
}

GameClearScene::GameClearScene()
{
}

GameClearScene::~GameClearScene()
{
}

bool GameClearScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	// ƒV[ƒ“–¼‘OÝ’è
	this->setName("GameClearScene");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("GameClear Scene ", "fonts/Marker Felt.ttf", 24);
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 0);
	this->scheduleOnce(schedule_selector(GameClearScene::ChangeScene), 3.0f);
	return true;
}

void GameClearScene::ChangeScene(float delta)
{
	Scene *scene = TitleScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, scene));
}
