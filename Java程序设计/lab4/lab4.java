import java.time.LocalDate;

public class lab4 {
    public static void main(String[] args) {
        Student s1=new Student("alice", 1001);
        Student s2=new Student("clara", 1002);
        s1.timeOfEnrollment=LocalDate.of(2013,4, 1);
        s2.getTimeOfEnrollment();

    }
}
class Student{
    public static LocalDate timeOfEnrollment = LocalDate.of(2023, 9, 1);
    public static void getTimeOfEnrollment(){
        int year = timeOfEnrollment.getYear();  
        int month = timeOfEnrollment.getMonthValue(); 
        int day = timeOfEnrollment.getDayOfMonth();
        System.out.println("timeOfEnrollment is "+year+"-"+month+"-"+day);
    }
    private String name;
    private int uid;
    public Student(String name,int uid){
        this.name=name;
        this.uid=uid;
    }
    public String toString(){
        String res="name:"+name+"\tuid:"+uid;
        return res;
    }
}

