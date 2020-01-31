#pragma once
#include"Obj.h"

enum class Ability
{
	PowerUp,
	SpeedUp,
	Heal,
	ChargeLevel,
	ChargeSpeed,
	MAX
};

enum class ChargeType
{
	SHOT,
	TWISTER,
	FLONTAL,
	MAX
};

using AbilityPair = std::pair<std::string, Ability>;	//���O, �A�r���e�B���

class Player : public Obj
{
public:
	// �֐�
	static cocos2d::Sprite* createPlayer();

	Player();
	~Player();

	void addExp(const int exp);
	float GetMovePower();
	float GetPowerRate();
	void SetAbility(AbilityPair ability);
	void SetStrong(bool flag);
	bool IsCharged();
	bool GetStrong();
	void SetChargeType(ChargeType chargeType);
	ChargeType GetChargeType();
	std::vector<AbilityPair> GetUnacquiredAbility();

	bool ColisionObj(Obj& hitObj, cocos2d::Scene& scene)override;

	std::unique_ptr<OPRT_state>_inputState;

	CREATE_FUNC(Player);
private:
	bool init()override;				// �������@���ײč쐬
	void update(float delta)override;	// ��ڲ԰�̈ړ��Ʊ�Ұ��ݏ���
	void LevelUp(void);
	cocos2d::Animation* SetAnim(DIR dir);	// �����ɉ�������Ұ��݂̐ݒ�

	// �ϐ�
	cocos2d::DrawNode* line;
	int _hpMax;
	int _expMax;			// ����ȏ�ɂȂ�ƃ��x���A�b�v
	int _level;				// ���x��
	float _charge;			// �`���[�W���Ă��鎞��
	float _chargeMax;		// �`���[�W�����܂鎞��
	int _chargeLevel;		// �`���[�W�̋���
	int _chargeLevelMax;	// �`���[�W�̍ő勭��
	bool _strongF;			// ���G
	float _strongCnt;		// ���G���Զ���

	float _powerRate;		// �U���̓A�r���e�B�p
	float _movePower;		// �ړ����x�A�r���e�B�␳�p

	ChargeType _chargeType;

	cocos2d::Sprite* texSprite;
	cocos2d::Animation* _oldAnim;
	
	std::vector<AbilityPair>_ability;		// �擾���Ă���A�r���e�B
	std::vector<AbilityPair>_unacquiredAbility;	// ���擾�A�r���e�B
};

