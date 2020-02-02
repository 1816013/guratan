#include "Colision.h"
#include <algorithm>
#include <array>
#include <obj/Player.h>


USING_NS_CC;

bool actColision::operator()(Sprite & sp, actModule& module) const // “–‚½‚è”»’è
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
		// ºØ¼Þ®ÝµÌ¾¯Ä
		Vec2 colOffset = { Vec2((module.speed.x * ((Player&)sp).GetMovePower()) +module.colSize[i].width,
							 ( module.speed.y* ((Player&)sp).GetMovePower()) + module.colSize[i].height) };

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
