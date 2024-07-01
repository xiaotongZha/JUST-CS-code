#include <iostream>
using namespace std;

struct Node{
    int data;
    Node*next;
};
class LinkStack{
private:
    Node*first;
public:
    LinkStack(){
        first=new Node;
        first->next=nullptr;
    }
    void push(int x){
        Node*p=new Node;
        Node*head=first->next;
        p->next=head;
        p->data=x;
        first->next=p;
    }
    void pop(){
        if(first->next==nullptr)
            throw "empty stack!";
        Node*head=first->next;
        first->next=head->next;
        delete head;
    }
    int top(){
        if(first->next==nullptr)
            throw "empty stack!";
        return first->next->data;
    }
    bool empty(){
        return first->next==nullptr;
    }
    ~LinkStack(){
        Node*p=first;
        while(first!=nullptr){
            first=first->next;
            delete p;
            p=first;
        }
    }

};

int main(){
    ios::sync_with_stdio(false);
    cout<<"Please enter the number of examples\n";
    int t;cin>>t;
    LinkStack ls;
    cout<<"Please enter the elements to be pushed onto the stack\n";
    while(t--){
        int x;cin>>x;
        if(x!=-1)
            ls.push(x);
        else{
            cout<<ls.top()<<'\n';
            ls.pop();
        }
    }
    
        

    return 0;
}