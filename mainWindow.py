import tkinter as tk
from rdkit import Chem
from rdkit.Chem import Draw
from isomerNum import quickCount
from isomerNum import listAll
root = tk.Tk()
root.geometry("500x400")
root.title('同分异构体计算')
root.configure(bg='Beige')
l1 = tk.Label(root,text='( ੭ ˙ᗜ˙ )੭请在下框中输入分子式',font=("Times",12),width=25,height=2,bg='Beige')
l1.place(x=250,y=140,anchor='center')
e = tk.Entry(root,show=None,width=34)
e.place(x=195,y=180,anchor='center')
def hit1():
    global R1
    R1 = tk.messagebox.askquestion(title='设置',message='你是否只需要得到同分异构体的数目（目前仅提供烯烃，炔烃，醚,以及单取代基的结构）')
    var1=e.get()
    m = len(var1)
    for i in range(0,m):
        if var1[i] == 'H':
           j = i
    n = int(var1[1:j])
    if n < 4:
        H = int(var1[3])
    else:
        H = int(var1[j+1:j+3])
    test1 = 'OK'
    substitude = ['F','l','B','I']
    for y in range(0,m):
        if var1[y] in substitude:
            if H != 2*n + 1: 
                test1 = 'NO'
        else:
            test1 = 'OK'
        if var1[y] == 'O':
            if H != 2*n + 2: 
                test1 = 'NO'
        else:
            test1 = 'OK'
    if test1 == 'OK':
        global R2,R3
        if R1 == 'yes':
            if H == 2*n:
                R2 = (f"单环烷烃共有：{quickCount.cycloAlk(n)}")+(f"单烯烃共有：{quickCount.alkene(n)}")
            elif H == 2*n + 2:
                if var1[-1] == 'O':
                    R2 = (f"醚共有：{quickCount.monoAlkene(n)}") + (f"醇共有：{quickCount.alkyl(n)}")
                else:
                    R2 = quickCount.alkane(n)
            else:
                if H == 2*n - 2:
                    R2 = (f"炔烃共有：{quickCount.alkyl(n-2) + quickCount.monoAlkene(n-2)}")
                else:
                    R2 = quickCount.alkyl(n)
        else:
            if H == 2*n:
                R2 = listAll.lsAlkenes(n)
                R3 = R2
            elif H == 2*n - 2:
                R2 = listAll.lsMonosub(n-2,'C≡C') + listAll.lsAlkene(n-2,'C≡C')
                R3 = listAll.lsMonosub(n-2,'C#C') + listAll.lsAlkene(n-2,'C#C')
            else:
                if H == 2*n + 2:
                    R2 = listAll.lsAlkene(n,'O') + listAll.lsMonosub(n,'OH')
                    R3 = listAll.lsAlkene(n,'O') + listAll.lsMonosub(n,'O')
                else:
                    w = var1[-2:]
                    R2 = listAll.lsMonosub(n,w)
                    R3 = R2
        t.insert('end',R2) 
    else:
        t.insert('end','分子式好像有些错误呢π_π，再重新输入一个吧')
b1 = tk.Button(root,text='结果',bg='Plum',font=('Arial',10),width=6,height=1,command=hit1)
b1.place(x=345,y=180,anchor='center')
def clearbox():
    t.delete('1.0','end')
b4 = tk.Button(root,text='清空',bg = 'Plum',font=('Arial',10),width=6,height=1,command = clearbox)
b4.place(x=400,y=180,anchor='center')
t = tk.Text(root,width=50,height=5)
t.place(x=250,y=240,anchor='center')
def hit2():
    smi = (".".join(str(x) for x in R3))
    m = Chem.MolFromSmiles(smi) 
    root.destroy()
    Draw.ShowMol(m,size=(600,600),kekulize=False)
b3 = tk.Button(text = '结构展示',bg='Plum',font=("Arial",14),width=14,height=1,command=hit2)
b3.place(x=250,y=350,anchor='center')
l2 = tk.Label(root,text='同分异构计算',font=("Times",32),fg='purple',width=40,height=1,bg='Beige')
l2.place(x=250,y=60,anchor='center')
l3 = tk.Label(root,text='一起来试试看吧(=^_^=)',font=("Times",10),fg='purple',width=40,height=1,bg='Beige')
l3.place(x=250,y=90)
l4 = tk.Label(root,text='嗯？听说有人还需要结构图',font=("Times",12),width=40,height=1,bg='Beige')
l4.place(x=250,y=310,anchor='center')
canvas1 = tk.Canvas(root,height=40,width=100,bg='Beige')
image_file1 = tk.PhotoImage(file='./nku.gif')
image = canvas1.create_image(50,20,image=image_file1)
canvas1.place(x=60,y=25,anchor='center')
canvas2 = tk.Canvas(root,height=90,width=90,bg='Beige')
image_file2 = tk.PhotoImage(file='./little.gif')
image = canvas2.create_image(50,50,anchor='center',image=image_file2)
canvas2.place(x=100,y=330,anchor='center')
canvas3 = tk.Canvas(root,height=90,width=90,bg='Beige')
image_file3 = tk.PhotoImage(file='./little.gif')
image = canvas3.create_image(50,50,anchor='center',image=image_file3)
canvas3.place(x=400,y=330,anchor='center')
root.mainloop()
