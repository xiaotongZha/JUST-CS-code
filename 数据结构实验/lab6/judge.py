import sys
i=1
for line in sys.stdin:
    ls=line.split()
    ls=[int(_) for _ in ls]
    minval=-114514
    for em in ls:
        if(em<minval):
            print(f"WA in test {i}")
            exit()
        minval=em
    i+=1
print("Accept")