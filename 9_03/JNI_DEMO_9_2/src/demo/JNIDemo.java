package demo;

public class JNIDemo {

	// JNI���ʷǾ�̬����
	public native void accessMedthod();

	// JNI���ʾ�̬����
	public native void accessStaticMethod();

	// JNI���ʹ��캯��
	public native void accessConstructMenthod();

	// JNIstrig��ʽ����
	public native void accessString(String str);

	// ͨ������String�Ĺ��췽��������һ��String
	public native String getStringFromJNI();

	static {
		System.loadLibrary("JNI_HelloWord");
	}

	public static void main(String[] args) {
		JNIDemo j = new JNIDemo();
		j.accessMedthod();
		j.accessStaticMethod();
		j.accessConstructMenthod();
		j.accessString("����");
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
