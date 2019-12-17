#pragma once
#include <jni.h>
#ifndef __ANDROID_JNI__
#define __ANDROID_JNI__
#ifdef __cplusplus
extern "C" {
#endif

	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_initCricket(
		JNIEnv * env,
		jclass activity,
		jobject context
	);

#ifdef __cplusplus
}
#endif
#endif
