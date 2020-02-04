#pragma once
#include "cocos2d.h"
class GameOverScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	GameOverScene();
	~GameOverScene();

	virtual bool init();
	void ChangeScene();
	CREATE_FUNC(GameOverScene);
private:
	void StartBGM(float delta);
};

