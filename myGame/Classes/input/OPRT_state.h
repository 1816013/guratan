#pragma once
#include "cocos2d.h"
#include <array>
#include <map>

#define intCast(tag) static_cast<int>(tag)

enum class OPRT_TYPE	// ������@
{
	KEY,			// ���ް��
	TOUCH,			// ���
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


enum class INPUT_ID	// ����
{
	UP,			// ��
	RIGHT,		// �E
	DOWN,		// ��
	LEFT,		// ��
	ATTACK,		// �U��
	SELECT,		// ����
	NONE,		// �������Ă��Ȃ�
	MAX			
};

enum class Timing
{
	ON,
	ON_MOM,
	OFF,
	OFF_MOM
};

enum class TRG_STATE	// �ضް����p
{
	NOW,	// ���݂̓���
	OLD,	// �ضް����
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