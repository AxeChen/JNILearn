package demo;

public class JNIMain {
	
	static {
		System.loadLibrary("JNI_HelloWord");
		// initIDs();
	}
	// ����һ��int���飬Ȼ���������
	private native void getArray(int[] array);

	// ��c����������һ���ַ������飬Ȼ�󷵻ظ�java
	private native String[] getStringArray(int size);

	// ��jni������һ��People�����飨��������ķ�������û���ҽ��������
	private native PeopleBean[] getPeopleArray(int size);
	
	// ���һ��jni�е��쳣
	private native void cannotCatchException();
	
	// ����һ��java�ܲ�����쳣
	private native void canCatchException();
	
	// jni�оֲ���̬��������
	public String key ="key";
	public String key2 ="key";
	private native void getStaticField();
	
	// ����
	// 1���ֲ�����
	private native void getGlobalField();
	// 2��ȫ�ֱ���
	// ����һ��ȫ�ֱ�������ֵ
	private native void createGlobalRef();
	// �������ķ����л�ȡ���ȫ�ֱ���
	private native void getGlobalRef();
	// �ͷ����ȫ�ֱ���
	private native void delGlobalRef();
	// 3����ȫ�ֱ���
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
		// ����Ĵ����������
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
