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
	void attack(float delta, cocos2d::Scene& scene);
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
	

	float _powerRate;		// �U���̓A�r���e�B�p
	float _movePower;		// �ړ����x�A�r���e�B�␳�p

	ChargeType _chargeType;

	cocos2d::Sprite* texSprite;		// �`��p�X�v���C�g���摜���傫��boundingbox�ł̓����蔻�肪�ł��Ȃ����ߕK�v	
	cocos2d::Animation* _oldAnim;

	// �e�L�X�g
	cocos2d::Label* lvText;
	cocos2d::Label* chargeText;
	
	std::vector<AbilityPair>_ability;		// �擾���Ă���A�r���e�B
	std::vector<AbilityPair>_unacquiredAbility;	// ���擾�A�r���e�B
};

