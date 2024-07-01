L5=5;R5=6
class subRect:
    sx,sy,dx,dy,dim,len_x,len_y=0,0,0,0,0,0,0
    def __init__(self,sx,sy,dx,dy,len_x,len_y,dim):
        self.sx,self.sy,self.dx,self.dy,self.dim,self.len_x,self.len_y=sx,sy,dx,dy,dim,len_x,len_y

def is_rectangle(grid,rect):
    sx,sy,dx,dy,len_x,len_y,dim=rect.sx,rect.sy,rect.dx,rect.dy,rect.len_x,rect.len_y,rect.dim
    all_not1=True
    if dim!=R5:
        for i in range(sx,sx+dx):
            for j in range(sy,sy+dy):
                if grid[i%len_x][j%len_y] == 0:
                    return False
                if grid[i%len_x][j%len_y] == 1:
                    all_not1=False
        if all_not1:
            return False
    else:
        for i in range(sx,sx+dx):
            for j in range(sy,sy+dy):
                if grid[i%len_x][j%len_y+4] == 0:
                    return False
                if grid[i%len_x][j%len_y+4] == 1:
                    all_not1=False
        if all_not1:
            return False
    return True

def fill_rectangle(grid,rect):
    sx,sy,dx,dy,len_x,len_y,dim=rect.sx,rect.sy,rect.dx,rect.dy,rect.len_x,rect.len_y,rect.dim
    if dim!=R5:
        for i in range(sx,sx+dx):
            for j in range(sy,sy+dy):
                grid[i%len_x][j%len_y]+=1
    else:
        for i in range(sx,sx+dx):
            for j in range(sy,sy+dy):
                grid[i%len_x][j%len_y+4]+=1

def toString_rectangle(grid,rect,symmetry):
    sx,sy,dx,dy,len_x,len_y,dim=rect.sx,rect.sy,rect.dx,rect.dy,rect.len_x,rect.len_y,rect.dim
    res_expression=[]
    if dim == 3:
        if dy==2:
            tmp='aBAb'
            res_expression.append(tmp[sy])
        elif dy==1:
            tmp=['ab','aB','AB','Ab']
            res_expression.append(tmp[sy])
        if dx==1:
            tmp='cC'
            res_expression.append(tmp[sx])
        if len(res_expression)==0:
            return "T"
        else:
            return ''.join(res_expression)
    elif dim == 4:
        if dx==2:
            tmp='aBAb'
            res_expression.append(tmp[sx])
        elif dx==1:
            tmp=['ab','aB','AB','Ab']
            res_expression.append(tmp[sx])
        if dy==2:
            tmp='cDCd'
            res_expression.append(tmp[sy])
        elif dy==1:
            tmp=['cd','cD','CD','Cd']
            res_expression.append(tmp[sy])
        if len(res_expression)==0:
                return "T"
        else:
            return ''.join(res_expression) 
    elif dim==L5:
        if dx==2:
            tmp='aBAb'
            res_expression.append(tmp[sx])
        elif dx==1:
            tmp=['ab','aB','AB','Ab']
            res_expression.append(tmp[sx])
        if not symmetry:
            res_expression.append('c')
        if dy==2:
            tmp='dEDe'
            res_expression.append(tmp[sy])
        elif dy==1:
            tmp=['de','dE','DE','De']
            res_expression.append(tmp[sy])
        return ''.join(res_expression)
    elif dim==R5:
        if dx==2:
            tmp='aBAb'
            res_expression.append(tmp[sx])
        elif dx==1:
            tmp=['ab','aB','AB','Ab']
            res_expression.append(tmp[sx])
        if not symmetry:
            res_expression.append('C')
        if dy==2:
            tmp='dEDe'
            res_expression.append(tmp[sy-4])
        elif dy==1: 
            tmp=['De','DE','dE','de']
            res_expression.append(tmp[sy-4])
        return ''.join(res_expression)

def getCoordinates(rect,symmetry):
    sx,sy,dx,dy,len_x,len_y,dim=rect.sx,rect.sy,rect.dx,rect.dy,rect.len_x,rect.len_y,rect.dim
    res=[]
    if dim!=R5:
        for i in range(sx,sx+dx):
            for j in range(sy,sy+dy):
                res.append((i%len_x,j%len_y))
                if symmetry:
                    res.append((i%len_x,7-(j%len_y)))
    else:
        for i in range(sx,sx+dx):
            for j in range(sy,sy+dy):
                res.append((i%len_x,j%len_y+4))
                if symmetry:
                    res.append((i%len_x,7-(j%len_y+4)))
    return res

def check_all_above_two(grid,rect):
    sx,sy,dx,dy,len_x,len_y,dim=rect.sx,rect.sy,rect.dx,rect.dy,rect.len_x,rect.len_y,rect.dim
    if dim!=R5:
        for i in range(sx,sx+dx):
            for j in range(sy,sy+dy):
                if grid[i%len_x][j%len_y]<=2:
                    return False
    else:
         for i in range(sx,sx+dx):
            for j in range(sy,sy+dy):
                if grid[i%len_x][j%len_y+4]<=2:
                    return False
    return True


def solve(grid,dim):
    res_expression=[];res_coordinate=[]
    if dim==3:
        res_expression,res_coordinate=__solve3(grid)
    elif dim==4:
        res_expression,res_coordinate=__solve4(grid)
    elif dim==5:
        res_expression,res_coordinate=__solve5(grid)
    return res_expression,res_coordinate

def __solve3(grid):
    delta_xy=[(2,4),(2,2),(1,4),(2,1),(1,2),(1,1)]
    res_expression=[];res_coordinate=[]
    res_rect=[]
    for dx,dy in delta_xy: 
        for sx in range(2):
            for sy in range(4):
                if grid[sx][sy]==0:
                    continue
                rect=subRect(sx,sy,dx,dy,2,4,3)
                if is_rectangle(grid,rect):
                    fill_rectangle(grid,rect)
                    res_rect.append(rect)           
    for rect in res_rect:
        if not check_all_above_two(grid,rect):
            res_expression.append(toString_rectangle(grid,rect,False))
            res_coordinate.append(getCoordinates(rect,False))
    return res_expression,res_coordinate

def __solve4(grid):
    delta_xy=[(4,4),(4,2),(2,4),(4,1),(1,4),(2,2),(1,2),(2,1),(1,1)]
    res_expression=[];res_coordinate=[]
    res_rect=[]
    for dx,dy in delta_xy: 
        for sx in range(4):
            for sy in range(4):
                if grid[sx][sy]==0:
                    continue
                rect=subRect(sx,sy,dx,dy,4,4,4)
                if is_rectangle(grid,rect):
                    fill_rectangle(grid,rect)
                    res_rect.append(rect)           
    for rect in res_rect:
        if not check_all_above_two(grid,rect):
            res_expression.append(toString_rectangle(grid,rect,False))
            res_coordinate.append(getCoordinates(rect,False))
    return res_expression,res_coordinate

def is_symmetry(grid,rect):
    sx,sy,dx,dy,len_x,len_y,dim=rect.sx,rect.sy,rect.dx,rect.dy,4,4,rect.dim
    if dim!=R5:
        for i in range(sx,sx+dx):
            for j in range(sy,sy+dy):
                if grid[i%len_x][7-j%len_y] == 0:
                    return False
    else:
        for i in range(sx,sx+dx):
            for j in range(sy,sy+dy):
                if grid[i%len_x][7-(j%len_y+4)] == 0:
                    return False
                
    return True

def fill_symmetry(grid,rect):
    sx,sy,dx,dy,len_x,len_y=rect.sx,rect.sy,rect.dx,rect.dy,4,4
    for i in range(sx,sx+dx):
        for j in range(sy,sy+dy):
            grid[i%len_x][7-(j%len_y)]+=1

def __solve5_left(grid):
    delta_xy=[(4,4),(4,2),(2,4),(4,1),(1,4),(2,2),(1,2),(2,1),(1,1)]
    res_expression=[];res_coordinate=[]
    res_rect=[]
    for dx,dy in delta_xy: 
        for sx in range(4):
            for sy in range(4):
                if grid[sx][sy]==0:
                    continue
                rect=subRect(sx,sy,dx,dy,4,4,L5)
                if is_rectangle(grid,rect):
                    fill_rectangle(grid,rect)
                    if is_symmetry(grid,rect):
                        fill_symmetry(grid,rect)
                        res_rect.append((rect,True))
                    else:
                        res_rect.append((rect,False))
    for rect,isSym in res_rect:
        if not check_all_above_two(grid,rect):
            res_expression.append(toString_rectangle(grid,rect,isSym))
            res_coordinate.append(getCoordinates(rect,isSym))
    return res_expression,res_coordinate

def __solve5_right(grid):
    delta_xy=[(4,4),(4,2),(2,4),(4,1),(1,4),(2,2),(1,2),(2,1),(1,1)]
    res_expression=[];res_coordinate=[]
    res_rect=[]
    for dx,dy in delta_xy: 
        for sx in range(4):
            for sy in range(4,8):
                if grid[sx][sy]==0:
                    continue
                rect=subRect(sx,sy,dx,dy,4,4,R5)
                if is_rectangle(grid,rect):
                    fill_rectangle(grid,rect)
                    if is_symmetry(grid,rect):
                        res_rect.append((rect,True))
                    else:
                        res_rect.append((rect,False))
    for rect,isSym in res_rect:
        if not check_all_above_two(grid,rect):
            res_expression.append(toString_rectangle(grid,rect,isSym))
            res_coordinate.append(getCoordinates(rect,isSym))
    return res_expression,res_coordinate

def __solve5(grid):
    exp1,cod1=__solve5_left(grid)
    exp2,cod2=__solve5_right(grid)
    exp1.extend(exp2)
    cod1.extend(cod2)
    return exp1,cod1

# def init_grid():
#     grid=[]
#     with open("gg",'r') as file:
#         for line in file:
#             grid.append([int(x) for x in line.split()])
#     return grid 

# if __name__=='__main__':
#     grid=init_grid()
#     res=solve(grid,5)
#     exp=res[0];cor=res[1]
#     for i in range(len(exp)):
#         print(exp[i],cor[i]) 
