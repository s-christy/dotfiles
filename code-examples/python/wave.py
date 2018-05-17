import Tkinter
import math

top = Tkinter.Tk()

c = Tkinter.Canvas(top, bg="#000000", height=1080, width=1920)

colors=[1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,5,5,54,4,4,3]
colors[0]="#000000"
colors[1]="#001100"
colors[2]="#002200"
colors[3]="#003300"
colors[4]="#004400"
colors[5]="#005500"
colors[6]="#006600"
colors[7]="#007700"
colors[8]="#008800"
colors[9]="#009900"
colors[10]="#00aa00"
colors[11]="#00bb00"
colors[12]="#00cc00"
colors[13]="#00dd00"
colors[14]="#00ee00"
colors[15]="#00ff00"

def wave(x):
    wav=math.sin(x/10.0)+math.sin(x/4.0)
    return 20.0*wav+540

def circ(x,y,z):
    i=z
    z=14-z
    z=z/2.0
    c.create_oval(x-z,y-z,x+z,y+z, fill=colors[i], outline="")

for w in range(0,16):
    for x in range(0,1920):
        y1=wave(x)
        y2=wave(x+1)
        circ(x,wave(x),w)

c.pack()
top.mainloop()
