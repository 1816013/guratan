#include"Obj.h"
#include <array>
#include "input/OPRT_state.h"

class Enemy : public Obj
{
public:
	static cocos2d::Sprite* createSprite();

	// �֐�
	Enemy();
	~Enemy();

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Enemy);
private:
	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;	// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���

	DIR GetDIR();

	std::array<cocos2d::Vec2, static_cast<int>(DIR::MAX)> _speedTbl;
};

