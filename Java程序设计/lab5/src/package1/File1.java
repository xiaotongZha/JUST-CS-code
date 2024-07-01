package package1;
public class File1 {
    public static void main(String[] args) {
        Person p1=new Person();
        p1.name="张三";
        System.out.println(p1.showInfo());
        Person p2=new Person(10, "李四", 12);
        System.out.println(p2.toString());
        Student stu1=new Student(1001, "小明", 18, 82.5);
        System.out.println(stu1.showInfo());
        System.out.println(stu1.showStudentInfo());
    }
}




