#include "stdafx.h"
#include "demo_JNIDemo.h"
#include <Windows.h>
#include <string.h>

/// 调用java的非静态方法
JNIEXPORT void JNICALL Java_demo_JNIDemo_accessMedthod
(JNIEnv *env, jobject jobj) {

	// 1、先获取jclass
	jclass jclz = (*env)->GetObjectClass(env, jobj);

	// 2、获取jmethodId
	jmethodID mid = (*env)->GetMethodID(env, jclz, "getInt", "()I");

	// 3、调用该方法
	jint value = (*env)->CallIntMethod(env, jobj, mid);

	printf("获得的值：%d\n",value);

	/////////////// 调用 getString 方法
	jmethodID mid2 = (*env)->GetMethodID(env,jclz,"getString","()Ljava/lang/String;");

	jstring str = (*env)->CallObjectMethod(env,jobj,mid2);

	printf("获取到的值 %s\n",str);


	/////////////// 调用 getTwo 方法
	jmethodID mid3 = (*env)->GetMethodID(env,jclz,"getIntTwo","(I)I");

	jint value2 = (*env)->CallIntMethod(env,jobj,mid3,1555);
	printf("获得的值：%d\n", value2);
}

//////  调用java的静态方法
JNIEXPORT void JNICALL Java_demo_JNIDemo_accessStaticMethod
(JNIEnv *env, jobject jobj) {
	// 1、先获取jclass
	jclass jclz = (*env)->GetObjectClass(env, jobj);

	// 2、获取静态方法id
	jmethodID mid = (*env)->GetStaticMethodID(env,jclz,"getStaticString","()Ljava/lang/String;");

	jstring str = (*env)->CallStaticObjectMethod(env,jclz,mid);

	printf("获取到的值 %s\n", str);

	/// jstring - char *
	char *getStr = (*env)->GetStringUTFChars(env,str,NULL);

	// 生成一个文件
	char fileName[100];
	sprintf(fileName,"D://%s.txt",getStr);
	FILE *fp = fopen(fileName,"w");
	fputs("yes yes yes",fp);

	// 访问  getStaticInt
	jmethodID mid2 = (*env)->GetStaticMethodID(env,jclz,"getStaticInt","(I)I");

	// 叼方法
	jint getInt = (*env)->CallStaticIntMethod(env,jclz,mid2,133);
	printf("获得的值：%d\n", getInt);

}

/// 访问构造函数
JNIEXPORT void JNICALL Java_demo_JNIDemo_accessConstructMenthod
(JNIEnv *env, jobject jobj) {

	// 获取系统的类
	jclass jclz = (*env)->FindClass(env,"java/util/Date");

	// jmethodid
	jmethodID jmid = (*env)->GetMethodID(env, jclz, "<init>", "()V");

	// newObject
	jobject dateObj = (*env)->NewObject(env,jclz,jmid);

	jmethodID timeid = (*env)->GetMethodID(env,jclz,"getTime","()J");
	jlong time = (*env)->CallLongMethod(env, dateObj, timeid);

	printf("获得的值：%lld\n", time);


	// 获取系统的类
	jclass jclz2 = (*env)->FindClass(env, "demo/People");
	if (jclz2 == NULL) {
		printf("jclz2,为空");
	}

	// jmethodid
	jmethodID jmid2 = (*env)->GetMethodID(env, jclz2, "<init>", "()V");

	// newObject
	jobject people = (*env)->NewObject(env, jclz2, jmid2);
	jmethodID intmid = (*env)->GetMethodID(env, jclz2, "getAge", "()I");
	jint age = (*env)->CallIntMethod(env, people, intmid);
	printf("获得的值：%ld\n", age);

}

/// 字符串格式问题
JNIEXPORT void JNICALL Java_demo_JNIDemo_accessString
(JNIEnv *env, jobject jobj,jstring inStr) {

	// 第一种方式，先转jchar再转char *
	printf("格式（jstring）获取到的值 %s\n", inStr);

	int length = (*env)->GetStringLength(env,inStr);

	//  把jsString转化为jchar
	const jchar *jchar = (*env)->GetStringChars(env, inStr, NULL);

	if (jchar == NULL) {
		return;
	}
	// 把jchar转为char (先将char分配内存)
	char *cchar = (char *)malloc(sizeof(char)*2*length + 1);
	// 初始化
	memset(cchar,0, sizeof(char) * 2 *length + 1);
	int size = 0;
	size = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)jchar, length, cchar, sizeof(char) * 2 *  length+1 , NULL, NULL);
	if (size<=0) {
		return;
	}
	printf("格式（char *）获取到的值 %s\n", cchar);

	if (cchar != NULL) {
		free(cchar);
		cchar = NULL;
	}
	(*env)->ReleaseStringChars(env, inStr, cchar);
	// 直接调用java中String的方法

	char *c_str = "测试代码";
	jclass str_cls = (*env)->FindClass(env, "java/lang/String");
	jmethodID jmid = (*env)->GetMethodID(env, str_cls, "<init>", "([BLjava/lang/String;)V");
	
	//jstring -> jbyteArray
	jbyteArray bytes = (*env)->NewByteArray(env, strlen(c_str));
	// 将Char * 赋值到 bytes
	(*env)->SetByteArrayRegion(env, bytes, 0, strlen(c_str), c_str);
	jstring charsetName = (*env)->NewStringUTF(env, "GB2312");

	return (*env)->NewObject(env, str_cls, jmid, bytes, charsetName);

}

// 调用java中String的构造函数来返回个String
JNIEXPORT jobject JNICALL Java_demo_JNIDemo_getStringFromJNI
(JNIEnv *env, jobject jobj, jstring inStr) {
	char *c_str = "陈再峰你就是个大傻逼";
	// 获取jclz
	jclass jclz = (*env)->FindClass(env, "java/lang/String");

	// 获取构造函数的methodID
	jmethodID jmid = (*env)->GetMethodID(env,jclz,"<init>", "([BLjava/lang/String;)V");

	// jstring -> jbyteArray (声明一个jbytearray对象)
	jbyteArray bytes = (*env)->NewByteArray(env, strlen(c_str));

	// 将 char转化为jbytearray
	(*env)->SetByteArrayRegion(env, bytes, 0, strlen(c_str), c_str);

	//声明一个jstring对象
	jstring charsetName = (*env)->NewStringUTF(env, "GB2312");

	// 调用String 构造函数，返回一个String
	return (*env)->NewObject(env, jclz, jmid, bytes, charsetName);

}