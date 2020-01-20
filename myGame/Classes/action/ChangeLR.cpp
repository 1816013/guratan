#include "ChangeLR.h"
#include <Unit/Player.h>

bool ChangeDIR::operator()(cocos2d::Sprite & sp, actModule & module)
{
	auto checkinput = [](INPUT_ID input, cocos2d::Sprite& sp)
	{
		for (auto inputID : INPUT_ID())
		{
			if (((Player&)sp)._inputState->GetInput(TRG_STATE::NOW, inputID) == true)
			{
				if (input != inputID && inputID != INPUT_ID::ATTACK)
				{
					return false;
				}
			}
		}
		return true;
	};
	if (!((Player&)sp).IsCharged())
	{
		DIR dir = ((Obj&)sp).GetDIR();
		if (checkinput(module.inputID, sp))
		{
			dir = module.dir;
			((Obj&)sp).SetDIR(dir);
		}
		//// ���ޯ�ޗp�@@�L�����G���o�����炢��Ȃ��Ȃ�
		//if (dir == DIR::UP)
		//{
		//	sp.setRotation(0.0f);
		//}
		//if (dir == DIR::RIGHT)
		//{
		//	sp.setRotation(90.0f);
		//}
		//if (dir == DIR::DOWN)
		//{
		//	sp.setRotation(180.0f);
		//}
		//if (dir == DIR::LEFT)
		//{
		//	sp.setRotation(270.0f);
		//}
	}

	return true;
}
