""" Main file for the Zappy Launcher. """

from ttkthemes import ThemedTk

from app import App

if __name__ == "__main__":
    root: ThemedTk = ThemedTk(theme="equilux")
    root.title("Zappy Launcher")
    root.geometry("1000x600")
    app: App = App(root)
    root.mainloop()
