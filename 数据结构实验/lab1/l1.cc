#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
};

class LinkList
{
private:
    Node *first;//dummy head
public:
    LinkList(int a[],int n){//insert in head
        first=new Node;
        Node*r=first,*s=nullptr;
        for(int i=0;i<n;i++){
            s=new Node;
            s->data=a[i];
            r->next=s;
            r=s;
        }
        r->next=nullptr;
    }
    LinkList(){
        first=new Node;
        first->next=nullptr;
    }
    ~LinkList(){
        Node*p=first;
        while(first!=nullptr){
            first=first->next;
            delete p;
            p=first;
        }
    }
    int get(int i){
        Node*p=first->next;
        int count=i;
        while(p!=nullptr && count<i){
            p=p->next;
            count++;
        }
        if(p==nullptr)
            throw "invaild index";
        else
            return p->data;
    }
    void insert(int i,int x){
        Node *p=first,*s=nullptr;
        int count=0;
        while (p!=nullptr && count<i-1){
            p=p->next;
            count++;
        }
        if(p==nullptr)throw"invaild index";
        else{
            s=new Node;
            s->data=x;
            s->next=p->next;
            p->next=s;
        }
    }
    int erase(int i){
        int x;
        Node *p=first,*q=nullptr;
        int count=0;
        while(p!=nullptr && count<i-1){
            p=p->next;
            count++;
        }
        if(p==nullptr || p->next==nullptr)
            throw "invaild index";
        else{
            q=p->next;
            x=q->data;
            p->next=q->next;
            delete q;
            return x;
        }
    }
    int locate(int x){
        Node *p=first->next;
        int count=1;
        while(p!=nullptr){
            if(p->data==x)
                return count;
            p=p->next;
            count++;
        }
        return 0;
    }
    void printList(){
        Node*p=first->next;
        while (p!=nullptr){
            cout<<p->data<<'\t';
            p=p->next;
        }
        cout<<'\n';
    }
    void reverse(){
        Node*pre=nullptr;
        Node*head=first->next;
        if(head==nullptr)return;
        Node*nxt=head->next;
        while(head!=nullptr){
            head->next=pre;
            pre=head;
            head=nxt;
            if(nxt!=nullptr)
                nxt=nxt->next;
        }
        first->next=pre;
    }
    void unique(){
        Node*head=first->next;
        Node*pre=nullptr;
        int val= -114514;
        while(head!=nullptr){
            if(head->data==val){
                Node*tmp=head;
                head=head->next;
                pre->next=head;
                delete tmp;
            }else{
                pre=head;
                val=head->data;
                head=head->next;
            }
        }
    }
};
int main() {
    int arr[] = {1, 2, 3, 3, 4, 5, 5, 5, 6, 7, 8, 9};

    // 创建链表并打印原始链表
    LinkList l1(arr, sizeof(arr) / sizeof(int));
    std::cout << "Original List: ";
    l1.printList();

    // 反转链表并打印
    std::cout << "Reversed List: ";
    l1.reverse();
    l1.printList();

    // 删除重复节点并打印
    std::cout << "Unique List: ";
    l1.unique();
    l1.printList();

    return 0;
}
