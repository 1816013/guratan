#pragma once
#include "cocos2d.h"
enum class BarType
{
	HP,
	EXP,
	MAX
};


class Bar : public cocos2d::Sprite
{
	// �Q�[�W�̘g
	cocos2d::Sprite* _frame;

	// �e�F�o�[�ƌ��ݕ\�����̃o�[
	cocos2d::Sprite* _blue;
	cocos2d::Sprite* _green;
	cocos2d::Sprite* _red;
	cocos2d::Sprite* _currentbar;
	// ����
	cocos2d::Label* _number;

	unsigned int _max;
	unsigned int _current;
	BarType _barType;

public:
	static cocos2d::Sprite* createHpBar(const unsigned int max, BarType barType, cocos2d::Size size);
	Bar();
	~Bar();
	bool initValue(const unsigned int max, BarType barType, cocos2d::Size size);
	// �o�[�̗ʂ�ύX����
	void changeValue(const unsigned int value);
	// �V�����ő�l�ƒl��ݒ肵�ĕ\�����X�V����
	void changeMax(const unsigned int max, const unsigned int value);
	
	unsigned int getNowMax();
	CREATE_FUNC(Bar);

private:

	// �o�[�̃��[�h
	cocos2d::Sprite* loadSprite(const std::string& name);
	// �w�肵���l�ɑΉ�����o�[��Sprite���擾����
	cocos2d::Sprite* getSprite(const unsigned int value);
	void ChangeNumber(unsigned int max, unsigned int value = 0 );
};

