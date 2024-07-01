import java.util.LinkedList;

class MyDeque extends LinkedList<Integer> {
    // ��д addFirst ����
    @Override
    public void addFirst(Integer e) {
        System.out.println("Adding element to the front: " + e);
        super.addFirst(e);
    }
    // ��д addLast ����
    @Override
    public void addLast(Integer e) {
        System.out.println("Adding element to the end: " + e);
        super.addLast(e);
    }
    // ��д removeFirst ����
    @Override
    public Integer removeFirst() {
        Integer e = super.removeFirst();
        System.out.println("Removing element from the front: " + e);
        return e;
    }
    // ��д removeLast ����
    @Override
    public Integer removeLast() {
        Integer e = super.removeLast();
        System.out.println("Removing element from the end: " + e);
        return e;
    }
}

class MyStack extends MyDeque {
    // ��ջ����
    public void push(int element) {
        addFirst(element);
    }
    // ��ջ����
    public Integer pop() {
        return removeFirst();
    }
    // ��ȡջ��Ԫ�ط���
    public Integer peek() {
        return getFirst();
    }
}

class MyQueue extends MyDeque {
    // ��ӷ���
    public void enqueue(int element) {
        addLast(element);
    }
    // ���ӷ���
    public Integer dequeue() {
        return removeFirst();
    }
    // ��ȡ����Ԫ�ط���
    public Integer peek() {
        return getFirst();
    }
}

// ������
public class Main {
    public static void main(String[] args) {
        // ���� MyStack
        MyStack stack = new MyStack();
        stack.push(1);
        stack.push(2);
        stack.push(3);
        System.out.println("ջ��Ԫ��: " + stack.peek()); // ���: ջ��Ԫ��: 3
        System.out.println("��ջ: " + stack.pop()); // ���: ��ջ: 3
        System.out.println("��ջ: " + stack.pop()); // ���: ��ջ: 2
        // ���� MyQueue
        MyQueue queue = new MyQueue();
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);
        System.out.println("����Ԫ��: " + queue.peek()); // ���: ����Ԫ��: 1
        System.out.println("����: " + queue.dequeue()); // ���: ����: 1
        System.out.println("����: " + queue.dequeue()); // ���: ����: 2
    }
}
