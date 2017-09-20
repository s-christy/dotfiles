
from gi.repository import Gtk

class Main(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="title")
        self.button=Gtk.Button(label="Button")
        self.button.connect("clicked",self.click)
        self.add(self.button)
    def click(self, widget):
        print("test")

window=Main()
window.connect("delete-event", Gtk.main_quit)
window.show_all()
Gtk.main()

