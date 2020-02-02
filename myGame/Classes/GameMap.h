#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>

#define MAP_X 32
#define MAP_Y 32

class GameMap
{
public:
	void createMap(cocos2d::Layer& layer);
	GameMap();
	~GameMap();
	bool mapColision(cocos2d::Sprite & sp, cocos2d::Vec2 speed, std::array<cocos2d::Size, 2> colSize);

private:
	cocos2d::Size _mapChipSize = cocos2d::Size(MAP_X, MAP_Y);
	int _mapData[MAP_Y][MAP_X];
};

