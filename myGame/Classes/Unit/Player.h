#pragma once
#include"Obj.h"
#include <array>

class Player : public Obj
{
public:
	// �֐�
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	int GetHP();
	void SetHP(int hp);

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;	// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���

	DIR GetDIR();
	void SetDIR(DIR dir);

	// �ϐ�
	cocos2d::DrawNode* line;
	bool changeF;
};

