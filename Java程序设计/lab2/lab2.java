public class lab2 {
    public static void ques1(){
            // byte  
            System.out.println("type:byte bits:" + Byte.SIZE);  
            System.out.println("minval:Byte.MIN_VALUE=" + Byte.MIN_VALUE);  
            System.out.println("maxval:Byte.MAX_VALUE=" + Byte.MAX_VALUE);  
            System.out.println();  
        
            // short  
            System.out.println("type:short bits:" + Short.SIZE);  
            System.out.println("minval:Short.MIN_VALUE=" + Short.MIN_VALUE);  
            System.out.println("maxval:Short.MAX_VALUE=" + Short.MAX_VALUE);  
            System.out.println();  
        
            // int  
            System.out.println("type:int bits:" + Integer.SIZE);  
            System.out.println("minval:Integer.MIN_VALUE=" + Integer.MIN_VALUE);  
            System.out.println("maxval:Integer.MAX_VALUE=" + Integer.MAX_VALUE);  
            System.out.println();  
        
            // long  
            System.out.println("type:long bits:" + Long.SIZE);  
            System.out.println("minval:Long.MIN_VALUE=" + Long.MIN_VALUE);  
            System.out.println("maxval:Long.MAX_VALUE=" + Long.MAX_VALUE);  
            System.out.println();  
        
            // float  
            System.out.println("type:float bits:" + Float.SIZE);   
            System.out.println("minval:Float.MIN_VALUE=" + Float.MIN_VALUE);  
            System.out.println("maxval:Float.MAX_VALUE=" + Float.MAX_VALUE);  
            System.out.println();  
        
            // double  
            System.out.println("type:double bits:" + Double.SIZE);  
            System.out.println("minval:Double.MIN_VALUE=" + Double.MIN_VALUE);  
            System.out.println("maxval:Double.MAX_VALUE=" + Double.MAX_VALUE);  
            System.out.println();  
        
            // char  
            System.out.println("type:char bits:" + Character.SIZE);  
            System.out.println("minval:Character.MIN_VALUE="  + (int) Character.MIN_VALUE);   
            System.out.println("maxval:Character.MAX_VALUE="  + (int) Character.MAX_VALUE);  
    }
    public static void ques234(){
        //定义数组
        int []arr=new int[100];//基本类型数组
        StringBuilder []sbArr=new StringBuilder[10];//对象类型数组
        //初始化数组
        for(int i=0;i<sbArr.length;i++)
            sbArr[i]=new StringBuilder("java is interesting");
        for(int i=0;i<arr.length;i++)
            arr[i]=i;
        //存取数组
        StringBuilder sb0=sbArr[0];
        sb0.append("abcdef");
        sbArr[1].insert(7, " not");

        //遍历打印数组
        for(int x : arr)
            System.out.print(x+" ");
        System.out.println();
        for(StringBuilder em:sbArr)
            System.out.println(em);
    }       
    public static void ques5(int []arr){
        System.out.print("all element:");
        for(int x:arr)
            System.out.print(x+" ");
        System.out.print("\neven number:");
        //打印偶数
        for(int x:arr){
            if(x%2==0)
                System.out.print(x+" ");
        }
        System.out.println();
    }
    public static void main(String[] args) {
        //ques1();
        //ques234();
        //ques5(new int[]{1,2,3,4,5,6,7});
    }
}
