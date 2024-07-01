from stack import *
import algo
def is_expr(word):
    return word not in ['(',')','+','*','`']

def low_up(ss):
    res=[]
    for i in ss:
        if str.islower(i):
            res.append(i.upper())
        else:
            res.append(i.lower())
    return ''.join(res)
def vaild(slist):
    s=stack()
    s2=stack()
    n=len(slist)
    for i in range(n):
        if slist[i]=='(':
            s.push(i)
        elif slist[i]==')':
            if s.empty():
                return False
            if i-s.top()==1:
                return False
            s.pop()
        elif slist[i]=='+' or slist[i]=='*':
            if i==0 or i==n-1:
                return False
            ok=False
            pre_is_expr,next_is_expr=is_expr(slist[i-1]),is_expr(slist[i+1])
            if slist[i-1]==')' and slist[i+1]=='(':
                ok=True
            if pre_is_expr and next_is_expr:
                ok=True
            if pre_is_expr and slist[i+1]=='(':
                ok=True
            if slist[i-1]==')' and next_is_expr:
                ok=True
            if slist[i-1]=='`' and (next_is_expr or slist[i+1]=='('):
                ok=True
            if not ok:
                return False
        elif slist[i]=='`':
            if i==0:
                return False
            ok=False
            if slist[i-1]==')':
                ok=True
            if not ok:
                return False
    if not s.empty():
        return False
    return True
def op_or(l1,l2):
    #print("or",l1,l2)
    l1.extend(l2)
    return l1
def op_and(l1,l2):
    #print("and",l1,l2)
    res=[]
    for w1 in l1:
        for w2 in l2:
            res.append(w1+w2)
    return res
def _op_and(l1,l2):
    res=[]
    for w1 in l1:
        for w2 in l2:
            res.append(w1+w2)
    return res
def op_not(l1):
    #print("not",l1)
    res=[]
    ss=stack()
    for w in l1:
        tmp=[]
        for ch in set(w):
            tmp.append(low_up(ch))
        ss.push(tmp)
    res=ss.top()
    ss.pop()
    while not ss.empty():
        res=list(set(_op_and(res,ss.top())))
        ss.pop()
    return res
def to_postfix(slist):
    ops=stack()
    res=[]
    for ch in slist:
        if ch == '(':
            ops.push(ch)
        elif ch == ')':
            while not ops.empty() and ops.top()!='(':
                res.append(ops.top())
                ops.pop()
            ops.pop()
        elif ch=='+':
            while not ops.empty() and ops.top()!='(':
                res.append(ops.top())
                ops.pop()
            ops.push(ch)  
        elif ch=='*':
            ops.push(ch)
        else:
            res.append(ch)
    while not ops.empty():
        res.append(ops.top())
        ops.pop()
    return res

def to_minterm(term,dim):
    res=['']
    chs=[]
    if dim==3:
        chs=[('a','A'),('b','B'),('c','C')]
    elif dim==4:
        chs=[('a','A'),('b','B'),('c','C'),('d','D')]
    elif dim==5:
        chs=[('a','A'),('b','B'),('c','C'),('d','D'),('e','E')]

    for ch1,ch2 in chs:
        f1,f2=term.find(ch1),term.find(ch2)
        rlen=len(res)
        if f1!=-1 and f2!=-1:
            return []
        elif f1==-1 and f2==-1:
            res.extend(res)
            for i in range(rlen):
                res[i]+=ch1
            for i in range(rlen,rlen*2):
                res[i]+=ch2
        elif f1==-1:
            for i in range(rlen):
                res[i]+=ch2
        elif f2==-1:
            for i in range(rlen):
                res[i]+=ch1
    return res

def to_01rect(min_terms,dim):
    num_list=[]
    res_rect=[]
    for term in set(min_terms):
        num=0
        for i in range(dim):
            if term[i].isupper():
                num+=(2**(dim-i-1))
        num_list.append(num)
    #print(num_list)
    d={}
    if dim==3:
        res_rect = [[0] * 4 for _ in range(2)]
        d={
            0:(0,0),2:(0,1),6:(0,2),4:(0,3),
            1:(1,0),3:(1,1),7:(1,2),5:(1,3)
        }
    if dim==4:
        res_rect = [[0] * 4 for _ in range(4)]
        d={
            0:(0,0),1:(0,1),3:(0,2),2:(0,3),
            4:(1,0),5:(1,1),7:(1,2),6:(1,3),
            12:(2,0),13:(2,1),15:(2,2),14:(2,3),
            8:(3,0),9:(3,1),11:(3,2),10:(3,3)
        }
    if dim==5:
        res_rect=[[0] * 8 for _ in range(4)]
        d={
            0:(0,0),1:(0,1),3:(0,2),2:(0,3),6:(0,4),7:(0,5),5:(0,6),4:(0,7),
            8:(1,0),9:(1,1),11:(1,2),10:(1,3),14:(1,4),15:(1,5),13:(1,6),12:(1,7),
            24:(2,0),25:(2,1),27:(2,2),26:(2,3),30:(2,4),31:(2,5),29:(2,6),28:(2,7),
            16:(3,0),17:(3,1),19:(3,2),18:(3,3),22:(3,4),23:(3,5),21:(3,6),20:(3,7)
        }
    for num in num_list:
            x,y=d[num]
            res_rect[x][y]=1
    return res_rect

def solve(slist,dim):
    plist=to_postfix(slist)
    #print("后缀表达式：",plist)
    for i in range(len(plist)):
        if is_expr(plist[i]):
            plist[i]=[plist[i]]
    stc=stack()
    for ch in plist:
        if ch=='+':
            ch1=stc.top()
            stc.pop()
            ch2=stc.top()
            stc.pop()
            stc.push(op_or(ch1,ch2))
        elif ch=='*':
            ch1=stc.top()
            stc.pop()
            ch2=stc.top()
            stc.pop()
            stc.push(op_and(ch1,ch2))
        elif ch=='`':
            ch1=stc.top()
            stc.pop()
            tmp=op_not(ch1)
            stc.push(tmp)
        else:
            stc.push(ch)
    min_terms=[]
    for term in stc.top():
        tmp=to_minterm(term,dim)
        if len(tmp)!=0:
            min_terms.extend(tmp)
    return to_01rect(min_terms,dim)

# if __name__=='__main__':
#     sline="( ( aB ) ` + C ) * ABD + AD "
#     rect=solve(sline.split(),4)
#     print(rect)
#     print(algo.solve(rect,4))


