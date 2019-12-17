#include "CricketJni.h"
#include <ck/ck.h>
#include <ck/config.h>

#if CK_PLATFORM_ANDROID
#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_initCricket(JNIEnv * env, jclass activity, jobject context)
	{
		CkConfig config(env, context);
		CkInit(&config);
	}
#ifdef __cplusplus
}
#endif
#endif 
