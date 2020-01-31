#pragma once
#include "Obj.h"

class mapObject : public Obj
{
public:
	static cocos2d::Sprite* createMapObj();
	mapObject();
	~mapObject();

	CREATE_FUNC(mapObject);
private:
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;
	cocos2d::Animation* _oldanim;
};