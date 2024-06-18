import tkinter as tk
from tkinter import ttk, scrolledtext, IntVar, DoubleVar, Label, Frame
from ttkthemes import ThemedTk
import datetime
from processManager import ProcessManager
from configuratorManager import ConfiguratorManager, Config
import time

class App:
    def __init__(self, root):
        self.root = root
        self.config = Config()
        self.process_managers = []
        self.output_texts = []
        self.is_running = False

        root.columnconfigure(0, weight=1)
        for i in range(1, 4):
            root.columnconfigure(i, weight=3)

        ttk.Label(root, text="Configuration", font=("Helvetica", 12, "bold")).grid(row=0, column=0, sticky="ew")
        # Create a dictionary to store the process manager and button states for each process
        self.process_states = {"SERVER": {"pm": None, "running": False},
                               "GUI": {"pm": None, "running": False},
                               "AI": {"pm": None, "running": False}}

        # Modified loop to add Start/Stop buttons
        for i, name in enumerate(["SERVER", "GUI", "AI"]):
            ttk.Label(root, text=name, font=("Helvetica", 12, "bold")).grid(row=0, column=i+1, sticky="ew")

            # Create MAIN frame to hold both buttons and output
            process_frame = ttk.Frame(root)
            process_frame.grid(row=1, column=i+1, sticky="nsew", padx=5, pady=5)  # Added padding for aesthetics

            # Create button frame INSIDE the main frame
            button_frame = ttk.Frame(process_frame)
            button_frame.pack(fill=tk.X, pady=(5, 0))

            # Create Start/Stop buttons
            start_button = ttk.Button(button_frame, text="Start", command=lambda n=name: self.start_process(n))
            start_button.pack(side=tk.LEFT)
            stop_button = ttk.Button(button_frame, text="Stop", command=lambda n=name: self.stop_process(n), state=tk.DISABLED)
            stop_button.pack(side=tk.LEFT)

            # Store button states
            self.process_states[name]["start_button"] = start_button
            self.process_states[name]["stop_button"] = stop_button

            # Create the scrolled text area INSIDE the main frame
            output_text = scrolledtext.ScrolledText(process_frame, width=30, height=15, fg='white', bg='black', insertbackground='white')
            output_text.pack(fill=tk.BOTH, expand=True)  # Allow text area to fill the frame
            self.output_texts.append(output_text)

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

        # for i in range(3):
        #     output_text = scrolledtext.ScrolledText(root, width=30, height=15, fg='white', bg='black', insertbackground='white')
        #     output_text.grid(row=1, column=i+1, sticky="nsew")
        #     self.output_texts.append(output_text)

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

    # Start a single process based on the name
    def start_process(self, name):
        if not self.process_states[name]["running"]:
            self.config.update(
                self.use_refServer_var.get(),
                self.use_refGui_var.get(),
                self.width_var.get(),
                self.height_var.get(),
                self.starting_egg_var.get(),
                self.f_scale_var.get()
            )
            cm = ConfiguratorManager(self.config)
            command = cm.get_commands()[["SERVER", "GUI", "AI"].index(name)].split()

            pm = ProcessManager(command)
            pm.start_process()
            self.process_states[name]["pm"] = pm
            self.process_states[name]["running"] = True

            self.process_states[name]["start_button"].state(['disabled'])
            self.process_states[name]["stop_button"].state(['!disabled'])

    # Stop a single process based on the name
    def stop_process(self, name):
        if self.process_states[name]["running"]:
            self.process_states[name]["pm"].stop_process()
            self.process_states[name]["pm"] = None
            self.process_states[name]["running"] = False

            self.process_states[name]["start_button"].state(['!disabled'])
            self.process_states[name]["stop_button"].state(['disabled'])

    def update_outputs(self):
        for i, name in enumerate(["SERVER", "GUI", "AI"]):
            if self.process_states[name]["pm"]:
                output = self.process_states[name]["pm"].get_output()
                if output:
                    self.output_texts[i].insert(tk.END, output)
                    self.output_texts[i].see(tk.END)
                errors = self.process_states[name]["pm"].get_errors()
                if errors:
                    self.output_texts[i].insert(tk.END, errors)
                    self.output_texts[i].see(tk.END)
        self.root.after(1, self.update_outputs) 

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
                time.sleep(5)

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
