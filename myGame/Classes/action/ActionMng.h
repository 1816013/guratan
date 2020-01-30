#pragma once
#include <cocos2d.h>
#include <map>
#include <functional>
#include <input/OPRT_state.h>
//#pragma execution_character_set("utf-8")
enum class ACT_STATE
{
	RUN,
	IDLE,
	ATACK,
	SHOT
};

struct actModule;
using funcActModule = std::function<bool(cocos2d::Sprite&, actModule&)>;

struct actModule
{
	ACT_STATE actID;							// �����ID
	std::list<ACT_STATE>white;					// �ܲ�ؽ�
	std::list<ACT_STATE>black;					// ��ׯ�ؽ�
	std::list<funcActModule>act;				// �����n�̱����
	funcActModule runAction;					// ���s���鱸���	
	cocos2d::Vec2 speed;						// �ړ����x
	std::array<cocos2d::Size, 2> colSize;		// �����蔻��̻���
	Timing keyTiming;							// �������ݸ�
	INPUT_ID inputID;							// ���̎��
	DIR dir;									// �����ύX�p
};

class ActionMng
{
public:
	ActionMng();
	//ActionMng(cocos2d::Sprite& sp);
	~ActionMng();
	void AddActModule(const std::string& actName, actModule& module);	// ����݂̾��
	void update(cocos2d::Sprite& sp);

	std::map<std::string, actModule>_moduleMap;

	// �ϐ�
	ACT_STATE nowAct;	// ���݂̱����
};

