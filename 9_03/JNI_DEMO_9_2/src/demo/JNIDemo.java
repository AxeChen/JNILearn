package demo;

public class JNIDemo {

	// JNI访问非静态方法
	public native void accessMedthod();

	// JNI访问静态方法
	public native void accessStaticMethod();

	// JNI访问构造函数
	public native void accessConstructMenthod();

	// JNIstrig格式问题
	public native void accessString(String str);

	// 通过调用String的构造方法，返回一个String
	public native String getStringFromJNI();

	static {
		System.loadLibrary("JNI_HelloWord");
	}

	public static void main(String[] args) {
		JNIDemo j = new JNIDemo();
		j.accessMedthod();
		j.accessStaticMethod();
		j.accessConstructMenthod();
		j.accessString("宝宝");
		System.out.println(j.getStringFromJNI());
	}

	public int getInt() {
		return 10;
	}

	public String getString() {
		return "axeChen";
	}

	public int getIntTwo(int value) {
		return 1000;
	}

	public static String getStaticString() {
		return "toString";
	}

	public static int getStaticInt(int value) {
		return 390;
	}
}
