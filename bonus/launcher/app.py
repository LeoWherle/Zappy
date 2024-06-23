from typing import List, Dict
from guiConfigurator import GUIConfigurator
from aiGuiProcessManager import AIGUIProcessManager
from guiProcessManager import GUIProcessManager
from tkinter import Tk

class App:
    """
    Represents the main application.

    Args:
        root (Tk): The root Tkinter object.

    Attributes:
        root (Tk): The root Tkinter object.
        process_managers (List[GUIProcessManager]): List of GUI process managers.
        is_running (bool): Flag indicating if the application is running.
        process_states (Dict[str, Dict[str, bool]]): Dictionary containing the states of different processes.
        configurator (GUIConfigurator): The GUI configurator object.

    Methods:
        update_outputs: Updates the outputs of the process managers.
        clear_output: Clears the output of the process managers.
        save_output: Saves the output of the process managers.
    """

    def __init__(self, root: Tk) -> None:
        """
        Initializes the App object.

        Args:
            root (Tk): The root Tkinter object.
        """
        self.root: Tk = root
        self.process_managers: List[GUIProcessManager] = []
        self.is_running: bool = False

        root.columnconfigure(0, weight=1)
        for i in range(1, 4):
            root.columnconfigure(i, weight=3)

        self.process_states: Dict[str, Dict[str, bool]] = {
            "SERVER": {"pm": None, "running": False},
            "GUI": {"pm": None, "running": False},
            "AI": {"pm": None, "running": False}
        }

        for i, name in enumerate(["SERVER", "GUI"]):
            self.process_managers.append(GUIProcessManager(root, name, i+1, self))
        self.configurator: GUIConfigurator = GUIConfigurator(root, self)
        self.process_managers.append(AIGUIProcessManager(root, "AI", 3, self))

        self.update_outputs()

    def update_outputs(self) -> None:
        """
        Updates the outputs of the process managers.
        """
        self.process_managers[-1].update_team_count(self.configurator.teams_var.get())
        for pm in self.process_managers:
            pm.update_output()
        self.root.after(1, self.update_outputs) 

    def clear_output(self) -> None:
        """
        Clears the output of the process managers.
        """
        for pm in self.process_managers:
            pm.clear_output()

    def save_output(self) -> None:
        """
        Saves the output of the process managers.
        """
        for pm in self.process_managers:
            pm.save_output()
    
    def stop_app(self) -> None:
        """
        Stops the application.
        """
        for pm in self.process_managers:
            pm.stop_process()
        self.root.quit()
        self.root.destroy()
        self.is_running = False
