package package1;

class Teacher extends Person{
    private double salary;
    public Teacher(int id,String name,int age,double salary){
        this.name=name;
        this.age=age;
        this.id=id;
        this.salary=salary;
    }
    public void setSalary(double salary){
        this.salary=salary;
    }   
    public double getSalary(){
        return this.salary;
    }
    public String showTeacherInfo(){
        String msg=showInfo()+"нˮ:"+this.salary+"\n";
        return msg;
    }
}