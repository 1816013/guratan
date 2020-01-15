#pragma once
#include <Unit/Obj.h>

class mapObject : public Obj
{
public:
	static cocos2d::Sprite* createMapObj();
	mapObject();
	~mapObject();
	DIR GetDIR();
	void SetDIR(DIR dir);
	int GetPower();


	CREATE_FUNC(mapObject);
private:
	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;
};