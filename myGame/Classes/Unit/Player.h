#pragma once
#include"Obj.h"
#include <array>

class Player : public Obj
{
public:
	// �֐�
	static cocos2d::Sprite* createSprite();

	Player();
	~Player();

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;	// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���

	DIR GetDIR();

	// �ϐ�
	cocos2d::DrawNode* line;
	bool changeF;
};

