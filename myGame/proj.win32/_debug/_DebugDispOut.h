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
	// DxLib×¯Ìß—pŠÖ”¦DxLib‚ÌØÌ§Úİ½‚©‚ç‚Æ‚Á‚Ä‚¢‚é‚Ì‚Å‚í‚©‚ç‚È‚©‚Á‚½‚ç‚»‚ê‚ğŒ©‚é‚±‚Æ

	// ½¸Ø°İİ’è
private:
	struct _DebugDispOutDeleter		// ÃŞØ°À°
	{
		void operator()(_DebugDispOut* _debugContOut) const
		{
			delete _debugContOut;
		}
	};
	_DebugDispOut();
	~_DebugDispOut();

	static std::unique_ptr<_DebugDispOut, _DebugDispOutDeleter> s_Instance;

	// ÃŞÊŞ¯¸Ş½¸Ø°İ

};
#else
// Relese‚Ì‚Æ‚«‚Í‹ó“Ç‚İ‚·‚é
//#define _dbgDrawFormatString(fmt, ...)
#define _dbgDrawFormatString(fmt, ...)
#endif	// _DEBUG

