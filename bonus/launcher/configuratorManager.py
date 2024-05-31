class Config:
    def __init__(self):
        self.use_refServer = False
        self.use_refGui = False
        self.width = 10
        self.height = 10
        self.starting_egg = 6

    def update(self, use_refServer, use_refGui, width, height, starting_egg):
        self.use_refServer = use_refServer
        self.use_refGui = use_refGui
        self.width = width
        self.height = height
        self.starting_egg = starting_egg
        self.refwd = "./tests/ref/"


class ConfiguratorManager:
    def __init__(self, config):
        self.config = config

    def get_commands(self):
        server_cmd = (f"{'.' if not self.config.use_refServer else './tests/ref'} ./zappy_server -p 4242"
                      + f" -x {self.config.width} -y {self.config.height} -n team -c {self.config.starting_egg}"
                      + f" {'' if not self.config.use_refGui else '--spam-gui' if not self.config.use_refServer else ''}")
        gui_cmd = f"{'.' if not self.config.use_refGui else './tests/ref'} ./zappy_gui -h 0.0.0.0 -p 4242"
        ai_cmd = f". ./zappy_ai -h 0.0.0.0 -p 4242 -n team -t"

        return [server_cmd, gui_cmd, ai_cmd]
