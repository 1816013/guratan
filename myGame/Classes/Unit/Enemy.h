#include"Obj.h"
#include <array>
#include "input/OPRT_state.h"

class Enemy : public Obj
{
public:
	static cocos2d::Sprite* createSprite();

	// 関数
	Enemy();
	~Enemy();

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Enemy);
private:
	bool init()override;				// 初期化　ｽﾌﾟﾗｲﾄ作成
	void update(float delta)override;	// ﾌﾟﾚｲﾔｰの移動とｱﾆﾒｰｼｮﾝ処理

	DIR GetDIR();

	std::array<cocos2d::Vec2, static_cast<int>(DIR::MAX)> _speedTbl;
};

