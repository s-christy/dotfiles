import Tkinter as tk
import sys
import alsaaudio

m=alsaaudio.Mixer()

def setvol(event):
    print(w.get())
    m.setvolume(w.get())


root=tk.Tk()
w=tk.Scale(root,from_=0, to=100, orient=tk.HORIZONTAL,command=setvol)
w.configure(length=1000)
w.pack()

def close(event):
    sys.exit()

root.bind('<Escape>', close)

root.mainloop()
