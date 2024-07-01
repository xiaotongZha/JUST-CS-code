
public class Person extends Object {
    private String name;
    private int age;
    private int id;

    // �޲ι��캯��
    public Person() {
        this.name = "NULL";
        this.age = -1;
        this.id = -1;
    }

    // �вι��캯��
    public Person(int id, String name, int age) {
        this.name = name;
        this.age = age;
        this.id = id;
    }

    // ��ӡ��Ϣ�ĳ�Ա����
    protected String showInfo() {
        String msg = "����: " + this.name + "\n����: " + this.age + "\nѧ��: " + this.id + '\n';
        return msg;
    }

    // ��д��toString����
    @Override
    public String toString() {
        return showInfo();
    }

    // ���������в���
    public static void main(String[] args) {
        // ʹ���޲ι��캯����������
        Person p1 = new Person();
        p1.name = "����";
        System.out.println(p1.showInfo());

        // ʹ���вι��캯����������
        Person p2 = new Person(10, "����", 12);
        System.out.println(p2.toString());
    }
}
