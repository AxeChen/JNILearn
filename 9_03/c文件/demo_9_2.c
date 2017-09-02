#include "stdafx.h"
#include "demo_JNIDemo.h"
#include <Windows.h>
#include <string.h>

/// ����java�ķǾ�̬����
JNIEXPORT void JNICALL Java_demo_JNIDemo_accessMedthod
(JNIEnv *env, jobject jobj) {

	// 1���Ȼ�ȡjclass
	jclass jclz = (*env)->GetObjectClass(env, jobj);

	// 2����ȡjmethodId
	jmethodID mid = (*env)->GetMethodID(env, jclz, "getInt", "()I");

	// 3�����ø÷���
	jint value = (*env)->CallIntMethod(env, jobj, mid);

	printf("��õ�ֵ��%d\n",value);

	/////////////// ���� getString ����
	jmethodID mid2 = (*env)->GetMethodID(env,jclz,"getString","()Ljava/lang/String;");

	jstring str = (*env)->CallObjectMethod(env,jobj,mid2);

	printf("��ȡ����ֵ %s\n",str);


	/////////////// ���� getTwo ����
	jmethodID mid3 = (*env)->GetMethodID(env,jclz,"getIntTwo","(I)I");

	jint value2 = (*env)->CallIntMethod(env,jobj,mid3,1555);
	printf("��õ�ֵ��%d\n", value2);
}

//////  ����java�ľ�̬����
JNIEXPORT void JNICALL Java_demo_JNIDemo_accessStaticMethod
(JNIEnv *env, jobject jobj) {
	// 1���Ȼ�ȡjclass
	jclass jclz = (*env)->GetObjectClass(env, jobj);

	// 2����ȡ��̬����id
	jmethodID mid = (*env)->GetStaticMethodID(env,jclz,"getStaticString","()Ljava/lang/String;");

	jstring str = (*env)->CallStaticObjectMethod(env,jclz,mid);

	printf("��ȡ����ֵ %s\n", str);

	/// jstring - char *
	char *getStr = (*env)->GetStringUTFChars(env,str,NULL);

	// ����һ���ļ�
	char fileName[100];
	sprintf(fileName,"D://%s.txt",getStr);
	FILE *fp = fopen(fileName,"w");
	fputs("yes yes yes",fp);

	// ����  getStaticInt
	jmethodID mid2 = (*env)->GetStaticMethodID(env,jclz,"getStaticInt","(I)I");

	// �𷽷�
	jint getInt = (*env)->CallStaticIntMethod(env,jclz,mid2,133);
	printf("��õ�ֵ��%d\n", getInt);

}

/// ���ʹ��캯��
JNIEXPORT void JNICALL Java_demo_JNIDemo_accessConstructMenthod
(JNIEnv *env, jobject jobj) {

	// ��ȡϵͳ����
	jclass jclz = (*env)->FindClass(env,"java/util/Date");

	// jmethodid
	jmethodID jmid = (*env)->GetMethodID(env, jclz, "<init>", "()V");

	// newObject
	jobject dateObj = (*env)->NewObject(env,jclz,jmid);

	jmethodID timeid = (*env)->GetMethodID(env,jclz,"getTime","()J");
	jlong time = (*env)->CallLongMethod(env, dateObj, timeid);

	printf("��õ�ֵ��%lld\n", time);


	// ��ȡϵͳ����
	jclass jclz2 = (*env)->FindClass(env, "demo/People");
	if (jclz2 == NULL) {
		printf("jclz2,Ϊ��");
	}

	// jmethodid
	jmethodID jmid2 = (*env)->GetMethodID(env, jclz2, "<init>", "()V");

	// newObject
	jobject people = (*env)->NewObject(env, jclz2, jmid2);
	jmethodID intmid = (*env)->GetMethodID(env, jclz2, "getAge", "()I");
	jint age = (*env)->CallIntMethod(env, people, intmid);
	printf("��õ�ֵ��%ld\n", age);

}

/// �ַ�����ʽ����
JNIEXPORT void JNICALL Java_demo_JNIDemo_accessString
(JNIEnv *env, jobject jobj,jstring inStr) {

	// ��һ�ַ�ʽ����תjchar��תchar *
	printf("��ʽ��jstring����ȡ����ֵ %s\n", inStr);

	int length = (*env)->GetStringLength(env,inStr);

	//  ��jsStringת��Ϊjchar
	const jchar *jchar = (*env)->GetStringChars(env, inStr, NULL);

	if (jchar == NULL) {
		return;
	}
	// ��jcharתΪchar (�Ƚ�char�����ڴ�)
	char *cchar = (char *)malloc(sizeof(char)*2*length + 1);
	// ��ʼ��
	memset(cchar,0, sizeof(char) * 2 *length + 1);
	int size = 0;
	size = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)jchar, length, cchar, sizeof(char) * 2 *  length+1 , NULL, NULL);
	if (size<=0) {
		return;
	}
	printf("��ʽ��char *����ȡ����ֵ %s\n", cchar);

	if (cchar != NULL) {
		free(cchar);
		cchar = NULL;
	}
	(*env)->ReleaseStringChars(env, inStr, cchar);
	// ֱ�ӵ���java��String�ķ���

	char *c_str = "���Դ���";
	jclass str_cls = (*env)->FindClass(env, "java/lang/String");
	jmethodID jmid = (*env)->GetMethodID(env, str_cls, "<init>", "([BLjava/lang/String;)V");
	
	//jstring -> jbyteArray
	jbyteArray bytes = (*env)->NewByteArray(env, strlen(c_str));
	// ��Char * ��ֵ�� bytes
	(*env)->SetByteArrayRegion(env, bytes, 0, strlen(c_str), c_str);
	jstring charsetName = (*env)->NewStringUTF(env, "GB2312");

	return (*env)->NewObject(env, str_cls, jmid, bytes, charsetName);

}

// ����java��String�Ĺ��캯�������ظ�String
JNIEXPORT jobject JNICALL Java_demo_JNIDemo_getStringFromJNI
(JNIEnv *env, jobject jobj, jstring inStr) {
	char *c_str = "���ٷ�����Ǹ���ɵ��";
	// ��ȡjclz
	jclass jclz = (*env)->FindClass(env, "java/lang/String");

	// ��ȡ���캯����methodID
	jmethodID jmid = (*env)->GetMethodID(env,jclz,"<init>", "([BLjava/lang/String;)V");

	// jstring -> jbyteArray (����һ��jbytearray����)
	jbyteArray bytes = (*env)->NewByteArray(env, strlen(c_str));

	// �� charת��Ϊjbytearray
	(*env)->SetByteArrayRegion(env, bytes, 0, strlen(c_str), c_str);

	//����һ��jstring����
	jstring charsetName = (*env)->NewStringUTF(env, "GB2312");

	// ����String ���캯��������һ��String
	return (*env)->NewObject(env, jclz, jmid, bytes, charsetName);

}