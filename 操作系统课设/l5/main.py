from random import randint,seed
import matplotlib.pyplot as plt

def getInstruction():
    instruction=[]
    for i in range(0,320,4):
        mid=randint(0,318)
        instruction.extend([randint(0,mid),mid,mid+1,randint(mid+1,319)])
    return instruction

def FIFO(instruction,userMemSize):
    userMemList=[]
    hitCount=0
    for x in instruction:
        x//=10
        if userMemList.count(x)==0:
            if len(userMemList)>=userMemSize:
                userMemList.pop(0)
            userMemList.append(x)
        else:
            hitCount+=1
    return hitCount/len(instruction)

def LRU(instruction,userMemSize):
    lastAppear={}
    hitCount=0
    for i,x in enumerate(instruction):
        x//=10
        if lastAppear.get(x)==None:
            if len(lastAppear)>=userMemSize:
                min_value=min(lastAppear,key=lambda k:lastAppear[k])
                lastAppear.pop(min_value)
            lastAppear.update({x:i})
        else:
            lastAppear[x]=i
            hitCount+=1
    return hitCount/len(instruction)

def OPT(instruction,userMemSize):
    userMemList=[]
    futureAppearCnt={}
    for i,x in enumerate(instruction):
        x//=10
        if futureAppearCnt.get(x)==None:
            futureAppearCnt.update({x:1})
        else:
            futureAppearCnt[x]+=1
    hitCount=0
    for i,x in enumerate(instruction):
        x//=10
        if userMemList.count(x)==0:
            if len(userMemList)>=userMemSize:
                min_index=-1
                min_value=114514
                for j,y in enumerate(userMemList):
                    if  min_value>futureAppearCnt[y]:
                        min_index=j
                        min_value=futureAppearCnt[y]
                userMemList.pop(min_index)
            userMemList.append(x)
        else:
            hitCount+=1
        futureAppearCnt[x]-=1
    return hitCount/len(instruction)

def CLOCK(instruction,userMemSize):
    userMemList=[]
    pageCount={}
    ptr=0
    hitCount=0
    for x in instruction:
        x//=10
        if userMemList.count(x)==0:
            if len(userMemList)<userMemSize:
                userMemList.append(x)
                pageCount.update({x:1})
                ptr=(ptr+1)%userMemSize
            else:
                while pageCount[userMemList[ptr]]==1:
                    pageCount[userMemList[ptr]]=0
                    ptr=(ptr+1)%userMemSize

                pageCount.pop(userMemList[ptr])
                pageCount.update({x:1})
                userMemList[ptr]=x
                ptr=(ptr+1)%userMemSize
        else:
            pageCount[x]=1
            hitCount+=1
    return hitCount/len(instruction)

if __name__=='__main__':
    #random.seed(1003)
    instruction=getInstruction()
    X=[_ for _ in range(2,33)]
    LRU_Result=[LRU(instruction,i) for i in range(2,33)]
    FIFO_Result=[FIFO(instruction,i) for i in range(2,33)]
    OPT_Result=[OPT(instruction,i) for i in range(2,33)]
    CLOCK_Result=[CLOCK(instruction,i) for i in range(2,33)]

    plt.figure()
    plt.plot(X, LRU_Result, label='LRU', color='blue')  
    plt.plot(X, FIFO_Result, label='FIFO', color='red')   
    plt.plot(X, OPT_Result, label='OPT', color='green')
    plt.plot(X,CLOCK_Result,label='CLOCK',color='purple')
    plt.title('Four algorithm')
    plt.xlabel('内存块数',fontproperties='SimHei')
    plt.ylabel('命中率',fontproperties='SimHei')
    plt.legend() 
    plt.grid(True)
    plt.show()
