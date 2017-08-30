
public class JNIHelloWord {

	private native static String getStringFromC();

	static {
		System.loadLibrary("JNI_HelloWord");
	}

	public String key = "key";
	
	public static int count = 9;

	public native void plusField();

	public native String accessField();

	public native String getStringFrom2C();
	
	public static void main(String[] args) {
		System.out.println(getStringFromC());
		
		JNIHelloWord j = new JNIHelloWord();
		
		System.out.println("修改以前："+j.key);
		j.accessField();
		System.out.println("修改后："+j.key);
		
		System.out.println("修改以前："+JNIHelloWord.count);
		j.plusField();
		System.out.println("修改后："+JNIHelloWord.count);
		
		System.out.println("修改非静态"+j.getStringFrom2C());
		
	}

}
