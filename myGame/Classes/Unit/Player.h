#pragma once
#include"Obj.h"

enum class Ability
{
	PowerUp,
	SpeedUp,
	RangeAttack,
	MAX
};

enum class ChargeType
{

};


class Player : public Obj
{
public:
	// �֐�
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	DIR GetDIR()override;
	void SetDIR(DIR dir)override;
	int GetHP()override;
	void SetHP(const int hp)override;
	int GetPower()override;

	void addExp(const int exp);
	bool GetRangeFlag();
	float GetMovePower();
	void SetAbility(Ability& ability);
	std::vector<Ability> GetUnacquiredAbility();
	bool FindAbility(Ability ability);

	bool ColisionObj(Obj* hitObj, cocos2d::Layer* layer);

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;	// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���
	void LevelUp(void);

	// �ϐ�
	cocos2d::DrawNode* line;
	bool _rangeF;	// �������U���׸ށ�����Ȃ�����
	int _expMax;	// ����ȏ�ɂȂ�ƃ��x���A�b�v
	int _level;		// ���x��

	float _movePower;	// �ړ����x�A�r���e�B�␳�p
	float _charge;

	std::vector<Ability>_ability;		// �擾���Ă���A�r���e�B
	std::vector<Ability>_unacquiredAbility;	// ���擾�A�r���e�B
};

