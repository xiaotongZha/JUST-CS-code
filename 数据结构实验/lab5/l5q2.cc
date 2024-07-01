#include <iostream>

struct BiNode {
    BiNode* left;
    BiNode* right;
    int val;
};

class BiSortTree {
public:
    BiSortTree(int a[], int n) : root(nullptr) {
        for (int i = 0; i < n; i++)
            root = __insert(root, a[i]);
    }
    ~BiSortTree() {
        __release(root);
    }

    void printUpperX(int x){
        __printUpperX(root,x);
    }

private:
    BiNode* root;

    void __release(BiNode* bt) {
        if (bt == nullptr)
            return;
        __release(bt->left);
        __release(bt->right);
        delete bt;
    }

    BiNode* __insert(BiNode* bt, int x) {
        if (bt == nullptr) {
            BiNode* s = new BiNode;
            s->val = x;
            s->left = nullptr, s->right = nullptr;
            bt = s;
            return bt;
        }
        if (bt->val > x)
            bt->left = __insert(bt->left, x);
        else
            bt->right = __insert(bt->right, x);
        return bt; 
    }

    void __printUpperX(BiNode* bt , int x) {
        if (bt != nullptr) {
            if (bt->val <= x){
                __printUpperX(bt->right, x);
            }else{
                __printUpperX(bt->left, x);
                std::cout << bt->val << " ";
                __printUpperX(bt->right, x);
            }
        }
    }
};

int main() {
    int arr[] = {5, 3, 7, 1, 4, 6, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    BiSortTree bs(arr, n);
    std::cout<<"upper than 5:  ";
    bs.printUpperX(5);
    std::cout<<"\nupper than 2:  ";
    bs.printUpperX(2);

    return 0;
}
