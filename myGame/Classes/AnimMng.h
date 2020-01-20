#pragma once
#include <cocos2d.h>
#include <input/OPRT_state.h>
#include <memory>

#define lpAnimMng AnimMng::GetInstance()

enum class Tag
{
	ANIM,		// ��Ұ���
	ACT,		// �����(1�ڰі��ɓ���������)
	TRG_ACT		// �����(���̎���������������)
};

class AnimMng
{
public:
	static AnimMng & GetInstance(void)
	{
		return *s_Instance;
	}	
	~AnimMng();

	// ��Ұ��݂̍쐬(����:: �N��, key�̖��O, �摜�̖���, ��Ұ��݂̎���)
	bool AnimCreate(const std::string type, const std::string key, int num, float time); 
	void runAnim(cocos2d::Sprite& sp, cocos2d::Animation& anim, int repeatNum = 0);
private:
	AnimMng();

	cocos2d::Animation* _anim;
	cocos2d::Animation* _oldAnim;

	static std::unique_ptr<AnimMng> s_Instance;
};

