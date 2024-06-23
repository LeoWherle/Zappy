import tkinter as tk
from tkinter import ttk, scrolledtext
import datetime
from processManager import ProcessManager
from typing import List, TYPE_CHECKING

if TYPE_CHECKING:
    from app import App

class GUIProcessManager:
    """
    A class representing the GUI process manager.

    Args:
        root (tk.Tk): The root Tkinter window.
        name (str): The name of the process manager.
        row (int): The row position of the process manager.
        app (App): The instance of the App class.

    Attributes:
        root (tk.Tk): The root Tkinter window.
        name (str): The name of the process manager.
        row (int): The row position of the process manager.
        pm (ProcessManager | None): The instance of the ProcessManager class.
        running (bool): Indicates whether the process is running or not.
        command (List[str] | None): The command to start the process.
        app (App): The instance of the App class.
        start_button (ttk.Button): The button to start the process.
        stop_button (ttk.Button): The button to stop the process.
        output_text (scrolledtext.ScrolledText): The text widget to display the process output.
    """

    def __init__(self, root: tk.Tk, name: str, row: int, app: "App") -> None:
        """
        Initializes the GUIProcessManager instance.

        Args:
            root (tk.Tk): The root Tkinter window.
            name (str): The name of the process manager.
            row (int): The row position of the process manager.
            app (App): The instance of the App class.
        """
        self.root: tk.Tk = root
        self.name: str = name
        self.row: int = row
        self.pm: ProcessManager | None = None
        self.running: bool = False
        self.command: List[str] | None = None
        self.app: "App" = app

        ttk.Label(root, text=name, font=("Helvetica", 12, "bold")).grid(row=0, column=row, sticky="ew")

        process_frame: ttk.Frame = ttk.Frame(root)
        process_frame.grid(row=1, column=row, sticky="nsew", padx=5, pady=5)

        button_frame: ttk.Frame = ttk.Frame(process_frame)
        button_frame.pack(fill=tk.X, pady=(5, 0))

        self.start_button: ttk.Button = ttk.Button(button_frame, text="Start", command=self.start_process)
        self.start_button.pack(side=tk.LEFT)
        self.stop_button: ttk.Button = ttk.Button(button_frame, text="Stop", command=self.stop_process, state=tk.DISABLED)
        self.stop_button.pack(side=tk.LEFT)

        self.create_output_text(process_frame)

    def create_output_text(self, process_frame: ttk.Frame) -> None:
        """
        Creates the output text widget.

        Args:
            process_frame (ttk.Frame): The frame to contain the output text widget.
        """
        self.output_text: scrolledtext.ScrolledText = scrolledtext.ScrolledText(process_frame, width=30, height=15, fg='white', bg='black', insertbackground='white')
        self.output_text.pack(fill=tk.BOTH, expand=True)

    def start_process(self) -> None:
        """
        Starts the process.
        """
        self.command = self.app.configurator.get_commands()[self.row-1].split()
        print(f"Starting {self.name} with command: {self.command}")
        if not self.running:
            self.pm = ProcessManager(self.command)
            self.pm.start_process()
            self.running = True

            self.start_button.state(['disabled'])
            self.stop_button.state(['!disabled'])

    def stop_process(self) -> None:
        """
        Stops the process.
        """
        if self.running:
            self.pm.stop_process()
            self.pm = None
            self.running = False

            self.start_button.state(['!disabled'])
            self.stop_button.state(['disabled'])
    
    def update_output(self) -> None:
        """
        Updates the output text widget with the process output and errors.
        """
        if self.pm:
            output: str = self.pm.get_output()
            if output:
                self.output_text.insert(tk.END, output)
                self.output_text.see(tk.END)
            errors: str = self.pm.get_errors()
            if errors:
                self.output_text.insert(tk.END, errors)
                self.output_text.see(tk.END)

    def clear_output(self) -> None:
        """
        Clears the output text widget.
        """
        self.output_text.delete("1.0", tk.END)

    def save_output(self) -> None:
        """
        Saves the output text to a file.
        """
        now: datetime.datetime = datetime.datetime.now()
        filename: str = f"zappy_{self.name}_{now.strftime('%Y%m%d_%H%M%S')}.log"
        with open(filename, "w") as file:
            file.write(self.output_text.get("1.0", tk.END))
        print(f"Output saved to {filename}")
