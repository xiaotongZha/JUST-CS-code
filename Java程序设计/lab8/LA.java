public class StringBufferThreadSafetyExample {
    public static void main(String[] args) {
        // 创建一个共享的StringBuffer对象
        StringBuffer sharedBuffer = new StringBuffer();

        // 创建两个线程，并传入共享的StringBuffer对象
        Thread thread1 = new Thread(new AppendTask(sharedBuffer, "Thread 1"));
        Thread thread2 = new Thread(new AppendTask(sharedBuffer, "Thread 2"));

        // 启动线程
        thread1.start();
        thread2.start();

        // 等待两个线程执行完毕
        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // 打印最终结果
        System.out.println("Final Result: " + sharedBuffer.toString());
    }
}

class AppendTask implements Runnable {
    private StringBuffer sharedBuffer;
    private String threadName;

    public AppendTask(StringBuffer sharedBuffer, String threadName) {
        this.sharedBuffer = sharedBuffer;
        this.threadName = threadName;
    }

    @Override
    public void run() {
        for (int i = 0; i < 50; i++) {
            sharedBuffer.append("Hello from " + threadName + "\n");
        }
    }
}
