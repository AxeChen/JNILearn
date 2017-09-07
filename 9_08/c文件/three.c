#include "stdafx.h"
#include "JNIHelloWord.h"
#include <string.h>

// ��������
int compare(jint * a, jint *b);

// ���ʻ���������������
JNIEXPORT void JNICALL Java_demo_JNIMain_getArray
(JNIEnv * env, jobject jobj,jintArray arr) {

	//1��jintArray  -> jint *
	jint *elemts = (*env)->GetIntArrayElements(env,arr,NULL);
	if (elemts == NULL) {
		return;
	}
	// ���鳤��
	int len = (*env)->GetArrayLength(env,arr);
	// ����
	qsort(elemts,len,sizeof(int),compare);

	(*env)->ReleaseIntArrayElements(env,arr,elemts,JNI_COMMIT);
}

// ����
int compare(jint * a, jint *b) {
	return *a - *b;
}

// ����������������
JNIEXPORT jobjectArray JNICALL Java_demo_JNIMain_getStringArray
(JNIEnv * env, jobject jobj, jint size) {
	
	//jobjectArray
	jclass jclz = (*env)->FindClass(env, "java/lang/String");
	if (jclz == NULL) {
		return NULL;
	}
	// �����µ�����
	jobjectArray jobjArray = (*env)->NewObjectArray(env,size,jclz, jobj);
	if (jobjArray == NULL) {
		return NULL;
	}
	// ��ֵ
	for (int i = 0;i<size;i++) {
		char *c_str = (char *)malloc(256);
		memset(c_str,0,256);
		// ��string����������
		sprintf(c_str,"hello num:%d\n",i);
		// c -> jstring
		jstring str = (*env)->NewStringUTF(env, c_str);
		if (str == NULL) {
			return NULL;
		}
		//��jstring��ֵ������
		(*env)->SetObjectArrayElement(env, jobjArray, i, str);
		free(c_str);
		c_str = NULL;
		(*env)->DeleteGlobalRef(env,str);
	}

	return jobjArray;
}

// ����һ���������͵�����
JNIEXPORT jobjectArray JNICALL Java_demo_JNIMain_getPeopleArray
(JNIEnv * env, jobject jobj, jint size) {

	// ��ȡҪ���������class
	jclass jclz = (*env)->FindClass(env, "demo/PeopleBean");
	if (jclz == NULL) {
		return NULL;
	}
	// ��������
	jobjectArray jobjArray = (*env)->NewObjectArray(env, size, jclz, jobj);
	if (jobjArray == NULL) {
		return NULL;
	}

	// jmethodid �ȳ�ʼ������
	jmethodID init = (*env)->GetMethodID(env, jclz, "<init>", "()V");
	// newObject
	jobject people = (*env)->NewObject(env, jclz, init);
	if (people == NULL) return;
	// ��ȡsetName����ID
	jmethodID setName = (*env)->GetMethodID(env, jclz, "setName", "(Ljava/lang/String;)V");
	if (setName == NULL) return;
	//char *c_str = (char *)malloc(256);
	//memset(c_str, 0, 256);
	//// ��string����������
	//sprintf(c_str, "hello num:%d\n");
	(*env)->CallObjectMethod(env, people, setName,"11111");

	//��people��ֵ������
	//(*env)->SetObjectArrayElement(env, jobjArray, 0, people);

	//free(c_str);
	//c_str = NULL;
	//(*env)->DeleteGlobalRef(env, c_str);

	return jobjArray;
}

//JNIץ���쳣����
// ԭ���ǣ�jni�������쳣�޷���java�������������Ҫ�õ�jthrowable
JNIEXPORT void JNICALL Java_demo_JNIMain_cannotCatchException
(JNIEnv * env, jobject jobj) {
	jclass jclz = (*env)->FindClass(env, "java/lang/String;");
	jfieldID fid = (*env)->GetFieldID(env, jclz, "key", "LJava/lang/String;");
	/*
	Java����ʱ�������쳣��
	at demo.JNIMain.catchException(Native Method)
	at demo.JNIMain.main(JNIMain.java:37)
	*/

	// ����Ƿ����쳣�ķ���
	jthrowable ex = (*env)->ExceptionOccurred(env);
	// �������쳣
	if (ex!=NULL) {
		// 1�� ����쳣
		(*env)->ExceptionClear(env);
	}
}


JNIEXPORT void JNICALL Java_demo_JNIMain_canCatchException
(JNIEnv * env, jobject jobj) {
	jclass jclz = (*env)->FindClass(env, "java/lang/String");
	jfieldID fid = (*env)->GetFieldID(env, jclz, "key", "LJava/lang/String;");
	/*
	Java����ʱ�������쳣��
	at demo.JNIMain.catchException(Native Method)
	at demo.JNIMain.main(JNIMain.java:37)
	*/

	// ����Ƿ����쳣�ķ���
	jthrowable ex = (*env)->ExceptionOccurred(env);
	// �������쳣
	if (ex != NULL) {
		// 1�� ����쳣
		(*env)->ExceptionClear(env);

		// ����һ��java���Բ�����쳣
		jclass newException;
		newException = (*env)->FindClass(env,"java/lang/IllegalArgumentException");
		if(newException == NULL){
			return;
		}
		(*env)->ThrowNew(env, newException,"axeChen:This is an Exception!!");
	}
}

// JNI�Ļ������

/// 1���ֲ���̬�������л���
JNIEXPORT void JNICALL Java_demo_JNIMain_getStaticField
(JNIEnv * env, jobject jobj) {
	// �ֲ���̬����
	jclass cls = (*env)->GetObjectClass(env,jobj);

	// static ���� ()
	static jfieldID fid;
	if(fid == NULL){
		fid = (*env)->GetFieldID(env, cls,  "key", "Ljava/lang/String;");
		printf("key\n");
	}

	// �Ǿ�̬
	jfieldID fid2 = NULL;
	if (fid2 == NULL) {
		fid2 = (*env)->GetFieldID(env, cls, "key2", "Ljava/lang/String;");
		printf("key2\n");
	}

}

// ȫ�־�̬����
static jfieldID mFid;
// 1�����÷�Χ������ĺ������еط�
// 2���������static�������ļ�������
JNIEXPORT void JNICALL Java_demo_JNIMain_getGlobalField
(JNIEnv * env, jclass jclz){
	mFid = (*env)->GetFieldID(env, jclz,  "key", "Ljava/lang/String;");
}


//JNI ���� 
// 1�� �ֲ����� 
/*
 1������������
 2��jni��һ���������Ͳ���ֲ�����
 3����jni�������ľֲ��������512������������������ᱨ�쳣������Ҫ��ʱ�ͷ�
 4�������ڶ��߳���ʹ�ã������̫��Ӧ��
*/
JNIEXPORT void JNICALL Java_demo_JNIMain_getGlobalField
(JNIEnv * env, jclass jclz) {
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		jclass cls = (*env)->FindClass(env, "java/util/Date");
		jmethodID jmid = (*env)->GetMethodID(env, cls, "<init>", "()V");
		//����һ��Date���͵ľֲ�����
		jobject obj = (*env)->NewObject(env, cls, jmid);
		//ʹ���������

		//�ͷ�����
		(*env)->DeleteLocalRef(env, cls);
		(*env)->DeleteLocalRef(env, obj);

	}

}
// 2�� ȫ������
//ȫ������
//���̣߳��緽��ʹ��
// NewGlobalRef �Ǵ���ȫ�����õ�Ψһ����
jstring global_str;
JNIEXPORT void JNICALL Java_demo_JNIMain_createGlobalRef
(JNIEnv * env, jobject jobj) {
	jobject obj = (*env)->NewStringUTF(env, "JNI is intersting");
	global_str = (*env)->NewGlobalRef(env, obj);
}
// ʹ�� global_str
JNIEXPORT jstring JNICALL Java_demo_JNIMain_getGlobalRef
(JNIEnv * env, jobject jobj) {
	return global_str;
}

// �ͷ� global_str
JNIEXPORT void JNICALL Java_demo_JNIMain_delGlobalRef
(JNIEnv * env, jobject jobj) {
	(*env)->DeleteGlobalRef(env, global_str);

}
// 3�� ��ȫ������
//��ȫ������
//1����������ֹGC,/���̣߳��緽��ʹ��
//2��������ȫ������NewWeakGlobalRef����
jclass g_weak_cls;
JNIEXPORT jstring JNICALL Java_demo_JNIMain_createWeakRef
(JNIEnv * env, jobject jobj) {
	jclass cls_string = (*env)->FindClass(env, "java/lang/String");
	g_weak_cls = (*env)->NewWeakGlobalRef(env, cls_string);
	return g_weak_cls;
}