#pragma once
#include "cocos2d.h"
class GameClearScene : cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	GameClearScene();
	~GameClearScene();

	virtual bool init();
	void ChangeScene(float delta);

	CREATE_FUNC(GameClearScene);
private:

};

