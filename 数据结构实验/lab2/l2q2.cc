#include <iostream>
struct Node{
    int data;
    Node*next;
};
class LinkQueue{
private:
    Node*tail;
public:
    LinkQueue(){
        tail=nullptr;
    }
    void push(int x){
        if(tail==nullptr){
            tail=new Node;
            tail->data=x;
            tail->next=tail;
        }else{
            Node*head=tail->next;
            Node*p=new Node;
            p->data=x;
            p->next=head;
            tail->next=p;
            tail=p;
        }
    }
    void pop(){
        if(tail==nullptr){
            throw "empty queue!";
        }else{
            Node*head=tail->next->next;
            if(tail->next==tail){
                delete tail;
                tail=nullptr;
            }else{
                delete tail->next;
                tail->next=head;
            }
        }
    }
    int front(){
        if(tail==nullptr){
            throw "empty queue!";
            return -114514;
        }
        else
            return tail->next->data;
    }
    bool empty(){
        return tail==nullptr;
    }
    ~LinkQueue(){
        Node*p;
        while(tail!=nullptr){
            p=tail;
            tail=tail->next;
            delete p;
        }
    }
};
int main(){
    LinkQueue lq;
    int arr[]={1,2,3,4,5,6,7,8,9};
    std::cout<<"input sequence:";
    for(int a: arr){
        lq.push(a);
        std::cout<<a<<' ';
    }
    std::cout<<'\n';

    std::cout<<"LinkQueue sequeue:";
    while(!lq.empty()){
        std::cout<<lq.front()<<" ";
        lq.pop();
    }
    std::cout<<'\n';
    return 0;
}