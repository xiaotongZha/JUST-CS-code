#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkList {
private:
    Node* first; // dummy head

public:
    LinkList(int a[], int n) { // insert in head
        first = new Node;
        Node* r = first, * s = nullptr;
        for (int i = 0; i < n; i++) {
            s = new Node;
            s->data = a[i];
            r->next = s;
            r = s;
        }
        r->next = nullptr;
    }

    LinkList() {
        first = new Node;
        first->next = nullptr;
    }

    ~LinkList() {
        Node* p = first;
        while (first != nullptr) {
            first = first->next;
            delete p;
            p = first;
        }
    }

    int get(int i) {
        Node* p = first->next;
        int count = 0;
        while (p != nullptr && count < i) {
            p = p->next;
            count++;
        }
        if (p == nullptr)
            throw "invalid index";
        else
            return p->data;
    }
    Node* get_ptr(int i){
        Node* p = first->next;
        int count = 0;
        while (p != nullptr && count < i) {
            p = p->next;
            count++;
        }
        if (p == nullptr)
            throw "invalid index";
        else
            return p;
    }

    void insert(int i, int x) {
        Node* p = first, * s = nullptr;
        int count = 0;
        while (p != nullptr && count < i - 1) {
            p = p->next;
            count++;
        }
        if (p == nullptr)
            throw "invalid index";
        else {
            s = new Node;
            s->data = x;
            s->next = p->next;
            p->next = s;
        }
    }

    int erase(int i) {
        int x;
        Node* p = first, * q = nullptr;
        int count = 0;
        while (p != nullptr && count < i - 1) {
            p = p->next;
            count++;
        }
        if (p == nullptr || p->next == nullptr)
            throw "invalid index";
        else {
            q = p->next;
            x = q->data;
            p->next = q->next;
            delete q;
            return x;
        }
    }

    int locate(int x) {
        Node* p = first->next;
        int count = 1;
        while (p != nullptr) {
            if (p->data == x)
                return count;
            p = p->next;
            count++;
        }
        return 0;
    }

    void printList(){
        Node*p=first->next;
        while (p!=nullptr){
            std::cout<<p->data<<' ';
            p=p->next;
        }
        std::cout<<'\n';
    }

    void insertSort();

    void selectSort();
};



void LinkList::insertSort() {
    if(first==nullptr || first->next==nullptr)
        return;
    Node* ni=first->next,*sorted=nullptr;
    while(ni!=nullptr){
        Node*next=ni->next;
        if(sorted==nullptr || sorted->data > ni->data ){//考虑头插
            ni->next=sorted;
            sorted=ni;
        }
        else{
            Node* nj=sorted;//这里不可以用first,原链关系已被打乱
            while(nj->next!=nullptr && nj->next->data < ni->data){
                nj=nj->next;
            }
            ni->next=nj->next;
            nj->next=ni;
        }
        ni=next;
    }

    first->next=sorted;
}

void LinkList::selectSort() {
    if(first==nullptr || first->next==nullptr)
        return;
    Node*head=new Node;
    Node*tail=head;
    while(first->next!=nullptr){
        Node*nmin=nullptr;
        Node*nmin_pref=nullptr;
        int min_val=114514;
        for(Node*ni=first;ni->next!=nullptr;ni=ni->next){
            if(ni->next->data < min_val){
                nmin=ni->next;
                nmin_pref=ni;
                min_val=ni->next->data;
            }
        }
        tail->next=nmin;
        tail=tail->next;
        nmin_pref->next=nmin->next;
    }
    delete first;
    first=head;
}

const int N = 105;
void solve(){
    int t;scanf("%d",&t);
    while(t--){
        int a[N],n;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        LinkList list(a,n);
        list.selectSort();
        list.printList();
    }
}

int main() {
    // int arr1[]={4,2,1,5,2,5,7};
    // LinkList l1(arr1,sizeof(arr1)/sizeof(arr1[0]));
    // l1.selectSort();
    // std::cout<<"selectSort:";
    // l1.printList();

    // LinkList l2(arr1,sizeof(arr1)/sizeof(arr1[0]));
    // l2.insertSort();
    // std::cout<<"insertSort:";
    // l2.printList();
    solve();
    return 0;
}
