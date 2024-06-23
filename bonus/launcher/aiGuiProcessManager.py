""" This module contains the AIGUIProcessManager class. """

import tkinter as tk
from tkinter import ttk, scrolledtext
import datetime
from processManager import ProcessManager
from typing import List, TYPE_CHECKING

if TYPE_CHECKING:
    from app import App

class AIGUIProcessManager:
    """
    A class representing the GUI process manager for AI.

    Attributes:
        root (tk.Tk): The root Tkinter window.
        name (str): The name of the process manager.
        row (int): The row position of the process manager.
        app (App): The main application instance.
        pms (List[ProcessManager]): List of process managers.
        running (bool): Indicates if the process is running.
        start_button (ttk.Button): The Start button.
        stop_button (ttk.Button): The Stop button.
        outputmain_frame (ttk.Frame): The main frame for output texts.
        output_frames (List[ttk.Frame]): List of output frames.
        output_texts (List[scrolledtext.ScrolledText]): List of output text widgets.
    """

    def __init__(self, root: tk.Tk, name: str, row: int, app: "App") -> None:
        """
        Initialize the AIGUIProcessManager.

        Args:
            root (tk.Tk): The root Tkinter window.
            name (str): The name of the process manager.
            row (int): The row position of the process manager.
            app (App): The main application instance.
        """
        self.root: tk.Tk = root
        self.name: str = name
        self.row: int = row
        self.pms: List[ProcessManager] = []
        self.running: bool = False
        self.app: "App" = app

        ttk.Label(root, text=name, font=("Helvetica", 12, "bold")).grid(row=0, column=row, sticky="ew")

        # Create MAIN frame to hold both buttons and output
        self.process_frame: ttk.Frame = ttk.Frame(root)
        self.process_frame.grid(row=1, column=row, sticky="nsew", padx=5, pady=5)

        # Create button frame INSIDE the main frame
        button_frame: ttk.Frame = ttk.Frame(self.process_frame)
        button_frame.pack(fill=tk.X, pady=(5, 0))

        # Create Start/Stop buttons
        start_button: ttk.Button = ttk.Button(button_frame, text="Start", command=self.start_process)
        start_button.pack(side=tk.LEFT)
        stop_button: ttk.Button = ttk.Button(button_frame, text="Stop", command=self.stop_process, state=tk.DISABLED)
        stop_button.pack(side=tk.LEFT)

        # Store button states
        self.start_button: ttk.Button = start_button
        self.stop_button: ttk.Button = stop_button

        self.create_output_text()

    def create_output_text(self) -> None:
        """
        Create the output text widgets.
        """
        self.output_texts = []
        self.outputmain_frame = ttk.Frame(self.process_frame)
        self.outputmain_frame.pack(fill=tk.BOTH, expand=True)
        self.output_frames = []

        self.populate_output_texts()

    def populate_output_texts(self) -> None:
        """
        Populate the output text widgets.
        """
        self.teams_count = self.app.configurator.teams_var.get()

        for i in range(self.teams_count):
            output_frame = ttk.Frame(self.outputmain_frame)
            output_frame.grid(row=i, column=0, sticky='nsew')

            output_text = scrolledtext.ScrolledText(output_frame, width=30, fg='white', bg='black', insertbackground='white')
            output_text.pack(fill=tk.BOTH, expand=True)

            self.output_texts.append(output_text)
            self.output_frames.append(output_frame)

            self.outputmain_frame.grid_rowconfigure(i, weight=1)

        self.outputmain_frame.grid_columnconfigure(0, weight=1)

        for i in range(self.teams_count):
            self.outputmain_frame.grid_rowconfigure(i, weight=1)

    def start_process(self) -> None:
        """
        Start the process.
        """
        command: str = self.app.configurator.get_commands()[self.row-1]
        # for each team, replace "team" by "team1", "team2"
        for i in range(self.app.configurator.teams_var.get()):
            temp_cmd = command.replace("team", f"team{i+1}")
            print(f"Starting {self.name} with command: {temp_cmd}")
            pm = ProcessManager(temp_cmd.split())
            pm.start_process()
            self.pms.append(pm)
        self.running = True

        self.start_button.state(['disabled'])
        self.stop_button.state(['!disabled'])

    def stop_process(self) -> None:
        """
        Stop the process.
        """
        if self.running:
            for pm in self.pms:
                pm.stop_process()
            self.pms = []
            self.running = False

            self.start_button.state(['!disabled'])
            self.stop_button.state(['disabled'])

    def update_output(self) -> None:
        """
        Update the output text widgets.
        """
        for i, pm in enumerate(self.pms):
            output = pm.get_output()
            if output:
                self.output_texts[i].insert(tk.END, output)
                self.output_texts[i].see(tk.END)
            errors = pm.get_errors()
            if errors:
                self.output_texts[i].insert(tk.END, errors)
                self.output_texts[i].see(tk.END)

    def clear_output(self) -> None:
        """
        Clear the output text widgets.
        """
        for text in self.output_texts:
            text.delete("1.0", tk.END)

    def save_output(self) -> None:
        """
        Save the output to a file.
        """
        now = datetime.datetime.now()
        for i, text in enumerate(self.output_texts):
            filename = f"zappy_{self.name}_team{i+1}_{now.strftime('%Y%m%d_%H%M%S')}.log"
            with open(filename, "w") as file:
                file.write(text.get("1.0", tk.END))
            print(f"Output saved to {filename}")

    def update_team_count(self, count: int) -> None:
        """
        Update the team count.

        Args:
            count (int): The new team count.
        """
        if self.teams_count == count:
            return
        self.teams_count = count

        # Clear the existing frames and text widgets
        for frame in self.output_frames:
            frame.destroy()
        for text in self.output_texts:
            text.destroy()

        self.outputmain_frame.destroy()
        self.outputmain_frame = ttk.Frame(self.process_frame)
        self.outputmain_frame.pack(fill=tk.BOTH, expand=True)

        self.output_texts.clear()
        self.output_frames.clear()

        # Repopulate the frames and text widgets with the new team count
        self.populate_output_texts()
