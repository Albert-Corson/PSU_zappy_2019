import collections

class Trantorian:
    x, y = 0, 0
    life_unit = 126
    player_gathered = 0
    level = 1
    stones = { "linemate": 0, "deraumere": 0, "sibur": 0,
                "mendiane": 0, "phiras": 0, "thystame": 0 }
    elev_table = [
        [1, 1, 0, 0, 0, 0, 0],
        [2, 1, 1, 1, 0, 0, 0],
        [2, 2, 0, 1, 0, 2, 0],
        [4, 1, 1, 2, 0, 1, 2],
        [4, 1, 2, 1, 3, 0, 0],
        [6, 1, 2, 3, 0, 1, 0],
        [6, 2, 2, 2, 2, 2, 1],
    ]

    def __init__(self, name):
        print("A Trantorian has been invoked")
        self.name = name

    def collect_stone(self, stone):
        if stone in self.stones:
            print(self.name + " just picked up a " + stone + " stone!")
            self.stones[stone] += 1
        else:
            print("Dunno this stone, duh..")

    vision = {1: "", 2: "", 3: ""};

    def upgrade_vision(self):
        upgrades = len(self.vision) + 2;

        for i in range(len(self.vision), upgrades):
            self.vision.update({i: ""})

    def command_interpreter(self, command): # look command especially
        #[player,,,thystame,,food,,,,,,foo,,,]
        vision_limit = len(self.vision)

    def dump_stone(self):
        print("### Stone recap ###\n")
        [print("# [" + x + "]" + ":\t%d  #" %(self.stones[x])) for x in self.stones]
        print("\n### end ###")

    def reset_stones(self):
        for _ in self.stones:
            self.stones[_] = 0

    def check_ressources(self):
        actual_state = [self.player_gathered] + list(self.stones.values())
        require_state = self.elev_table[self.level - 1]
        if collections.Counter(actual_state) == collections.Counter(require_state):
            print("All ressources are reunited")
            self.elevate()

    def elevate(self):
        print("Ritual begins...")
        self.level += 1
        self.upgrade_vision()
        print("Now elevating to %d" %(self.level))
