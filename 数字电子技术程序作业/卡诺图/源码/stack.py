class stack:
    def __init__(self):
        self.__top = 0
        self.__data = []
    def push(self,val):
        if self.__top==len(self.__data):
            self.__data.append(val)
        else:
            self.__data[self.__top]=val
        self.__top+=1
    def pop(self):
        if self.__top==0:
            raise IndexError("stack is empty!")
        self.__top-=1
    def top(self):
        if self.__top==0:
            raise IndexError("stack is empty!")
        return self.__data[self.__top-1]
    def size(self):
        return self.__top
    def empty(self):
        return self.__top==0
    def clear(self):
        self.__top=0
        self.__data.clear()
    def show(self):
        print(self.__data)