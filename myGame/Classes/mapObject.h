#pragma once
#include <Unit/Obj.h>

class mapObject : public Obj
{
public:
	static cocos2d::Sprite* createMapObj();
	mapObject();
	~mapObject();
	DIR GetDIR()override;
	void SetDIR(DIR dir)override;
	int GetPower()override;


	CREATE_FUNC(mapObject);
private:
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;
};