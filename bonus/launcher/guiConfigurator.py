from tkinter import ttk, IntVar
from configuratorManager import ConfiguratorManager, Config
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from app import App

class GUIConfigurator:
    """
    Wrapper around the configuration columns for the launcher
    """
    
    def __init__(self, root: ttk.Frame, app: "App") -> None:
        """
        Initialize the GUIConfigurator object.

        Args:
            root (ttk.Frame): The root frame of the GUI.
            app (App): The main application object.
        """
        self.root = root
        self.config = Config()
        self.use_refServer_var = IntVar(value=0)
        self.use_refGui_var = IntVar(value=0)
        self.width_var = IntVar(value=10)
        self.height_var = IntVar(value=10)
        self.starting_egg_var = IntVar(value=1)
        self.f_scale_var = IntVar(value=100)
        self.teams_var = IntVar(value=2)
        self.app: "App" = app


        ttk.Label(root, text="Configuration", font=("Helvetica", 12, "bold")).grid(row=0, column=0, sticky="ew")
        
        self.config_frame = ttk.Frame(root)
        self.config_frame.grid(row=1, column=0, sticky="nsew")
        self.root.rowconfigure(1, weight=1)

        self.setup_config_widgets()

    def setup_config_widgets(self) -> None:
        """
        Set up the configuration widgets in the GUI.
        """
        ttk.Checkbutton(self.config_frame, text="Use Ref Server", variable=self.use_refServer_var).grid(row=1, column=0, sticky="w")
        ttk.Checkbutton(self.config_frame, text="Use Ref GUI", variable=self.use_refGui_var).grid(row=2, column=0, sticky="w")
        self.create_slider("Width", self.width_var, 3, 10, 100)
        self.create_slider("Height", self.height_var, 6, 10, 100)
        self.create_slider("Starting Egg", self.starting_egg_var, 9, 1, 10)
        self.create_slider("F Scale", self.f_scale_var, 12, 2, 100)
        self.create_slider("Teams", self.teams_var, 15, 1, 10)

        ttk.Button(self.config_frame, text="Clear Output", command=self.app.clear_output).grid(row=18, column=0, sticky="ew")
        ttk.Button(self.config_frame, text="Save Output", command=self.app.save_output).grid(row=19, column=0, sticky="ew")

    def create_slider(self, label: str, var: IntVar, start_row: int, min: int, max: int) -> None:
        """
        Create a slider widget in the GUI.

        Args:
            label (str): The label for the slider.
            var (IntVar): The variable to store the slider value.
            start_row (int): The starting row for the slider in the grid.
            min (int): The minimum value of the slider.
            max (int): The maximum value of the slider.
        """
        ttk.Label(self.config_frame, text=label).grid(row=start_row, column=0, sticky="w")
        slider = ttk.Scale(self.config_frame, from_=min, to=max, orient="horizontal", variable=var,
                        command=lambda v, l=label, var=var: self.update_slider_label(l, var))
        slider.grid(row=start_row + 1, column=0, sticky="ew")
        value_label = ttk.Label(self.config_frame, text=f"{var.get():.0f}")
        value_label.grid(row=start_row + 2, column=0, sticky="w")
        setattr(self, f"{label.lower()}_value_label", value_label)
    
    def update_slider_label(self, label: str, var: IntVar) -> None:
        """
        Update the label of a slider widget.

        Args:
            label (str): The label of the slider.
            var (IntVar): The variable storing the slider value.
        """
        getattr(self, f"{label.lower()}_value_label").config(text=f"{var.get():.0f}")
    
    def get_commands(self) -> list[str]:
        """
        Get the configuration commands.

        Returns:
            list[str]: The list of configuration commands.
        """
        self.config.update(self.use_refServer_var.get(), self.use_refGui_var.get(),
                        self.width_var.get(), self.height_var.get(),
                        self.starting_egg_var.get(), self.f_scale_var.get(),
                        self.teams_var.get())
        return ConfiguratorManager(self.config).get_commands()
