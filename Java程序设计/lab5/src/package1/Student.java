package package1;

class Student extends Person{
    private double score;
    public Student(int id,String name,int age,double score){
        this.name=name;
        this.age=age;
        this.id=id;
        this.score=score;
    }
    public void setScore(double score){
        this.score=score;
    }   
    public double getScore(){
        return this.score;
    }
    public String showStudentInfo(){
        String msg=showInfo()+"³É¼¨:"+this.score+"\n";
        return msg;
    }
}