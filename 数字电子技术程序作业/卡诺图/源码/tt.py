import algo
num_list=[0,1,2,3,4,7,8,9,10,13]
res_rect = [[0] * 4 for _ in range(4)]
d={
    0:(0,0),1:(0,1),3:(0,2),2:(0,3),
    4:(1,0),5:(1,1),7:(1,2),6:(1,3),
    12:(2,0),13:(2,1),15:(2,2),14:(2,3),
    8:(3,0),9:(3,1),11:(3,2),10:(3,3)
}
for num in num_list:
        x,y=d[num]
        res_rect[x][y]=1
print(res_rect)
res_exp,res_cod=algo.solve(res_rect,4)
for em in res_exp:
    msg=""
    for ch in em:
        if ch=='a':
            msg+='a3 '
        if ch=='A':
            msg+='A3 '
        if ch=='b':
            msg+='a2 '
        if ch=='B':
            msg+='A2 '
        if ch=='c':
            msg+='a1 '
        if ch=='C':
            msg+='A1 '
        if ch=='d':
            msg+='a0 '
        if ch=='D':
            msg+='A0 '
    print(msg)