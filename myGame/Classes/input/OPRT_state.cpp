#include "OPRT_state.h"

OPRT_state::OPRT_state()
{
	inputTbl.resize(static_cast<int>(INPUT_ID::MAX));
	inputTbl[static_cast<int>(INPUT_ID::UP)] = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW;
	inputTbl[static_cast<int>(INPUT_ID::RIGHT)] = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	inputTbl[static_cast<int>(INPUT_ID::DOWN)] = cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	inputTbl[static_cast<int>(INPUT_ID::LEFT)] = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	inputTbl[static_cast<int>(INPUT_ID::ATTACK)] = cocos2d::EventKeyboard::KeyCode::KEY_SPACE;
	inputTbl[static_cast<int>(INPUT_ID::SELECT)] = cocos2d::EventKeyboard::KeyCode::KEY_ENTER;
	for (auto input : INPUT_ID())
	{
		_keyData[static_cast<int>(TRG_STATE::INPUT)].emplace(inputTbl[static_cast<int>(input)], false);
	};
}

void OPRT_state::update(void)
{	
	auto checkNone = [this]()
	{
		for (auto input : INPUT_ID())
		{
			if (input != INPUT_ID::NONE)
			{
				if (_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(input)]] == true)
				{
					return false;
				}
			}
		}
		return true;
	};
	if (checkNone())
	{
		_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::NONE)]] = true;
	}
	else
	{
		_keyData[static_cast<int>(TRG_STATE::INPUT)][inputTbl[static_cast<int>(INPUT_ID::NONE)]] = false;
	}

	_keyData[static_cast<int>(TRG_STATE::OLD)] = _keyData[static_cast<int>(TRG_STATE::NOW)];
	_keyData[static_cast<int>(TRG_STATE::NOW)] = _keyData[static_cast<int>(TRG_STATE::INPUT)];

	/*for (auto input : INPUT_ID())
	{
		if (_keyData[static_cast<int>(TRG_STATE::NOW)][inputTbl[static_cast<int>(input)]] & ~
			_keyData[static_cast<int>(TRG_STATE::OLD)][inputTbl[static_cast<int>(input)]])
		{
			_keyData[static_cast<int>(TRG_STATE::)][inputTbl[static_cast<int>(input)]
		}
	
	}*/
}

INPUT_ID begin(INPUT_ID)
{
	return INPUT_ID::UP;
}

INPUT_ID end(INPUT_ID)
{
	return INPUT_ID::MAX;
}

INPUT_ID operator*(INPUT_ID key)
{
	return key;
}

INPUT_ID operator++(INPUT_ID & key)
{
	return key = INPUT_ID(std::underlying_type<INPUT_ID>::type(key) + 1);
}
