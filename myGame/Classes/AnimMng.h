#pragma once
#include <cocos2d.h>
#include <input/OPRT_state.h>
#include <memory>

#define lpAnimMng AnimMng::GetInstance()

enum class Tag
{
	ANIM,		// ±ÆÒ°¼®İ
	ACT,		// ±¸¼®İ(1ÌÚ°Ñ–ˆ‚É“®‚©‚·‚à‚Ì)
	TRG_ACT		// ±¸¼®İ(‚»‚Ì‚¾‚¯“®‚©‚·‚à‚Ì)
};

class AnimMng
{
public:
	static AnimMng & GetInstance(void)
	{
		return *s_Instance;
	}	
	~AnimMng();

	// ±ÆÒ°¼®İ‚Ìì¬(ˆø”:: ’N‚ª, key‚Ì–¼‘O, ‰æ‘œ‚Ì–‡”, ±ÆÒ°¼®İ‚ÌŠÔ)
	bool AnimCreate(const std::string type, const std::string key, int num, float time); 
	void runAnim(cocos2d::Sprite& sp, cocos2d::Animation& anim, int repeatNum = 0);
private:
	AnimMng();

	cocos2d::Animation* _anim;
	cocos2d::Animation* _oldAnim;

	static std::unique_ptr<AnimMng> s_Instance;
};

