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
	// DxLibﾗｯﾌﾟ用関数※DxLibのﾘﾌｧﾚﾝｽからとっているのでわからなかったらそれを見ること

	// ｽｸﾘｰﾝ設定
private:
	struct _DebugDispOutDeleter		// ﾃﾞﾘｰﾀｰ
	{
		void operator()(_DebugDispOut* _debugContOut) const
		{
			delete _debugContOut;
		}
	};
	_DebugDispOut();
	~_DebugDispOut();

	static std::unique_ptr<_DebugDispOut, _DebugDispOutDeleter> s_Instance;

	// ﾃﾞﾊﾞｯｸﾞｽｸﾘｰﾝ

};
#else
// Releseのときは空読みする
//#define _dbgDrawFormatString(fmt, ...)
#define _dbgDrawFormatString(fmt, ...)
#endif	// _DEBUG

