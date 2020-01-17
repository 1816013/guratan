#pragma once
#ifdef _DEBUG
#include <cocos2d.h>
#include <memory>
#include <tuple>


class _DebugDispOut
{
public:
	static _DebugDispOut& GetInstance(void)
	{
		return (*s_Instance);
	}
	// DxLibׯ�ߗp�֐���DxLib���̧�ݽ����Ƃ��Ă���̂ł킩��Ȃ������炻������邱��

	// ��ذݐݒ�
private:
	struct _DebugDispOutDeleter		// ��ذ��
	{
		void operator()(_DebugDispOut* _debugContOut) const
		{
			delete _debugContOut;
		}
	};
	_DebugDispOut();
	~_DebugDispOut();

	static std::unique_ptr<_DebugDispOut, _DebugDispOutDeleter> s_Instance;

	// ���ޯ�޽�ذ�

};
#else
// Relese�̂Ƃ��͋�ǂ݂���
//#define _dbgDrawFormatString(fmt, ...)
#define _dbgDrawFormatString(fmt, ...)
#endif	// _DEBUG

