import tkinter as tk
import isomerNum as iso
win = tk.Tk()
win.title("有机物同分异构体数目计算展示平台")
tk.Label(win, text="C").grid(row=1, column=1)
numC = tk.Entry(win, width=5)
numC.grid(row=1, column=2)
tk.Label(win, text="H").grid(row=1, column=3)
numH = tk.Entry(win, width=5)
numH.grid(row=1, column=4)

def begin():
    numOfC = int(numC.get())
    numOfH = int(numH.get())
    if numOfH == 2*numOfC + 2:
        tk.Label(win, text=iso.alkane(numOfC)).grid(row=3, column=1)

submit = tk.Button(win, text="开始计算", command=begin)
submit.grid(row=2, column=1, columnspan=3)

win.mainloop()
