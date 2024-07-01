import random
t=1000
ss=str(t)+'\n'
for i in range(t):
    n=random.randint(100,1000)
    ss+=str(n)+'\n'
    for j in range(n):
        ss+=str(random.randint(-114514,114514))+' '
    ss+='\n'
print(ss)

