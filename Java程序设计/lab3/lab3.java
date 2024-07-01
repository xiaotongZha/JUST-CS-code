import java.util.ArrayList;
import java.util.Stack;

public class lab3 {
    public static void StackOverFLow(){
        StackOverFLow();
    }
    public static void HeapOverFLow(){
        StringBuilder sb=new StringBuilder("this is a string");
        ArrayList<StringBuilder>alist=new ArrayList<>();
        for(int i=1;;i++){
            if(i%50000000==0){
                i=1;
                System.out.println(Runtime.getRuntime().freeMemory());
            }
            alist.add(sb);
        }
    }
    public static void main(String[] args) {
        HeapOverFLow();
    }
}   
