public class lab1 {
    public static void main(String[] args) {
        System.out.println("hello,this is public class");
        CL1.show();
        CL2 c2=new CL2();
        c2.show();
    }
}
class CL1{
    public static void show(){
        System.out.println("hello,this is class CL1 with static function");
    }
}
class CL2{
    public void show(){
        System.out.println("hello,this is class CL2 with member function");
    }
}