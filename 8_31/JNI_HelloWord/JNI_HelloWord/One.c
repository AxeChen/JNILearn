#include "stdafx.h"
#include "JNIHelloWord.h"
#include <string.h>

JNIEXPORT jstring JNICALL Java_JNIHelloWord_getStringFromC
(JNIEnv * env, jclass jclass) {
	return (*env)->NewStringUTF(env,"hello word");
}

JNIEXPORT jstring JNICALL Java_JNIHelloWord_accessField
(JNIEnv * env, jobject jobj) {
	// ��ȡ jclass
	jclass jclz = (*env)->GetObjectClass(env,jobj);

	// �õ� fieldId
	jfieldID fid = (*env)->GetFieldID(env,jclz, "key", "Ljava/lang/String;");

	// ��key -�� hard work
	jstring jstr = (*env)->GetObjectField(env,jobj,fid);

	// ��ȡ�� jni��ֵ֮�� תΪc���Ե��ַ�
	char *str = (*env)->GetStringUTFChars(env,jstr,NULL);

	/// ��һЩ�޸� (�����µ��ַ���)
	char text[30] = "ha sa gei";
	strcat(text,str);

	// �Ƚ� c ����ת���� jni
	jstring *new_str = (*env)->NewStringUTF(env, text);

	// ����
	(*env)->SetObjectField(env, jobj, fid, new_str);

	// �ͷ���Դ
	(*env)->ReleaseStringChars(env, new_str, str);

	return new_str;

}

JNIEXPORT void JNICALL Java_JNIHelloWord_plusField
(JNIEnv *env, jobject jobj) {
	// ��ȡ jclass
	jclass jclz = (*env)->GetObjectClass(env, jobj);

	// �õ� fieldId
	jfieldID fid = (*env)->GetStaticFieldID(env, jclz, "count", "I");

	// �޸� �� ���ʱһ���������ͣ�����Ҫͨ��c����
	jint count = (*env)->GetStaticIntField(env, jclz, fid);
	count++;

	(*env)->SetStaticIntField(env, jobj, fid, count);
}

JNIEXPORT jstring JNICALL Java_JNIHelloWord_getStringFrom2C
(JNIEnv * env, jobject jobj) {
	return (*env)->NewStringUTF(env,"not static haha");
}