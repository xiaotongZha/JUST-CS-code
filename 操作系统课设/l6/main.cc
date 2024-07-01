#include <iostream>
#include <vector>
using namespace std;

struct dir;

struct file{
    string name;
    string cotent;
    dir* father;
};
struct dir{
    string name;
    vector<dir*>childs_d;
    vector<file*>childs_f;
    dir* father;
};
void print_dir(dir*dp){
    vector<string>ds;
    while(dp!=nullptr){
        ds.push_back(dp->name);
        dp=dp->father;
    }

    for(int i=ds.size()-1;i>=0;i--)
        cout<<ds[i]<<"/>"[i==0];
}
file* open_file(dir* dp,string fname){
    for(auto fp:dp->childs_f)
        if(fp->name==fname)
            return fp;
    return nullptr;
}
void close_file(file* fp){
    fp=nullptr;
}
void create_file(dir* dp,string fname){
    file* fp=new file;
    fp->cotent="",fp->father=dp,fp->name=fname;
    dp->childs_f.push_back(fp);   
    cout<<"create ok\n"; 
}
void delete_file(dir* dp,string fname){
    auto &fs=dp->childs_f;
    bool ok=0;
    for(auto it=fs.begin();it!=fs.end();it++){
        if((*it)->name==fname){
            delete (*it);
            fs.erase(it);
            ok=1;
            break;
        }
    }
    if(!ok)cerr<<"no such file\n";
    else cout<<"delet ok\n";
}
dir* change_dir(dir* dp,string dname){
    if(dname=="../")
        return dp->father;
    for(auto fp:dp->childs_d)
        if(fp->name==dname)
            return fp;
    return nullptr;
}
void create_dir(dir* dp,string dname){
    dir* dr=new dir;
    dr->father=dp,dr->name=dname;
    dp->childs_d.push_back(dr); 
    cout<<"create ok\n"; 
}
void release(dir* root){
    if(root==nullptr)return;
    for(auto fp:root->childs_f)
        delete fp;
    for(auto dp:root->childs_d)
        release(dp);
    delete root;
}
void delete_dir(dir* dp,string dname){
    auto &ds=dp->childs_d;
    bool ok=0;
    for(auto it=ds.begin();it!=ds.end();it++){
        if((*it)->name==dname){
            release((*it));
            ds.erase(it);
            ok=1;
            break;
        }
    }
    if(!ok)cerr<<"no such file\n";
    else cout<<"delete ok\n";
}
void ls(dir* cur){
    for(auto dp:cur->childs_d)
        cout<<dp->name<<'\t';
    for(auto fp:cur->childs_f)
        cout<<fp->name<<'\t';
    cout<<'\n';
}
void read_file(dir* dp,string fname){
    file* fp=open_file(dp,fname);
    if(fp) cout<<fp->cotent<<'\n';
    else cerr<<"no such file\n";
}
void write_file(dir* dp,string fname,string msg){
    file* fp=open_file(dp,fname);
    if(fp) fp->cotent=msg;
    else cerr<<"no such file\n";
}
int main(){
    system("chcp 65001");
    dir* root=new dir;
    root->name="root",root->father=nullptr;
    dir* cur=root;
    while(true){
        print_dir(cur);
        string cmd;cin>>cmd;
        if(cmd=="mkdir"){
            string dname;cin>>dname;
            create_dir(cur,dname);
        }else if(cmd=="rmdir"){
            string dname;cin>>dname;
            delete_dir(cur,dname);
        }else if(cmd=="cd"){
            string dname;cin>>dname;
            dir* ndir=change_dir(cur,dname);
            if(ndir==nullptr)cerr<<"No such file\n";
            else cur=ndir;
        }else if(cmd=="mkfile"){
            string fname;cin>>fname;
            create_file(cur,fname);
        }else if(cmd=="rmfile"){
            string fname;cin>>fname;
            delete_file(cur,fname);
        }else if(cmd=="read"){
            string fname;cin>>fname;
            read_file(cur,fname);
        }else if(cmd=="write"){
            string fname,msg;cin>>fname>>msg;
            write_file(cur,fname,msg);
        }else if(cmd=="ls"){
            ls(cur);
        }else if(cmd=="man"){
            cout<<"mkdir dirname - 创建文件夹\nrmdir dirname - 删除文件夹\ncd dirname - 切换文件夹\nmkfile filename - 创建文件\nrmfile filename - 删除文件\nwrite filename - 写入文件\nread filename - 读取文件\n";
        }else if(cmd=="exit"){
            break;
        }else{
            cerr<<"no such command\n";
        }
    }
    release(root);
    return 0;
}