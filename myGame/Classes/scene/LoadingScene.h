#pragma once
#include "cocos2d.h"
class LoadingScene : cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	LoadingScene();
	~LoadingScene();

	virtual bool init();
	void ChangeScene(float delta);

	CREATE_FUNC(LoadingScene);
private:
	cocos2d::Scene* _scene;
};


