#include "OPRT_touch.h"

USING_NS_CC;

OPRT_touch::OPRT_touch(Node* sp)
{
	numberOfTouch = 0;
	touchVectors.clear();
	for (int i = 0; i < 5; i++)
	{
		touchVectors.emplace_back(Vec2::ZERO);
	}
	
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = [&](std::vector<Touch*> touches, Event *event)
	{
		auto gameScene = cocos2d::Director::getInstance()->getRunningScene();
		if (gameScene->getName() != "GameScene")
		{
			return false;
		}
		
		for (auto touch : touches) {
			touchVectors[touch->getID()] = touch->getLocation();
			auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();	
			if (touchVectors[touch->getID()].x > visibleSize.width / 2)
			{
				_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::ATTACK)]] = true;		
			}
			else
			{
				auto nowSp = gameScene->getChildByName("uiLayer")->getChildByName("nowTouch");
				auto startSp = gameScene->getChildByName("uiLayer")->getChildByName("startTouch");
				nowSp->setPosition(touchVectors[touch->getID()]);
				startSp->setPosition(touchVectors[touch->getID()]);
			}
		}
		numberOfTouch += touches.size();
		return true;
	};
	listener->onTouchesMoved = [&](std::vector<Touch*> touches, Event *event)
	{
		auto gameScene = cocos2d::Director::getInstance()->getRunningScene();
		if (gameScene->getName() != "GameScene")
		{
			return false;
		}
		auto nowSp = gameScene->getChildByName("uiLayer")->getChildByName("nowTouch");
		auto startSp = gameScene->getChildByName("uiLayer")->getChildByName("startTouch");
		auto line = (cocos2d::DrawNode*)gameScene->getChildByName("uiLayer")->getChildByName("line");
		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
		//auto start_p = _startTPos;
		float margin = 50.0f;
		for (auto touch : touches) {
			auto nowPos = touch->getLocation();
			if (touchVectors[touch->getID()].x < visibleSize.width / 2)
			{
				auto spPos = touch->getLocation();
				// 一定距離以上は丸を移動できない
				auto vec = nowPos - touchVectors[touch->getID()];
				float distance = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
				float rad = atan2(nowPos.y - touchVectors[touch->getID()].y, nowPos.x - touchVectors[touch->getID()].x);
				if (distance > 140)
				{
					float px = 140 * cos(rad);
					float py = 140 * sin(rad);
					spPos.x = px + touchVectors[touch->getID()].x;
					spPos.y = py + touchVectors[touch->getID()].y;
				}
				// 現在位置を更新する
				nowSp->setPosition(spPos);
				// 開始位置と現在位置の間に線を書く
				line->setVisible(true);
				line->clear();
				line->drawLine(touch->getStartLocation(), spPos, { 1.0f, 1.0f, 1.0f, 0.5f });

				// 入力
				if (nowPos.x > touchVectors[touch->getID()].x + margin)
				{
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::LEFT)]] = false;
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::RIGHT)]] = true;
				}

				if (nowPos.x < touchVectors[touch->getID()].x - margin)
				{
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::RIGHT)]] = false;
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::LEFT)]] = true;
				}

				if (nowPos.y > touchVectors[touch->getID()].y + margin)
				{
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::DOWN)]] = false;
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::UP)]] = true;
				}

				if (nowPos.y < touchVectors[touch->getID()].y - margin)
				{
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::UP)]] = false;
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::DOWN)]] = true;				
				}
				if (abs(nowPos.y - touchVectors[touch->getID()].y) < margin)
				{
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::UP)]] = false;
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::DOWN)]] = false;
				}
				if (abs(nowPos.x - touchVectors[touch->getID()].x) < margin)
				{
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::RIGHT)]] = false;
					_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::LEFT)]] = false;
				}
			}

			if (nowPos.x < touchVectors[touch->getID()].x + margin && nowPos.x > touchVectors[touch->getID()].x - margin
				&& nowPos.y < touchVectors[touch->getID()].y + margin && nowPos.y > touchVectors[touch->getID()].y - margin)
			{
				for (auto input : INPUT_ID())
				{
					if (input != INPUT_ID::ATTACK && input != INPUT_ID::SELECT && input != INPUT_ID::NONE)
					{
						_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(input)]] = false;
					}
				}
			}
		}
		return true;
	};
	listener->onTouchesEnded = [this](std::vector<Touch*> touches, Event *event)
	{
		auto gameScene = cocos2d::Director::getInstance()->getRunningScene();
		if (gameScene->getName() != "GameScene")
		{
			return false;
		}
		
		auto nowSp = gameScene->getChildByName("uiLayer")->getChildByName("nowTouch");
		auto startSp = gameScene->getChildByName("uiLayer")->getChildByName("startTouch");
		auto line = (cocos2d::DrawNode*)gameScene->getChildByName("uiLayer")->getChildByName("line");
		numberOfTouch -= touches.size();
		if (numberOfTouch == 0)
		{
			nowSp->setPosition(150, 150);
			startSp->setPosition(150, 150);
			line->setVisible(false);
			for (auto input : INPUT_ID())
			{
				_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(input)]] = false;
			}
		}
		return true;
	};

	sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, sp);
}

OPRT_TYPE OPRT_touch::GetType(void)
{
	return OPRT_TYPE::TOUCH;
}
