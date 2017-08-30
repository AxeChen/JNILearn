#include "stdafx.h"
#include "JNIHelloWord.h"
#include <string.h>

JNIEXPORT jstring JNICALL Java_JNIHelloWord_getStringFromC
(JNIEnv * env, jclass jclass) {
	return (*env)->NewStringUTF(env,"hello word");
}

JNIEXPORT jstring JNICALL Java_JNIHelloWord_accessField
(JNIEnv * env, jobject jobj) {
	// 获取 jclass
	jclass jclz = (*env)->GetObjectClass(env,jobj);

	// 得到 fieldId
	jfieldID fid = (*env)->GetFieldID(env,jclz, "key", "Ljava/lang/String;");

	// 把key -》 hard work
	jstring jstr = (*env)->GetObjectField(env,jobj,fid);

	// 获取到 jni的值之后 转为c语言的字符
	char *str = (*env)->GetStringUTFChars(env,jstr,NULL);

	/// 做一些修改 (生成新的字符串)
	char text[30] = "ha sa gei";
	strcat(text,str);

	// 先将 c 语言转换成 jni
	jstring *new_str = (*env)->NewStringUTF(env, text);

	// 设置
	(*env)->SetObjectField(env, jobj, fid, new_str);

	// 释放资源
	(*env)->ReleaseStringChars(env, new_str, str);

	return new_str;

}

JNIEXPORT void JNICALL Java_JNIHelloWord_plusField
(JNIEnv *env, jobject jobj) {
	// 获取 jclass
	jclass jclz = (*env)->GetObjectClass(env, jobj);

	// 得到 fieldId
	jfieldID fid = (*env)->GetStaticFieldID(env, jclz, "count", "I");

	// 修改 。 如果时一般数据类型，不需要通过c来改
	jint count = (*env)->GetStaticIntField(env, jclz, fid);
	count++;

	(*env)->SetStaticIntField(env, jobj, fid, count);
}

JNIEXPORT jstring JNICALL Java_JNIHelloWord_getStringFrom2C
(JNIEnv * env, jobject jobj) {
	return (*env)->NewStringUTF(env,"not static haha");
}