import tkinter as tk
import tkinter.messagebox as tkmsg
from PIL import Image, ImageTk
import algo 
import anal
class myUI:
    dim_val=None
    char_on_ui=[['A','B','C','D','E'],['A`','B`','C`','D`','E`'],['(',')',')`','+','*']]
    char_fact=[['A','B','C','D','E'],['a','b','c','d','e'],[' ( ',' ) ',' ) ` ',' + ',' * ']]
    cbtn_mat=[[None for _ in range(5)] for _ in range(3)]
    fact_str=[]
    rect_01=[[0,0,0,0,0,0,0,0],[1,1,0,1,0,0,0,0],[0,1,1,0,0,0,0,0],[1,1,1,1,0,0,0,0]]
    photos=[]
    canvas_list=[]
    colors = ["blue violet", "black", "red", "green", "blue", "yellow", "orange", "purple",
          "pink", "brown", "gray", "cyan", "magenta", "violet", "lime", "turquoise"]
    color_cnt=0
    def __init__(self,root):
        self.root=root
        self.root.title("卡诺图化简")
        self.root.geometry("800x600")
        self.frame = tk.Frame(self.root,relief=tk.SUNKEN,borderwidth=1,background="#3b84c0")
        self.frame.pack(side=tk.TOP,fill=tk.BOTH,expand=1)
        self.frame_top=tk.Frame(self.frame,width=800,height=100,background="#3b84c0")
        self.frame_top.pack()
        self.title_label=tk.Label(self.frame_top,width=28,text="     卡诺图化简可视化",font=("宋体",30,'bold'),background="#3b84c0")
        self.title_label.grid(row=0,column=0)

        self.infoBtn=tk.Button(self.frame_top,width=8,text="必看!",font=("宋体",20,'bold'),background="grey",command=self.infoBtn_click)
        self.infoBtn.grid(row=0,column=1)

        self.signBtn=tk.Button(self.frame_top,width=4,text="签名",font=("宋体",14,'bold'),background="grey",command=self.signBtn_click)
        self.signBtn.grid(row=0,column=2)

        self.frame_content=tk.Frame(self.frame,width=800,background="#88d2ed")
        self.frame_content.pack()
        self.frame_left=tk.Frame(self.frame_content,width=400,height=500,background="#88d2ed")
        self.frame_left.grid(row=0,column=0)
        self.frame_right=tk.Frame(self.frame_content,width=400,height=500,background="#88d2ed")
        self.frame_right.grid(row=0,column=1)

        self.frame_choose=tk.Frame(self.frame_left,borderwidth=1,background="#88d2ed",pady=10)
        self.frame_choose.pack()
        self.dim_val=tk.IntVar()
        self.dim_val.set(3)
        self.dim_radioBtns=[None for _ in range(3)]
        for i in range(3):
            self.dim_radioBtns[i]=tk.Radiobutton(self.frame_choose,width=10,height=3,text=f"{i+3}变量",variable=self.dim_val,value=i+3,font=("宋体",12),command=self.dim_select)
            self.dim_radioBtns[i].grid(row=0,column=i)


        self.frame_input=tk.Frame(self.frame_left,height=300,borderwidth=1,background="pink",pady=10)
        self.frame_input.pack(side=tk.TOP)
        self.input_line=tk.Message(self.frame_input,width=290,text="",font=('宋体',18,'bold'))
        self.input_line.grid(columnspan=5,pady=10)

        for i in range(3):
            for j in range(5):
                self.cbtn_mat[i][j]=tk.Button(self.frame_input,width=3,height=1,text=self.char_on_ui[i][j],font=('宋体',24,'bold'))
                if j>=3:
                    self.cbtn_mat[i][j].config(state='disabled')
                self.cbtn_mat[i][j].grid(row=i+1,column=j,padx=2,pady=2)
                self.cbtn_mat[i][j].bind('<ButtonPress-1>',self.charButton_click)
        for j in range(5):
            self.cbtn_mat[2][j].config(state="active")

        self.frame_button=tk.Frame(self.frame_left,height=100,background="pink")
        self.frame_button.pack()        

        self.backBtn=tk.Button(self.frame_button,text="<-",font=("宋体",18,'bold'))
        self.backBtn.grid(row=0,column=0,padx=10)
        self.backBtn.bind('<ButtonPress-1>',self.backButton_click)

        self.resetBtn=tk.Button(self.frame_button,text="重置",font=("宋体",18,'bold'))
        self.resetBtn.grid(row=0,column=1,padx=10)
        self.resetBtn.bind('<ButtonPress-1>',self.resetButton_click)

        self.submitBtn=tk.Button(self.frame_button,text="解析",font=("宋体",18,'bold'))
        self.submitBtn.grid(row=0,column=2,padx=10)
        self.submitBtn.bind('<ButtonPress-1>',self.submitButton_click)

        self.frame_footer=tk.Frame(self.frame,width=800,height=100,background="#88d2ed")
        self.frame_footer.pack()
        self.result_label=tk.Label(self.frame_footer,width=45,text="这里是结果",font=("宋体",20,'bold'),background="#8997b6")
        self.result_label.pack()

    def draw_3val(self):
        if len(self.canvas_list)!=0:
            for canv in self.canvas_list:
                canv.grid_forget()
            self.canvas_list.clear()
        self.photos.clear()
        cell_width = 80;cell_height = 80
        filenames=[['3var','00','01','11','10'],
                   ['0'],
                   ['1']]
        for i in range(2):
            for j in range(4):
                filenames[i+1].append(str(self.rect_01[i][j]))
        for i in range(3):
            for j in range(5):
                self.canvas_list.append(tk.Canvas(self.frame_right,width=cell_width,height=cell_height))
                self.canvas_list[-1].grid(row=i,column=j)
                img=Image.open(f"source/{filenames[i][j]}.jpg")
                img = img.resize((cell_width, cell_height), Image.ANTIALIAS)
                photo = ImageTk.PhotoImage(img)
                self.photos.append(photo)
                self.canvas_list[-1].create_image(0, 0, anchor=tk.NW, image=self.photos[-1])

    
    def draw_4val(self):
        if len(self.canvas_list)!=0:
            for canv in self.canvas_list:
                canv.grid_forget()
            self.canvas_list.clear()
        self.photos.clear()
        cell_width = 70;cell_height = 70
        filenames=[['4var','00','01','11','10'],
                   ['00'],
                   ['01'],
                   ['11'],
                   ['10']]
        for i in range(4):
            for j in range(4):
                filenames[i+1].append(str(self.rect_01[i][j]))
        for i in range(5):
            for j in range(5):
                self.canvas_list.append(tk.Canvas(self.frame_right,width=cell_width,height=cell_height))
                self.canvas_list[-1].grid(row=i,column=j)
                img=Image.open(f"source/{filenames[i][j]}.jpg")
                img = img.resize((cell_width, cell_height), Image.ANTIALIAS)
                photo = ImageTk.PhotoImage(img)
                self.photos.append(photo)
                self.canvas_list[-1].create_image(0, 0, anchor=tk.NW, image=self.photos[-1])

    
    def draw_5val(self):
        if len(self.canvas_list)!=0:
            for canv in self.canvas_list:
                canv.grid_forget()
            self.canvas_list.clear()
        self.photos.clear()
        cell_width = 40;cell_height = 40
        filenames=[['5var','000','001','011','010','110','111','101','100'],
                   ['00'],
                   ['01'],
                   ['11'],
                   ['10']]
        for i in range(4):
            for j in range(8):
                filenames[i+1].append(str(self.rect_01[i][j]))
        
        for i in range(5):
            for j in range(9):
                self.canvas_list.append(tk.Canvas(self.frame_right,width=cell_width,height=cell_height))
                self.canvas_list[-1].grid(row=i,column=j)
                img=Image.open(f"source/{filenames[i][j]}.jpg")
                img = img.resize((cell_width, cell_height), Image.ANTIALIAS)
                photo = ImageTk.PhotoImage(img)
                self.photos.append(photo)
                self.canvas_list[-1].create_image(0, 0, anchor=tk.NW, image=self.photos[-1])
    def infoBtn_click(self):
        tkmsg.showinfo(title='注意:',message='只有字母与字母之间的 * 可以省略\n以下表达式视为不合法:\nA(CD+B)\n(A+B)(C+D)\n合法输入:\nA*(CD+B)\n(A+B)*(C+D)')
    def signBtn_click(self):
        tkmsg.showinfo(title="数字签名",message="作业：卡诺图化简\n课程：数字电子技术\n教师：钱强\n姓名：彭羽轩\n班级：2222017011\n学号：222241807223")
    def charButton_click(self,event):
        cButton=event.widget
        if cButton['state']=="disabled":
            return
        i1,i2=int(cButton.grid_info()['row'])-1,int(cButton.grid_info()['column'])
        self.input_line['text']=self.input_line['text']+self.char_on_ui[i1][i2]
        self.fact_str.append((i1,i2))

    def resetButton_click(self,event):
        self.input_line['text']=''
        self.fact_str=[]

    def submitButton_click(self,event):
        char_list=[]
        for i1,i2 in self.fact_str:
            char_list.append(self.char_fact[i1][i2])
        tmp=''.join(char_list)
        slist=tmp.split()
        print(slist)
        if not anal.vaild(slist):
            tkmsg.showerror("error","表达式不合法")
        else:
            mydim=self.dim_val.get()
            self.rect_01=anal.solve(slist,mydim)
            print(self.rect_01)
            if mydim==3:
                self.draw_3val()
            elif mydim==4:
                self.draw_4val()
            elif mydim==5:
                self.draw_5val()
            slist,cords=algo.solve(self.rect_01,mydim)
            self.fill_grid_color(cords,mydim)
            self.show_res(slist)

    def fill_grid_color(self,cords,dim):
        self.color_cnt=0
        for cord in cords:
            for r,c in cord:
                idx=0
                if dim==3:
                    idx=(r+1)*5+(c+1)
                elif dim==4:
                    idx=(r+1)*5+(c+1)
                elif dim==5:
                    idx=(r+1)*9+(c+1)
                self.fill_cell_color(self.canvas_list[idx])
            self.color_cnt+=1

    def fill_cell_color(self,canvas):
        rows=4
        cols=4
        cell_idx=self.color_cnt
        cell_height = canvas.winfo_reqheight() // rows
        cell_width = canvas.winfo_reqwidth() // cols
        row = cell_idx // cols
        col = cell_idx % cols
        x1 = col * cell_width
        y1 = row * cell_height
        x2 = x1 + cell_width
        y2 = y1 + cell_height
        canvas.create_rectangle(x1, y1, x2, y2, fill=self.colors[self.color_cnt%16], outline="black",stipple="gray50")

    def show_res(self,slist):
        res=''
        for ss in slist:
            for ch in ss:
                if ch in ['a','b','c','d','e']:
                    res+=ch.upper()+'`'
                else:
                    res+=ch
            res+='+'
        self.result_label['text']=res[0:-1]

    def backButton_click(self,event):
        end_char=self.input_line['text'][-1]
        self.fact_str.pop()
        if end_char=='`':
            self.input_line['text']=self.input_line['text'][0:-2]
        else:
            self.input_line['text']=self.input_line['text'][0:-1]

    def dim_select(self):
        dval=self.dim_val.get()
        self.input_line['text']=''
        self.fact_str=[]
        for i in range(2):
            for j in range(5):
                if j<dval:
                    self.cbtn_mat[i][j].config(state='active')
                else:
                    self.cbtn_mat[i][j].config(state='disabled')
