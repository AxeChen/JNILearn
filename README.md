# JNILearn
JNI的学习  
### 8月31号
#### 简单的JNI流程示例。  
#### 出发native函数，JNI访问java静态属性，非静态属性。
**开发工具：** eclipse，用于编写native方法和加载动态库。 vs2015.用于编写jni代码，生成动态库。
* 1、编写native方法
```
	private native static String getStringFromC();
```
* 2、通过javah命令生成.h文件  
```
 //javah 文件名称
 javah JNIHelloWord
```
生成的.h文件中native对应的方法。
```
/*
 * Class:     JNIHelloWord
 * Method:    getStringFromC
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_JNIHelloWord_getStringFromC
  (JNIEnv *, jclass);
```
生成方法的命名规则： Java_[java类的名称]_[方法名称]
* 3、实现.h 头文件中的声明函数
```
 JNIEXPORT jstring JNICALL Java_JNIHelloWord_getStringFromC
 (JNIEnv * env, jclass jclass) {
	return (*env)->NewStringUTF(env,"hello word");
 }
```
* 4、生成一个dll 动态库
linux中是.os文件

* 5、在java中加载动态库
```
	static {
		System.loadLibrary("JNI_HelloWord");
	}
```
* 6、触发native函数
```
public static void main(String[] args) {
		// 访问静态的方法
		getStringFromC();
}
```
出以上之外，还有访问静态方法，静态属性等其他示例。
