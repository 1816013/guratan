#pragma once
#include "cocos2d.h"
#include <array>
#include <map>

#define intCast(tag) static_cast<int>(tag)

enum class OPRT_TYPE	// 操作方法
{
	KEY,			// ｷｰﾎﾞｰﾄﾞ
	TOUCH,			// ﾀｯﾁ
	MAX
};

enum class DIR
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	MAX
};


enum class INPUT_ID	// 入力
{
	UP,			// 上
	RIGHT,		// 右
	DOWN,		// 下
	LEFT,		// 左
	ATTACK,		// 攻撃
	SELECT,		// 決定
	NONE,		// 何もしていない
	MAX			
};

enum class Timing
{
	ON,
	ON_MOM,
	OFF,
	OFF_MOM
};

enum class TRG_STATE	// ﾄﾘｶﾞｰ判定用
{
	NOW,	// 現在の入力
	OLD,	// ﾄﾘｶﾞｰ入力
	INPUT,	//
	MAX
};

using KeyMap = std::map<cocos2d::EventKeyboard::KeyCode, bool>;
using TRG_ArrayKey = std::array<KeyMap, intCast(TRG_STATE::MAX)>;


struct OPRT_state
{
	OPRT_state();
	virtual OPRT_TYPE GetType(void) = 0;

	void update(void);
	void Init(void);
	
	bool GetInput(TRG_STATE trg, INPUT_ID inputID)
	{
		return _keyData[intCast(trg)][inputTbl[static_cast<int>(inputID)]];
	};
protected:
	TRG_ArrayKey _keyData;
	std::vector<cocos2d::EventKeyboard::KeyCode>inputTbl;
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator*(INPUT_ID key);
INPUT_ID operator++(INPUT_ID & key);