package demo;

public class JNIMain {
	
	static {
		System.loadLibrary("JNI_HelloWord");
		// initIDs();
	}
	// 传入一个int数组，然后进行排序
	private native void getArray(int[] array);

	// 在c语言中生成一个字符串数组，然后返回个java
	private native String[] getStringArray(int size);

	// 在jni中生成一个People的数组（存在问题的方法，还没有找解决方法）
	private native PeopleBean[] getPeopleArray(int size);
	
	// 清空一个jni中的异常
	private native void cannotCatchException();
	
	// 生成一个java能捕获的异常
	private native void canCatchException();
	
	// jni中局部静态变量缓存
	public String key ="key";
	public String key2 ="key";
	private native void getStaticField();
	
	// 变量
	// 1、局部变量
	private native void getGlobalField();
	// 2、全局变量
	// 生成一个全局变量并赋值
	private native void createGlobalRef();
	// 在其他的方法中获取这个全局变量
	private native void getGlobalRef();
	// 释放这个全局变量
	private native void delGlobalRef();
	// 3、弱全局变量
	private native void createWeakRef();
	
	public static void main(String[] args) {
		JNIMain jniMain = new JNIMain();
		int[] arry = { 1, 20, 4, 0, 46 };
		jniMain.getArray(arry);
		for (int i : arry) {
			System.out.println(i + "  ");
		}
		String[] strArr = jniMain.getStringArray(10);
		for (String str : strArr) {
			System.out.println(str + "  ");
		}
		// 这里的代码存在问题
//		PeopleBean[] peopleArr = jniMain.getPeopleArray(2);
//		for (PeopleBean bean : peopleArr) {
//			System.out.println(bean.getName() + "  ");
//		}
		jniMain.cannotCatchException();
		
		try{
			jniMain.canCatchException();
		}catch(Exception e){
			System.out.println(e.getMessage());
		}

		for(int i=0;i<10;i++){
			jniMain.getStaticField();
		}
	}
}
