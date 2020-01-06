#pragma once
#include "cocos2d.h"
class TitleScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	TitleScene();
	~TitleScene();

	virtual bool init();
	void ChangeScene(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(TitleScene);

private:
	int count;

};

