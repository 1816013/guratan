#include"Obj.h"
#include <array>
#include "input/OPRT_state.h"

class Enemy : public Obj
{
public:
	static cocos2d::Sprite* createSprite();

	// ŠÖ”
	Enemy();
	~Enemy();

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Enemy);
private:
	bool init()override;				// ‰Šú‰»@½Ìß×²Äì¬
	void update(float delta)override;	// ÌßÚ²Ô°‚ÌˆÚ“®‚Æ±ÆÒ°¼®İˆ—

	DIR GetDIR();

	std::array<cocos2d::Vec2, static_cast<int>(DIR::MAX)> _speedTbl;
};

