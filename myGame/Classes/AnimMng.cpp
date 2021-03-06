#include "AnimMng.h"

USING_NS_CC;

std::unique_ptr<AnimMng>AnimMng::s_Instance(new AnimMng);

AnimMng::AnimMng()
{
}

AnimMng::~AnimMng()
{

}

// ｱﾆﾒｰｼｮﾝの作成
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
	animation->setDelayPerUnit(time); // ｱﾆﾒｰｼｮﾝの期間
	animation->setRestoreOriginalFrame(true);	// ｱﾆﾒｰｼｮﾝ終了時に初めに戻るか

	AnimationCache::getInstance()->addAnimation(animation,type +"-"+ key);
	return true;
}

void AnimMng::runAnim(Sprite& sp, cocos2d::Animation& anim, cocos2d::Animation& oldAnim, int repeatNum)
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
	if (&oldAnim != &anim)
	{
		sp.stopAllActions();
		sp.runAction(animAct);
	}
}
