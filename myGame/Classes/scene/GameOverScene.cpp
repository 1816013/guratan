#include "GameOverScene.h"
#include "TitleScene.h"
#include "GameScene.h"

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
	// �V�[�����O�ݒ�
	this->setName("GameOverScene");
	// �ЂƂO�̼�݂�����
	auto scene = (GameScene*)Director::getInstance()->getRunningScene();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("GameOver Scene", "fonts/Marker Felt.ttf", 24);
	// position the label on the center of the screen
	label->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height - label->getContentSize().height));

	auto label2 = Label::createWithTTF("���B�K�w�@" + StringUtils::toString(scene->_floorNum) + " F", "fonts/PixelMplus12-Regular.ttf", 24);
	// position the label on the center of the screen
	label2->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2 - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 0);
	this->addChild(label2, 0);
	this->scheduleOnce(schedule_selector(GameOverScene::ChangeScene), 3.0f);
	return true;
}

void GameOverScene::ChangeScene(float delta)
{
	Scene *scene = TitleScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3f, scene));
}
