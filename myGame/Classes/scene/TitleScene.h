#pragma once
#include "cocos2d.h"
#include "input/OPRT_state.h"
class TitleScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	TitleScene();
	~TitleScene();

	virtual bool init();
	void ChangeScene();

	// implement the "static create()" method manually
	CREATE_FUNC(TitleScene);

private:
	int count;
	std::unique_ptr<OPRT_state>_inputState;
};

