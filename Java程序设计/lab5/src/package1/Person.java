package package1;


public class Person extends Object{
    protected String name;
    protected int age;
    protected int id;
    public Person(){
        this.name="NULL";
        this.age=-1;
        this.id=-1;
    }
    public Person(int id,String name,int age){
        this.name=name;
        this.age=age;
        this.id=id;
    }
    public void setAge(int age){
        this.age=age;
    }
    public void setName(String name){
        this.name=name;
    }
    public void setId(int id){
        this.id=id;
    }
    public int getAge(){
        return this.age;
    }
    public String getName(){
        return this.name;
    }
    public int getId(){
        return this.id;
    }
    protected String showInfo(){
        String msg="–’√˚:"+this.name+"\nƒÍ¡‰:"+this.age+"\n—ß∫≈:"+this.id+'\n';
        return msg;
    }
    @Override
    public String toString() {
        // TODO Auto-generated method stub
        return showInfo();
    }
    public static void main(String[] args) {
        System.out.println("ppp");
    }
}