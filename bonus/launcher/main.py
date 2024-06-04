import tkinter as tk
from tkinter import ttk, scrolledtext, IntVar, DoubleVar, Label, Frame
from ttkthemes import ThemedTk
import datetime
from processManager import ProcessManager
from configuratorManager import ConfiguratorManager, Config

class App:
    def __init__(self, root):
        self.root = root
        self.config = Config()
        self.process_managers = []
        self.is_running = False

        root.columnconfigure(0, weight=1)
        for i in range(1, 4):
            root.columnconfigure(i, weight=3)

        ttk.Label(root, text="Configuration", font=("Helvetica", 12, "bold")).grid(row=0, column=0, sticky="ew")
        for i, name in enumerate(["SERVER", "GUI", "AI"]):
            ttk.Label(root, text=name, font=("Helvetica", 12, "bold")).grid(row=0, column=i+1, sticky="ew")

        config_frame = ttk.Frame(root)
        config_frame.grid(row=1, column=0, sticky="nsew")
        root.rowconfigure(1, weight=1)

        self.use_refServer_var = IntVar(value=0)
        self.use_refGui_var = IntVar(value=0)
        self.width_var = IntVar(value=10)
        self.height_var = IntVar(value=10)
        self.starting_egg_var = IntVar(value=6)
        self.f_scale_var = IntVar(value=100)

        self.setup_config_widgets(config_frame)

        self.output_texts = []
        for i in range(3):
            output_text = scrolledtext.ScrolledText(root, width=30, height=15, fg='white', bg='black', insertbackground='white')
            output_text.grid(row=1, column=i+1, sticky="nsew")
            self.output_texts.append(output_text)

        self.update_outputs()

    def setup_config_widgets(self, frame):
        ttk.Checkbutton(frame, text="Use Ref Server", variable=self.use_refServer_var).grid(row=1, column=0, sticky="w")
        ttk.Checkbutton(frame, text="Use Ref GUI", variable=self.use_refGui_var).grid(row=2, column=0, sticky="w")
        self.create_slider(frame, "Width", self.width_var, 3, 1, 100)
        self.create_slider(frame, "Height", self.height_var, 6, 1, 100)
        self.create_slider(frame, "Starting Egg", self.starting_egg_var, 9, 1, 10)
        self.create_slider(frame, "F Scale", self.f_scale_var, 12, 2, 300)

        self.start_button = ttk.Button(frame, text="Start All", command=self.start_all_processes)
        self.start_button.grid(row=15, column=0, sticky="ew", pady=(10, 0))
        self.stop_button = ttk.Button(frame, text="Stop All", command=self.stop_all_processes, state=tk.DISABLED)
        self.stop_button.grid(row=16, column=0, sticky="ew")
        ttk.Button(frame, text="Clear Output", command=self.clear_output).grid(row=17, column=0, sticky="ew")
        ttk.Button(frame, text="Save Output", command=self.save_output).grid(row=18, column=0, sticky="ew")

    def update_outputs(self):
        for i, pm in enumerate(self.process_managers):
            output = pm.get_output()
            if output:
                self.output_texts[i].insert(tk.END, output)
            errors = pm.get_errors()
            if errors:
                self.output_texts[i].insert(tk.END, errors)
        self.root.after(100, self.update_outputs)

    def start_all_processes(self):
        if not self.is_running:
            self.is_running = True
            self.start_button.state(['disabled'])
            self.stop_button.state(['!disabled'])
            self.config.update(
                self.use_refServer_var.get(),
                self.use_refGui_var.get(),
                self.width_var.get(),
                self.height_var.get(),
                self.starting_egg_var.get(),
                self.f_scale_var.get()
            )
            cm = ConfiguratorManager(self.config)
            commands = cm.get_commands()
            for command in commands:
                pm = ProcessManager(command.split())
                pm.start_process()
                self.process_managers.append(pm)

    def stop_all_processes(self):
        if self.is_running:
            for pm in self.process_managers:
                pm.stop_process()
            self.process_managers = []
            self.is_running = False
            self.start_button.state(['!disabled'])
            self.stop_button.state(['disabled'])

    def create_slider(self, frame, label, var, start_row, min, max):
        ttk.Label(frame, text=label).grid(row=start_row, column=0, sticky="w")
        slider = ttk.Scale(frame, from_=min, to=max, orient="horizontal", variable=var,
                           command=lambda v, l=label, var=var: self.update_slider_label(l, var))
        slider.grid(row=start_row + 1, column=0, sticky="ew")
        value_label = ttk.Label(frame, text=f"{var.get():.0f}")
        value_label.grid(row=start_row + 2, column=0, sticky="w")
        setattr(self, f"{label.lower()}_value_label", value_label)

    def update_slider_label(self, label, var):
        getattr(self, f"{label.lower()}_value_label").config(text=f"{var.get():.0f}")

    def clear_output(self):
        for text_widget in self.output_texts:
            text_widget.delete("1.0", tk.END)

    def save_output(self):
        now = datetime.datetime.now()
        fnames = ["server", "gui", "ai"]
        for i, text_widget in enumerate(self.output_texts):
            content = text_widget.get("1.0", tk.END)
            filename = f"zappy_{fnames[i]}_{now.strftime('%Y%m%d_%H%M%S')}.log"
            with open(filename, "w") as file:
                file.write(content)
            print(f"Output saved to {filename}")

if __name__ == "__main__":
    root = ThemedTk(theme="equilux")
    root.title("Zappy Launcher")
    root.geometry("1000x600")
    app = App(root)
    root.mainloop()
