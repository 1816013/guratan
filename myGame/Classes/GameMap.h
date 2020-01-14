#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>

#define MAP_X 32
#define MAP_Y 32


struct _rect 
{
	int lx, ly, hx, hy;
};

class GameMap : public cocos2d::Sprite
{
public:
	static cocos2d::Sprite* createMap();
	GameMap();
	~GameMap();
	std::unique_ptr<OPRT_state>_inputState;
	bool mapColision(cocos2d::Sprite & sp, cocos2d::Vec2 speed, std::array<cocos2d::Size, 2> colSize);

	CREATE_FUNC(GameMap);

private:
	bool init()override;
	void update(float delta)override;

	void rectSplit(struct _rect rect_parent);
	struct _rect addRect(int sX, int sY, int eX, int eY);

	

	
	std::vector<struct _rect>_rectList;
	int rectMin = 8;

	cocos2d::Size _mapChipSize = cocos2d::Size(MAP_X, MAP_Y);
	int _mapData[MAP_Y][MAP_X];
};

