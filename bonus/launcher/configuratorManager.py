""" Contains the Config and ConfiguratorManager classes. """

class Config:
    """
    Represents the configuration settings for the Zappy game.
    """

    def __init__(self) -> None:
        self.use_refServer: bool = False
        self.use_refGui: bool = False
        self.width: int = 10
        self.height: int = 10
        self.starting_egg: int = 6
        self.f_scale: int = 100
        self.teams: int = 2

    def update(
        self,
        use_refServer: bool,
        use_refGui: bool,
        width: int,
        height: int,
        starting_egg: int,
        f_scale: int,
        teams: int,
    ) -> None:
        """
        Updates the configuration settings.

        Args:
            use_refServer (bool): Whether to use the reference server.
            use_refGui (bool): Whether to use the reference GUI.
            width (int): The width of the game board.
            height (int): The height of the game board.
            starting_egg (int): The number of starting eggs.
            f_scale (int): The scale factor.
            teams (int): The number of teams.
        """
        self.use_refServer = use_refServer
        self.use_refGui = use_refGui
        self.width = width
        self.height = height
        self.starting_egg = starting_egg
        self.f_scale = f_scale
        self.teams = teams


class ConfiguratorManager:
    """
    Manages the configuration for launching the Zappy game.
    """

    def __init__(self, config: Config) -> None:
        """
        Initializes the ConfiguratorManager.

        Args:
            config (Config): The configuration settings.
        """
        self.config = config

    def get_commands(self) -> list[str]:
        """
        Generates the commands for launching the Zappy game.

        Returns:
            list[str]: The list of commands.
        """
        server_cmd = (
            f"{'.' if not self.config.use_refServer else './tests/ref'} "
            f"./zappy_server -p 4242 -x {self.config.width} -y {self.config.height} "
            f"-c {self.config.starting_egg} -f {self.config.f_scale} "
            f"-n {' '.join([f'team{i + 1}' for i in range(self.config.teams)])} "
            f"{'--spam-gui' if self.config.use_refGui and not self.config.use_refServer else ''}"
        )

        gui_cmd = (
            f"{'.' if not self.config.use_refGui else './tests/ref'} "
            f"./zappy_gui -h 0.0.0.0 -p 4242 "
            f"{'--ref-serv' if self.config.use_refServer and not self.config.use_refGui else ''}"
        )

        ai_cmd = (
            ". "
            "./zappy_ai -h 0.0.0.0 -p 4242 -n team -t -nocolor "
            f"{'-ref' if self.config.use_refServer else ''}"
        )

        return [server_cmd, gui_cmd, ai_cmd]
