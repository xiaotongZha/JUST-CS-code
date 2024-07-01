
public class Person extends Object {
    private String name;
    private int age;
    private int id;

    // 无参构造函数
    public Person() {
        this.name = "NULL";
        this.age = -1;
        this.id = -1;
    }

    // 有参构造函数
    public Person(int id, String name, int age) {
        this.name = name;
        this.age = age;
        this.id = id;
    }

    // 打印信息的成员函数
    protected String showInfo() {
        String msg = "姓名: " + this.name + "\n年龄: " + this.age + "\n学号: " + this.id + '\n';
        return msg;
    }

    // 重写的toString方法
    @Override
    public String toString() {
        return showInfo();
    }

    // 主方法进行测试
    public static void main(String[] args) {
        // 使用无参构造函数创建对象
        Person p1 = new Person();
        p1.name = "张三";
        System.out.println(p1.showInfo());

        // 使用有参构造函数创建对象
        Person p2 = new Person(10, "李四", 12);
        System.out.println(p2.toString());
    }
}
