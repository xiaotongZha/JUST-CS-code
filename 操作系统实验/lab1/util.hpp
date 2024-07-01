#pragma once

#include <iostream>
#include <type_traits>

template<typename T1,typename T2>
std::ostream &operator<<(std::ostream &os,const std::pair<T1,T2>& em){
    os<<'['<<em.first<<" , "<<em.second<<']';
    return os;
}

template <typename T,typename = void>
struct HasBeginEnd : std::false_type{};

template <>
struct HasBeginEnd<std::string> : std::false_type {};

template <typename T>
struct HasBeginEnd<T,std::void_t<decltype(std::declval<T>().begin()),decltype(std::declval<T>().end())>> : std::true_type{};

template<typename T>
void __printList(const T& val){
    if constexpr(HasBeginEnd<T>::value){
        auto first=val.begin();
        auto last=val.end();
        while(first!=last){
            __printList(*first);
            first++;
        }
        std::cout<<'\n';
    }else{
        std::cout<<val<<' ';
    }
}

template<typename T>
void __print(const std::string& vName, const T& val){
    if constexpr(HasBeginEnd<T>::value){
        std::cout<<vName<<":\n";
        __printList(val);
    }else{
        std::cout<<"{"<<vName<<":\t"<<val<<"}\n";
    } 
}

template<typename T>
void __prints(const std::string& vName, const T& val){
    __print(vName,val);
}

template<typename T,typename... Args>
void __prints(const std::string& vName,const T& val,Args ...args){
    __print(vName,val);
    __prints(args...);
}

template <class T>
void printArr(T val,int N){
    static_assert(std::is_pointer<T>::value);
    for(auto first=val;first!=val+N;first++)
        std::cout<<*first<<' ';
    std::cout<<'\n';
}
template <class T>
void printArr(T val,int row,int col){
    static_assert(std::is_pointer<T>::value);
    std::cout<<"[\n";
    for(int i=0;i<row;i++)
        printArr(val[i],col);
    std::cout<<"]\n";
}
template <class T>
void __printl(const std::string& vName,const T& val){
    std::cout<<vName<<':'<<std::endl;
    if constexpr(HasBeginEnd<T>::value){
        for(auto iter=val.begin();iter!=val.end();iter++)
            std::cout<<*iter<<std::endl;
    }else{
        throw std::runtime_error("error type");
    }
}

#define VAR_NAME(x) #x
#define VAR(x) VAR_NAME(x),x
#define __prints1(n1) __prints(VAR(n1))
#define __prints2(n1,n2) __prints(VAR(n1),VAR(n2))
#define __prints3(n1,n2,n3) __prints(VAR(n1),VAR(n2),VAR(n3))
#define __prints4(n1,n2,n3,n4) __prints(VAR(n1),VAR(n2),VAR(n3),VAR(n4))
#define __prints5(n1,n2,n3,n4,n5) __prints(VAR(n1),VAR(n2),VAR(n3),VAR(n4),VAR(n5))
#define __prints6(n1,n2,n3,n4,n5,n6) __prints(VAR(n1),VAR(n2),VAR(n3),VAR(n4),VAR(n5),VAR(n6))
#define __prints7(n1,n2,n3,n4,n5,n6,n7) __prints(VAR(n1),VAR(n2),VAR(n3),VAR(n4),VAR(n5),VAR(n6),VAR(n7))
#define __prints8(n1,n2,n3,n4,n5,n6,n7,n8) __prints(VAR(n1),VAR(n2),VAR(n3),VAR(n4),VAR(n5),VAR(n6),VAR(n7),VAR(n8))
#define __prints9(n1,n2,n3,n4,n5,n6,n7,n8,n9) __prints(VAR(n1),VAR(n2),VAR(n3),VAR(n4),VAR(n5),VAR(n6),VAR(n7),VAR(n8),VAR(n9))
#define VAR_NUM_impl(__1,__2,__3,__4,__5,__6,__7,__8,__9,__N,...) __N
#define VAR_NUM(...) VAR_NUM_impl(__VA_ARGS__,9,8,7,6,5,4,3,2,1)
#define __CONNECT_NAME(__0,__1) __0##__1
#define CONNECT_NAME(__0,__1) __CONNECT_NAME(__0,__1)

#define print(...) CONNECT_NAME(__prints , VAR_NUM(__VA_ARGS__))  (__VA_ARGS__)
#define printl( X ) __printl(VAR(X))

#include <random>
template<class InputIter>
void fill_with_random(InputIter first,InputIter last,int l,int r){
    // 创建随机数生成器引擎
    std::random_device rd; // 用于获取种子值
    std::mt19937 gen(rd()); // Mersenne Twister 伪随机数生成器引擎
    // 创建随机数分布
    std::uniform_int_distribution<int> distribution(l, r);
    while(first!=last){
        *first=distribution(gen);
        first++;
    }
}
//生成[l,r]的随机数
int randomInt(int l, int r) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(l, r);
    return distribution(gen);
}
