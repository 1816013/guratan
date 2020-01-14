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

	DIR GetDIR();
	void SetDIR(DIR dir);
	int GetHP();
	void SetHP(int hp);
	int GetPower();
	float GetMovePower();
	void SetAbility(Ability ability);
	std::vector<Ability> GetAbilityList();
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
	bool changeF;
	int _exp;
	int _expMax;
	int _level;

	float _movePower;	// �ړ����x�A�r���e�B�␳�p

	std::vector<Ability>_abilityList;
};

