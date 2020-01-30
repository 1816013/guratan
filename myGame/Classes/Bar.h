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
	// ゲージの枠
	cocos2d::Sprite* _frame;

	// 各色バーと現在表示中のバー
	cocos2d::Sprite* _blue;
	cocos2d::Sprite* _green;
	cocos2d::Sprite* _red;
	cocos2d::Sprite* _currentbar;
	// 数字
	cocos2d::Label* _number;

	unsigned int _max;
	unsigned int _current;
	BarType _barType;

public:
	static cocos2d::Sprite* createHpBar(const unsigned int max, BarType barType, cocos2d::Size size);
	Bar();
	~Bar();
	bool initValue(const unsigned int max, BarType barType, cocos2d::Size size);
	// バーの量を変更する
	void changeValue(const unsigned int value);
	// 新しい最大値と値を設定して表示を更新する
	void changeMax(const unsigned int max, const unsigned int value);
	
	unsigned int getNowMax();
	CREATE_FUNC(Bar);

private:

	// バーのロード
	cocos2d::Sprite* loadSprite(const std::string& name);
	// 指定した値に対応するバーのSpriteを取得する
	cocos2d::Sprite* getSprite(const unsigned int value);
	void ChangeNumber(unsigned int max, unsigned int value = 0 );
};

