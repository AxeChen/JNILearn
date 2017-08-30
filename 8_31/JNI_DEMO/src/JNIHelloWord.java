
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
		
		System.out.println("�޸���ǰ��"+j.key);
		j.accessField();
		System.out.println("�޸ĺ�"+j.key);
		
		System.out.println("�޸���ǰ��"+JNIHelloWord.count);
		j.plusField();
		System.out.println("�޸ĺ�"+JNIHelloWord.count);
		
		System.out.println("�޸ķǾ�̬"+j.getStringFrom2C());
		
	}

}
