#ifdef _DEBUG
#include "_DebugDispOut.h"



std::unique_ptr<_DebugDispOut, _DebugDispOut::_DebugDispOutDeleter> _DebugDispOut::s_Instance(new _DebugDispOut);

_DebugDispOut::_DebugDispOut()
{

}

_DebugDispOut::~_DebugDispOut()
{
}

#endif	// _DEBUG


