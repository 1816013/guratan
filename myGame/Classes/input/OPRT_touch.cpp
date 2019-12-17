#include "OPRT_touch.h"

USING_NS_CC;

OPRT_touch::OPRT_touch(Node* sp)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		Point pos = touch->getLocation();
		_startTPos = pos;
		return true;
	};
	listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		float margin = 50.0f;
		Point pos = touch->getLocation();
		auto start_p = _startTPos;
		if (pos.x > start_p.x + margin)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::RIGHT)]] = true;
		}

		if (pos.x < start_p.x - margin)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::LEFT)]] = true;
		}

		if (pos.y > start_p.y + margin)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::UP)]] = true;
		}

		if (pos.y < start_p.y - margin)
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::DOWN)]] = true;
			_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::ATACK)]] = true;
		}

		if (pos.x < start_p.x + margin && pos.x > start_p.x - margin
			&& pos.y < start_p.y + margin && pos.y > start_p.y - margin)
		{
			for (auto input : INPUT_ID())
			{
				_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(input)]] = false;
			}
		}
		return true;
	};
	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		for (auto input : INPUT_ID())
		{
			_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(input)]] = false;
		}
		_startTPos = { -9999, -9999 };
		return true;
	};

	sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sp);
}

OPRT_TYPE OPRT_touch::GetType(void)
{
	return OPRT_TYPE::TOUCH;
}
