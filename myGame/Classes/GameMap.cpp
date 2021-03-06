#include "GameMap.h"
#include <input/OPRT_key.h>
#include <input/OPRT_touch.h>

USING_NS_CC;

GameMap::GameMap()
{

}

GameMap::~GameMap()
{
}
void GameMap::createMap(Layer& layer)
{
	auto mapS = TMXTiledMap::create("map/map2.tmx");
	mapS->setName("mapData");
	mapS->setCameraMask(static_cast<int>(CameraFlag::USER1));
	layer.addChild(mapS);
}


bool GameMap::mapColision(cocos2d::Sprite & sp, cocos2d::Vec2 speed, std::array<cocos2d::Size, 2> colSize)
{
	auto gameScene = Director::getInstance()->getRunningScene();
	if (gameScene->getName() != "GameScene")
	{
		return false;
	}
	auto map = (TMXTiledMap*)gameScene->getChildByName("backLayer")->getChildByName("mapData");
	auto col = map->getLayer("wall");
	auto mapSize = map->getMapSize();
	auto tileSize = col->getMapTileSize();

	Vec2 pos = sp.getPosition();
	std::array<Vec2, 2>arrayID;
	for (int i = 0; i < 2; i++)
	{
		// ｺﾘｼﾞｮﾝｵﾌｾｯﾄ
		Vec2 colOffset = { Vec2(speed.x + colSize[i].width,
								speed.y + colSize[i].height) };

		arrayID[i] = { (pos.x + colOffset.x) / tileSize.width,
					mapSize.height - ((pos.y + colOffset.y) / tileSize.height) };	// ﾌﾟﾚｲﾔｰ座標のID	

		if (arrayID[i].x < mapSize.width && arrayID[i].y < mapSize.height && arrayID[i].x > 0 && arrayID[i].y > 0)
		{
			if (col->getTileGIDAt({ arrayID[i].x, arrayID[i].y }) != 0)	// mapTileは0が空白
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}


