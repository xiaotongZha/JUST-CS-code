#include <iostream>
#include <cstring>
using namespace std;

#define MAXLEN 100 

class LinearFind{
public:
    LinearFind(int a[],size_t len):length(len){
        memcpy(data,a,sizeof(int)*len);
    }
    size_t find(int k){
        data[length]=k;
        int pos=0;
        while(data[pos]!=k)
            pos++;
        return pos;
    }
private:
    int data[MAXLEN];
    size_t length;
};

int main(){
    int arr[13]={1,1,4,5,1,4,1,9,1,9,8,1,0};
    LinearFind lf(arr,13);
    cout << "Index of 8 in the array: " << lf.find(8) << '\n';
    cout << "Index of 3 in the array: " << lf.find(3) << '\n';
    return 0;
}