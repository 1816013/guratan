#pragma once

#include"Obj.h"
enum class Ability
{
	PowerUp,
	SpeedUp,
	RangeAttack,
	MAX
};


class Player : public Obj
{
public:
	// �֐�
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	void addExp(const int exp);
	float GetMovePower();
	void SetAbility(Ability& ability);
	void SetStrong(bool flag);
	bool IsCharged();
	bool GetStrong();
	std::vector<Ability> GetUnacquiredAbility();

	bool ColisionObj(Obj& hitObj, cocos2d::Scene& scene)override;

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;	// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���
	void LevelUp(void);

	// �ϐ�
	cocos2d::DrawNode* line;
	int _expMax;	// ����ȏ�ɂȂ�ƃ��x���A�b�v
	int _level;		// ���x��
	float _charge;	// �`���[�W���Ă��鎞��

	bool _strongF;	// ���G
	float _strongCnt;	// ���G���Զ���

	float _powerRate;	// �U���̓A�r���e�B�p
	float _movePower;	// �ړ����x�A�r���e�B�␳�p
	
	std::vector<Ability>_ability;		// �擾���Ă���A�r���e�B
	std::vector<Ability>_unacquiredAbility;	// ���擾�A�r���e�B
};

