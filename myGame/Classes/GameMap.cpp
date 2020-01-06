#include "GameMap.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>

USING_NS_CC;
cocos2d::Sprite * GameMap::createMap()
{
	return GameMap::create();
}

GameMap::GameMap()
{

}

GameMap::~GameMap()
{
}

bool GameMap::init()
{
	if (!Sprite::init())
	{
		return false;
	}
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32	
	_inputState = std::make_unique<OPRT_key>(this);
#else
	_inputState.reset(new OPRT_touch(this));
	//_inputState = std::make_unique<OPRT_touch>();
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	//_mapChipSize = Size(32.0f, 32.0f);
	
	for (int y = 0; y < _mapChipSize.height; y++)
	{
		for (int x = 0; x < _mapChipSize.width; x++)
		{
			_mapData[y][x] = 0;
			if (y == 0 || y == _mapChipSize.height - 1 || x == 0 || x == _mapChipSize.width - 1)
			{
				_mapData[y][x] = 1;
				Rect rect = Rect(0, 0, 32, 32);
				Sprite* square = Sprite::create();
				square->setTextureRect(rect);
				square->setPosition(x * 32 + 16, y * 32 + 16);
				square->setColor(cocos2d::Color3B(255, 255, 255));
				this->addChild(square);
			}
		}
	}
	//_rectList.clear();
	//rectSplit(addRect(0, 0, _mapChipSize.width - 1, _mapChipSize.height - 1));

	//int i, j;
	////struct _rect *rect;
	//for (auto list : _rectList) {
	//	for (i = list.lx, j = list.ly; i <= list.hx; i++) _mapData[j][i] = 1;
	//	for (i = list.lx, j = list.hy; i <= list.hx; i++) _mapData[j][i] = 1;
	//	for (i = list.lx, j = list.ly; j <= list.hy; j++) _mapData[j][i] = 1;
	//	for (i = list.hx, j = list.ly; j <= list.hy; j++) _mapData[j][i] = 1;
	//};
	//
	//for (int y = 0; y < _mapChipSize.height; y++)
	//{
	//	for (int x = 0; x < _mapChipSize.width; x++)
	//	{
	//		if (_mapData[y][x] == 1)
	//		{
	//			Rect rect = Rect(0, 0, 8, 8);
	//			Sprite* square = Sprite::create();
	//			square->setTextureRect(rect);
	//			square->setPosition(x * rect.getMaxX() + rect.getMaxX() / 2, y * rect.getMaxY() + rect.getMaxY() / 2);
	//			square->setColor(cocos2d::Color3B(255, 255, 255));
	//			square->setTag(10);
	//			this->addChild(square);
	//		}
	//	}
	//}
	this->scheduleUpdate();
	return true;
}

void GameMap::update(float delta)
{
	_inputState->update();
	/*if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::ATACK))
	{
		_rectList.clear();
		rectSplit(addRect(0, 0, _mapChipSize.width - 1, _mapChipSize.height - 1));

		int i, j;
		for (auto list : _rectList) {
			for (i = list.lx, j = list.ly; i <= list.hx; i++) _mapData[j][i] = 1;
			for (i = list.lx, j = list.hy; i <= list.hx; i++) _mapData[j][i] = 1;
			for (i = list.lx, j = list.ly; j <= list.hy; j++) _mapData[j][i] = 1;
			for (i = list.hx, j = list.ly; j <= list.hy; j++) _mapData[j][i] = 1;
		};
		for (int y = 0; y < _mapChipSize.height; y++)
		{
			for (int x = 0; x < _mapChipSize.width; x++)
			{
				if (_mapData[y][x] == 1)
				{
					Rect rect = Rect(0, 0, 8, 8);
					Sprite* square = Sprite::create();
					square->setTextureRect(rect);
					square->setPosition(x * rect.getMaxX() + rect.getMaxX() / 2, y * rect.getMaxY() + rect.getMaxY() / 2);
					square->setColor(cocos2d::Color3B(255, 255, 255));		
					square->setTag(10);
					this->addChild(square);
					
				}
			}
		}
	}*/
	/*if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::UP))
	{

	}
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::RIGHT))
	{

	}
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::DOWN))
	{

	}
	if (_inputState->GetInput(TRG_STATE::NOW, INPUT_ID::LEFT))
	{

	}*/
	
}

void GameMap::rectSplit(struct _rect rect_parent)
{
	//struct _rect rect_child;
	//if ((rect_parent.hy - rect_parent.ly <= rectMin * 3) ||
	//	(rect_parent.hx - rect_parent.lx <= rectMin * 3)) {
	//	return;
	//};
	//rect_child = addRect(rect_parent.lx, rect_parent.ly,
	//	rect_parent.hx, rect_parent.hy);
	//if (rand()% 2 == 0) {
	//	int split_coord_y;
	//	split_coord_y = rand() % (rect_parent.hy - rect_parent.ly) + rectMin;//(rect_parent.hy - rectMin)) + (rect_parent.ly + rectMin);//g_random_int_range(rect_parent->ly + MINIMUM_RECT_SIZE, rect_parent->hy - MINIMUM_RECT_SIZE);
	//	rect_parent.hy = split_coord_y;
	//	rect_child.ly = split_coord_y;
	//	rectSplit(rect_parent);
	//	rectSplit(rect_child);
	//	return;
	//}
	//else {
	//	int split_coord_x;
	//	split_coord_x = rand() % (rect_parent.hx - rect_parent.lx) + rectMin;//(rand() % (rect_parent.hx - rectMin)) + (rect_parent.lx + rectMin);//g_random_int_range(rect_parent->lx + MINIMUM_RECT_SIZE, rect_parent->hx - MINIMUM_RECT_SIZE);
	//	rect_parent.hx = split_coord_x;
	//	rect_child.lx = split_coord_x;
	//	rectSplit(rect_parent);
	//	rectSplit(rect_child);
	//	return;
	//};
}

_rect GameMap::addRect(int sX, int sY, int eX, int eY)
{
	struct _rect rect;
	/*rect.lx = sX;
	rect.ly = sY;
	rect.hx = eX;
	rect.hy = eY;
	_rectList.emplace_back(rect);*/
	return rect;
}


