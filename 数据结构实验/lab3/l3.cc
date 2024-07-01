#include <iostream>
#include <functional>
using namespace std;
#define FIN -114514
struct BiNode{
    int data;
    BiNode *left,*right;
};
class BiTree{
public:
    BiTree(int a[],int len,int &pos){root=create(a,len,pos);}
    void preOrder(){__preOrder(root);cout<<'\n';}
    void inOrder(){__inOrder(root);cout<<'\n';}
    void postOrder(){__postOrder(root);cout<<'\n';}

    void bi_abs(){
        function<void(BiNode*)>dfs=[&dfs](BiNode*p){
            if(p==nullptr)
                return;
            dfs(p->left);
            if(p->data<0)
                p->data=-p->data;
            dfs(p->right);
        };
        dfs(root);
    }
    ~BiTree(){release(root);}
private:
    BiNode *root;
    BiNode *create(int a[],int len,int &pos){
        BiNode*bt;
        if(a[pos]==FIN){ 
            bt=nullptr;
            if(pos!=len-1)
                pos++;
        }
        else{
            bt=new BiNode;
            bt->data=a[pos];
            pos++;
            bt->left=create(a,len,pos);
            bt->right=create(a,len,pos);
        }
        return bt;
    }
    void release(BiNode*bt){
        if(bt==nullptr)
            return;
        release(bt->left);
        release(bt->right);
        delete bt;
    }
    void __preOrder(BiNode*bt){
        if(bt==nullptr)
            return;
        cout<<bt->data<<' ';
        __preOrder(bt->left);
        __preOrder(bt->right);
    }
    void __inOrder(BiNode*bt){
        if(bt==nullptr)
            return;
        __inOrder(bt->left);
        cout<<bt->data<<' ';
        __inOrder(bt->right);
    }
    void __postOrder(BiNode*bt){
        if(bt==nullptr)
            return;
        __postOrder(bt->left);
        __postOrder(bt->right);
        cout<<bt->data<<' ';
    }
};

int main() {
    int a[] = {1, 2, -3, FIN, FIN, -4, FIN, FIN, 5, 6, FIN, FIN, 7, 8, FIN};
    int pos = 0;
    BiTree bt(a, sizeof(a) / sizeof(int), pos);
    cout << "Original Binary Tree:" << endl;
    cout << "Pre-order: ";
    bt.preOrder();
    cout << "In-order: ";
    bt.inOrder();
    cout << "Post-order: ";
    bt.postOrder();
    cout << "Binary Tree After Applying bi_abs,Pre-order:" << endl;
    bt.bi_abs();
    bt.preOrder();
    
    return 0;
}
