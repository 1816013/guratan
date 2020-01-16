#include "GameMap.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>

USING_NS_CC;
void GameMap::createMap(Layer& layer)
{
	auto mapS = TMXTiledMap::create("map/map1.tmx");
	mapS->setName("mapData");
	mapS->setCameraMask(static_cast<int>(CameraFlag::USER1));
	layer.addChild(mapS);
}

GameMap::GameMap()
{

}

GameMap::~GameMap()
{
}

bool GameMap::init()
{
	return true;
}

bool GameMap::mapColision(cocos2d::Sprite & sp, cocos2d::Vec2 speed, std::array<cocos2d::Size, 2> colSize)
{
	auto directer = Director::getInstance();
	auto map = (TMXTiledMap*)directer->getRunningScene()->getChildByName("backLayer")->getChildByName("mapData");
	auto col = map->getLayer("wall");
	auto mapSize = map->getMapSize();
	auto tileSize = col->getMapTileSize();

	Vec2 pos = sp.getPosition();
	std::array<Vec2, 2>arrayID;
	/*std::array<Vec2, 3>IDarray;
	IDarray = { ID ,Vec2{0, 0} , mapSize };
	auto minMax = std::minmax_element(IDarray.begin(), IDarray.end());*/
	//if(*minMax.first == Vec2(0, 0) && *minMax.second == mapSize)
	for (int i = 0; i < 2; i++)
	{
		// ºØ¼Þ®ÝµÌ¾¯Ä
		Vec2 colOffset = { Vec2(speed.x + colSize[i].width,
								speed.y + colSize[i].height) };

		arrayID[i] = { (pos.x + colOffset.x) / tileSize.width,
					mapSize.height - ((pos.y + colOffset.y) / tileSize.height) };	// ÌßÚ²Ô°À•W‚ÌID	

		if (arrayID[i].x < mapSize.width && arrayID[i].y < mapSize.height && arrayID[i].x > 0 && arrayID[i].y > 0)
		{
			if (col->getTileGIDAt({ arrayID[i].x, arrayID[i].y }) != 0)	// mapTile‚Í0‚ª‹ó”’
			{
				return false;
			}
		}
	}
	return true;
}


