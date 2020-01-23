#pragma once
#include "cocos2d.h"

#define lpFloorMng FloorMng::GetInstance()

class FloorMng
{
public:
	static FloorMng & GetInstance(void)
	{
		return *s_Instance;
	}
	~FloorMng();

	void UpFloor();
private:
	FloorMng();

	int _floorLevel;
	
	static std::unique_ptr<FloorMng> s_Instance;
};