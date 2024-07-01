import java.util.LinkedList;

class MyDeque extends LinkedList<Integer> {
    // 重写 addFirst 方法
    @Override
    public void addFirst(Integer e) {
        System.out.println("Adding element to the front: " + e);
        super.addFirst(e);
    }
    // 重写 addLast 方法
    @Override
    public void addLast(Integer e) {
        System.out.println("Adding element to the end: " + e);
        super.addLast(e);
    }
    // 重写 removeFirst 方法
    @Override
    public Integer removeFirst() {
        Integer e = super.removeFirst();
        System.out.println("Removing element from the front: " + e);
        return e;
    }
    // 重写 removeLast 方法
    @Override
    public Integer removeLast() {
        Integer e = super.removeLast();
        System.out.println("Removing element from the end: " + e);
        return e;
    }
}

class MyStack extends MyDeque {
    // 入栈方法
    public void push(int element) {
        addFirst(element);
    }
    // 出栈方法
    public Integer pop() {
        return removeFirst();
    }
    // 获取栈顶元素方法
    public Integer peek() {
        return getFirst();
    }
}

class MyQueue extends MyDeque {
    // 入队方法
    public void enqueue(int element) {
        addLast(element);
    }
    // 出队方法
    public Integer dequeue() {
        return removeFirst();
    }
    // 获取队首元素方法
    public Integer peek() {
        return getFirst();
    }
}

// 测试类
public class Main {
    public static void main(String[] args) {
        // 测试 MyStack
        MyStack stack = new MyStack();
        stack.push(1);
        stack.push(2);
        stack.push(3);
        System.out.println("栈顶元素: " + stack.peek()); // 输出: 栈顶元素: 3
        System.out.println("出栈: " + stack.pop()); // 输出: 出栈: 3
        System.out.println("出栈: " + stack.pop()); // 输出: 出栈: 2
        // 测试 MyQueue
        MyQueue queue = new MyQueue();
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);
        System.out.println("队首元素: " + queue.peek()); // 输出: 队首元素: 1
        System.out.println("出队: " + queue.dequeue()); // 输出: 出队: 1
        System.out.println("出队: " + queue.dequeue()); // 输出: 出队: 2
    }
}
