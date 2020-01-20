#include "AnimMng.h"

USING_NS_CC;

std::unique_ptr<AnimMng>AnimMng::s_Instance(new AnimMng);

AnimMng::AnimMng()
{
}

AnimMng::~AnimMng()
{

}

// ±ÆÒ°¼®Ý‚Ìì¬
bool AnimMng::AnimCreate(const std::string type, const std::string key, int num, float time)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/"+ type + "/" + type + "-" + key + ".plist");
	auto animation = Animation::create();
	
	for (int i = 1; i <= 20; i++)
	{
		__String* str;
		if (num == 1)
		{
			str = __String::createWithFormat((type + "-" + key + ".png").c_str(), i);
		}
		else
		{
			str = __String::createWithFormat((type + "-" + key + "-%i.png").c_str(), i);
		}
		SpriteFrame *sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		if (sprite == nullptr)
		{
			break;
		}
		animation->addSpriteFrame(sprite);
	}
	animation->setDelayPerUnit(time); // ±ÆÒ°¼®Ý‚ÌŠúŠÔ
	animation->setRestoreOriginalFrame(true);	// ±ÆÒ°¼®ÝI—¹Žž‚É‰‚ß‚É–ß‚é‚©

	AnimationCache::getInstance()->addAnimation(animation, key);
	return true;
}

void AnimMng::runAnim(Sprite& sp, Animation& anim, int repeatNum)
{
	if (&anim == nullptr)
	{
		return;
	}
	Action* animAct;
	if (repeatNum <= 0)
	{
		animAct = RepeatForever::create(Animate::create(&anim));
	}
	else
	{
		animAct = Repeat::create(Animate::create(&anim), repeatNum);
	}
	if (_oldAnim != &anim)
	{
		sp.stopAllActions();
		sp.runAction(animAct);
		_oldAnim = &anim;
	}
}
