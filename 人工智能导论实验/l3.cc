#include <map>
#include <vector>
#include <iostream>
#include <functional>
#include <sstream>
using namespace std;
map<int,string>feature{
    {0,"毛发"},{1,"产乳"},{2,"羽毛"},{3,"飞行"},{4,"生蛋"},{5,"吃肉"},{6,"爪子"},{7,"利齿"},{8,"前视"},{9,"有蹄"},{10,"反刍"},{11,"黄褐色"},{12,"深色斑点"},{13,"黑色条纹"},{14,"长腿"},{15,"长颈"},{16,"白色"},{17,"黑白相杂"},{18,"游水"},{19,"黑色"}
};
map<int,string>animal{
    {-1,"无法推断"},{0,"动物"},{1,"哺乳动物"},{2,"鸟类动物"},{3,"食肉动物"},{4,"有蹄动物"},{5,"猎豹"},{6,"老虎"},{7,"长颈鹿"},{8,"斑马"},{9,"鸵鸟"},{10,"企鹅"},{11,"海燕"}
};
vector<function<bool(const vector<bool>&)>>checks{
    [](const vector<bool>& v){return true;},//动物
    [](const vector<bool>& v){return v[0] || v[1];},//哺乳动物
    [](const vector<bool>& v){return v[2] || (v[3] && v[4]);},//鸟类动物
    [](const vector<bool>& v){return v[5] || (v[6] && v[7] && v[8]);},//食肉动物
    [](const vector<bool>& v){return v[9] || v[10];},//有蹄动物 4
    [](const vector<bool>& v){return v[11] && v[12];},//猎豹
    [](const vector<bool>& v){return v[11] && v[13];},//老虎
    [](const vector<bool>& v){return v[14] && v[15] && v[11] && v[12];},//长颈鹿
    [](const vector<bool>& v){return v[13] && v[16];},//斑马 8
    [](const vector<bool>& v){return !v[3] && v[14] && v[15] && v[17];},//鸵鸟
    [](const vector<bool>& v){return !v[3] && v[18] && v[16] && v[19];},//企鹅
    [](const vector<bool>& v){return v[3];},//信天翁
};
int solve(const vector<vector<int>>&tree,const vector<bool>&v){
    bool ok=0;
    int ans=-1;
    function<void(int)>dfs=[&](int a){
        if(ok) return;
        printf("这是%s->",animal[a].c_str());
        if(tree[a].size()==0){
            ans=a,ok=1;
            return;
        }
        vector<int>nxt;
        for(auto b:tree[a])
            if(checks[b](v)) nxt.push_back(b);
        if(nxt.size()!=1){
            printf("我不知道\n");
            ok=1;
            return;
        }
        dfs(nxt[0]);
    };
    dfs(0);
    return ans;
}
void printPage(){
#ifndef __linux__
    system("chcp 65001");
#endif
    int i=0;
    for(auto[k,v]:feature){
        printf("[编号:%d 特征:%s]\t",k,v.c_str());
        if((++i)%5==0) printf("\n");
    }
    printf("\n");
    printf("--一行内输入动物具有的特征编号，以空格分割--\n");
}
vector<bool> load(){
    vector<bool>v(20);
    string s;getline(cin,s);
    stringstream sst(s);
    int x;
    while(sst>>x)
        v[x]=1;
    return v;
}
int main(){
    printPage();
    vector<bool>v=load();
    vector<vector<int>>tree(12);
    tree[0]={1,2},tree[1]={3,4},tree[2]={9,10,11},tree[3]={5,6},tree[4]={7,8};
    int res=solve(tree,v);
    printf("推理结果:%s",animal[res].c_str());
    return 0;
}