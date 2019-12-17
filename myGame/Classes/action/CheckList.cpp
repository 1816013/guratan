#include "CheckList.h"
#include <Unit/Player.h>

bool CheckList::operator()(cocos2d::Sprite& sp, actModule& module)
{
	//auto nowState = ((Player&)sp).ActState();
	//for (auto black : module.black)
	//{
	//	if (nowState == black)
	//	{
	//		return false;		
	//	}
	//}
	//for (auto white : module.white)
	//{
	//	if (nowState == white)
	//	{
	//		return true;
	//	}
	//}
	///*if (module.white.size() > 0)
	//{
	//	return false;
	//}*/
	return true;
}
