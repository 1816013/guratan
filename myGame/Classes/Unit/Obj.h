#pragma once
#include "cocos2d.h"
#include <input/OPRT_state.h>
#include <action/ActionMng.h>


class Obj : public cocos2d::Sprite
{
public:
	Obj();
	virtual ~Obj();

	virtual DIR GetDIR() = 0;

protected:
	// �ϐ�
	cocos2d::Vec2 _pos;				// ���W	
	cocos2d::Size _size;				//�傫��
	DIR _dir;

	std::shared_ptr<ActionMng>_actMng;
};

