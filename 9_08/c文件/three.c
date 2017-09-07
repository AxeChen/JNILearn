#include "stdafx.h"
#include "JNIHelloWord.h"
#include <string.h>

// 函数声明
int compare(jint * a, jint *b);

// 访问基本数据类型数组
JNIEXPORT void JNICALL Java_demo_JNIMain_getArray
(JNIEnv * env, jobject jobj,jintArray arr) {

	//1、jintArray  -> jint *
	jint *elemts = (*env)->GetIntArrayElements(env,arr,NULL);
	if (elemts == NULL) {
		return;
	}
	// 数组长度
	int len = (*env)->GetArrayLength(env,arr);
	// 排序
	qsort(elemts,len,sizeof(int),compare);

	(*env)->ReleaseIntArrayElements(env,arr,elemts,JNI_COMMIT);
}

// 排序
int compare(jint * a, jint *b) {
	return *a - *b;
}

// 访问引用类型数组
JNIEXPORT jobjectArray JNICALL Java_demo_JNIMain_getStringArray
(JNIEnv * env, jobject jobj, jint size) {
	
	//jobjectArray
	jclass jclz = (*env)->FindClass(env, "java/lang/String");
	if (jclz == NULL) {
		return NULL;
	}
	// 生成新的数组
	jobjectArray jobjArray = (*env)->NewObjectArray(env,size,jclz, jobj);
	if (jobjArray == NULL) {
		return NULL;
	}
	// 赋值
	for (int i = 0;i<size;i++) {
		char *c_str = (char *)malloc(256);
		memset(c_str,0,256);
		// 将string存入数组中
		sprintf(c_str,"hello num:%d\n",i);
		// c -> jstring
		jstring str = (*env)->NewStringUTF(env, c_str);
		if (str == NULL) {
			return NULL;
		}
		//将jstring赋值给数组
		(*env)->SetObjectArrayElement(env, jobjArray, i, str);
		free(c_str);
		c_str = NULL;
		(*env)->DeleteGlobalRef(env,str);
	}

	return jobjArray;
}

// 生成一个引用类型的数组
JNIEXPORT jobjectArray JNICALL Java_demo_JNIMain_getPeopleArray
(JNIEnv * env, jobject jobj, jint size) {

	// 获取要生成数组的class
	jclass jclz = (*env)->FindClass(env, "demo/PeopleBean");
	if (jclz == NULL) {
		return NULL;
	}
	// 声明数组
	jobjectArray jobjArray = (*env)->NewObjectArray(env, size, jclz, jobj);
	if (jobjArray == NULL) {
		return NULL;
	}

	// jmethodid 先初始化方法
	jmethodID init = (*env)->GetMethodID(env, jclz, "<init>", "()V");
	// newObject
	jobject people = (*env)->NewObject(env, jclz, init);
	if (people == NULL) return;
	// 获取setName方法ID
	jmethodID setName = (*env)->GetMethodID(env, jclz, "setName", "(Ljava/lang/String;)V");
	if (setName == NULL) return;
	//char *c_str = (char *)malloc(256);
	//memset(c_str, 0, 256);
	//// 将string存入数组中
	//sprintf(c_str, "hello num:%d\n");
	(*env)->CallObjectMethod(env, people, setName,"11111");

	//将people赋值给数组
	//(*env)->SetObjectArrayElement(env, jobjArray, 0, people);

	//free(c_str);
	//c_str = NULL;
	//(*env)->DeleteGlobalRef(env, c_str);

	return jobjArray;
}

//JNI抓捕异常处理
// 原因是：jni产生的异常无法别java捕获，因此这里需要用到jthrowable
JNIEXPORT void JNICALL Java_demo_JNIMain_cannotCatchException
(JNIEnv * env, jobject jobj) {
	jclass jclz = (*env)->FindClass(env, "java/lang/String;");
	jfieldID fid = (*env)->GetFieldID(env, jclz, "key", "LJava/lang/String;");
	/*
	Java调用时产生的异常：
	at demo.JNIMain.catchException(Native Method)
	at demo.JNIMain.main(JNIMain.java:37)
	*/

	// 检测是否有异常的方法
	jthrowable ex = (*env)->ExceptionOccurred(env);
	// 发生了异常
	if (ex!=NULL) {
		// 1、 清空异常
		(*env)->ExceptionClear(env);
	}
}


JNIEXPORT void JNICALL Java_demo_JNIMain_canCatchException
(JNIEnv * env, jobject jobj) {
	jclass jclz = (*env)->FindClass(env, "java/lang/String");
	jfieldID fid = (*env)->GetFieldID(env, jclz, "key", "LJava/lang/String;");
	/*
	Java调用时产生的异常：
	at demo.JNIMain.catchException(Native Method)
	at demo.JNIMain.main(JNIMain.java:37)
	*/

	// 检测是否有异常的方法
	jthrowable ex = (*env)->ExceptionOccurred(env);
	// 发生了异常
	if (ex != NULL) {
		// 1、 清空异常
		(*env)->ExceptionClear(env);

		// 创建一个java可以捕获的异常
		jclass newException;
		newException = (*env)->FindClass(env,"java/lang/IllegalArgumentException");
		if(newException == NULL){
			return;
		}
		(*env)->ThrowNew(env, newException,"axeChen:This is an Exception!!");
	}
}

// JNI的缓存策略

/// 1、局部静态变量进行缓存
JNIEXPORT void JNICALL Java_demo_JNIMain_getStaticField
(JNIEnv * env, jobject jobj) {
	// 局部静态变量
	jclass cls = (*env)->GetObjectClass(env,jobj);

	// static 类型 ()
	static jfieldID fid;
	if(fid == NULL){
		fid = (*env)->GetFieldID(env, cls,  "key", "Ljava/lang/String;");
		printf("key\n");
	}

	// 非静态
	jfieldID fid2 = NULL;
	if (fid2 == NULL) {
		fid2 = (*env)->GetFieldID(env, cls, "key2", "Ljava/lang/String;");
		printf("key2\n");
	}

}

// 全局静态变量
static jfieldID mFid;
// 1、作用范围，定义的后面所有地方
// 2、如果不加static，整个文件都可用
JNIEXPORT void JNICALL Java_demo_JNIMain_getGlobalField
(JNIEnv * env, jclass jclz){
	mFid = (*env)->GetFieldID(env, jclz,  "key", "Ljava/lang/String;");
}


//JNI 引用 
// 1、 局部引用 
/*
 1、必须是引用
 2、jni中一般数据类型不算局部引用
 3、在jni中声明的局部变量最多512个，多余这个数量将会报异常。所以要及时释放
 4、不能在多线程中使用，会产生太多应用
*/
JNIEXPORT void JNICALL Java_demo_JNIMain_getGlobalField
(JNIEnv * env, jclass jclz) {
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		jclass cls = (*env)->FindClass(env, "java/util/Date");
		jmethodID jmid = (*env)->GetMethodID(env, cls, "<init>", "()V");
		//创建一个Date类型的局部引用
		jobject obj = (*env)->NewObject(env, cls, jmid);
		//使用这个引用

		//释放引用
		(*env)->DeleteLocalRef(env, cls);
		(*env)->DeleteLocalRef(env, obj);

	}

}
// 2、 全局引用
//全局引用
//跨线程，跨方法使用
// NewGlobalRef 是创建全局引用的唯一方法
jstring global_str;
JNIEXPORT void JNICALL Java_demo_JNIMain_createGlobalRef
(JNIEnv * env, jobject jobj) {
	jobject obj = (*env)->NewStringUTF(env, "JNI is intersting");
	global_str = (*env)->NewGlobalRef(env, obj);
}
// 使用 global_str
JNIEXPORT jstring JNICALL Java_demo_JNIMain_getGlobalRef
(JNIEnv * env, jobject jobj) {
	return global_str;
}

// 释放 global_str
JNIEXPORT void JNICALL Java_demo_JNIMain_delGlobalRef
(JNIEnv * env, jobject jobj) {
	(*env)->DeleteGlobalRef(env, global_str);

}
// 3、 弱全局引用
//弱全局引用
//1、它不会阻止GC,/跨线程，跨方法使用
//2、声明弱全局引用NewWeakGlobalRef声明
jclass g_weak_cls;
JNIEXPORT jstring JNICALL Java_demo_JNIMain_createWeakRef
(JNIEnv * env, jobject jobj) {
	jclass cls_string = (*env)->FindClass(env, "java/lang/String");
	g_weak_cls = (*env)->NewWeakGlobalRef(env, cls_string);
	return g_weak_cls;
}