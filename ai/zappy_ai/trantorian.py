import collections
from enum import Enum, unique
from random import randrange
import socket

@unique
class Direction(Enum):
    NORTH = 0
    EST = 1
    SOUTH = 2
    WEST = 3

class Trantorian:
    # Space stuff 
    direction = Direction.NORTH
    x, y = 0, 0
    map_dimension = {'x': 0, 'y': 0}

    # Time stuff
    life_unit = 10
    time_unit = 1260

    # Player stuff
    food = 0
    player_gathered = 0
    level = 1
    stones = {}
    #stones = { "linemate": 0, "deraumere": 0, "sibur": 0,
    #            "mendiane": 0, "phiras": 0, "thystame": 0 }
    unused_player_slot = 0
    elev_table = [
        [1, 1, 0, 0, 0, 0, 0],
        [2, 1, 1, 1, 0, 0, 0],
        [2, 2, 0, 1, 0, 2, 0],
        [4, 1, 1, 2, 0, 1, 2],
        [4, 1, 2, 1, 3, 0, 0],
        [6, 1, 2, 3, 0, 1, 0],
        [6, 2, 2, 2, 2, 2, 1],
    ]
    vision_field = {1: "empty", 2: "empty", 3: "empty", 4: "empty"} # This is suppose to be the vision of a 1 level trantorian

    def __init__(self, name, sockfd):
        print("A Trantorian has been invoked")
        self.name = name
        self.sockfd = sockfd 

    def randomize_spawn(self):
        self.x = randrange(0, self.map_dimension['x'])
        self.y = randrange(0, self.map_dimension['y'])
        self.direction = randrange(0, 3)

    def set_map_dimension(self, x, y):
        self.map_dimension['x'] = x
        self.map_dimension['y'] = y

    def collect_stone(self, stone):
        if stone in self.stones:
            print(self.name + " just picked up a " + stone + " stone!")
            self.stones[stone] += 1
        else:
            print("Dunno this stone, duh..")

    def upgrade_vision_field(self):
        beg = len(self.vision_field)
        tmp = beg + 2
        end = beg + tmp
        for i in range(beg, end):
            self.vision_field.update({i: "empty"})

    def dump_stone(self):
        print("### Stone recap ###\n")
        [print("# [" + x + "]" + ":\t%d  #" %(self.stones[x])) for x in self.stones]
        print("\n### end ###")

    def reset_stones(self): # prendre en compte les cailloux restant si plus 
        for _ in self.stones:
            self.stones[_] = 0

    def check_ressources(self): # pareil 
        actual_state = [self.player_gathered] + list(self.stones.values())
        require_state = self.elev_table[self.level - 1]
        if collections.Counter(actual_state) == collections.Counter(require_state):
            print("All ressources are reunited")
            return True
        return False

    def send_cmd(self, msg):
        self.sockfd.send(msg.encode("Utf8"))
        response = self.sockfd.recv(1280).decode("Utf8")
        print(response)
        return response # TODO: maybe usefull later

    def incantation(self):
        response = self.send_cmd("Incantation\n")
        if response == "ko":
            print("ouspi doupsi")
            return
        print("Ritual begins...")
        self.level += 1
        self.upgrade_vision_field()
        print("Now elevating to %d" %(self.level))

    def forward(self):
        self.send_cmd("Forward\n")
        if self.direction == Direction.NORTH:
            if self.y + 1 > self.map_dimension['y']:
                self.y -= self.map_dimension['y']
            else:
                self.y += 1
        elif self.direction == Direction.SOUTH:
            if self.y - 1 < 0:
                self.y += self.map_dimension['y']
            else:
                self.y -= 1
        elif self.direction == Direction.EST:
            if self.x + 1 > self.map_dimension['x']:
                self.x -= self.map_dimension['x']
            else:
                self.x += 1
        elif self.direction == Direction.WEST:
            if self.x - 1 < 0:
                self.x += self.map_dimension['x']
            else:
                self.x -= 1

    def right(self):
        self.send_cmd("Right\n")
        self.direction += 1
        if self.direction > 3:
            self.direction = 0

    def left(self):
        self.send_cmd("Left\n")
        self.direction -= 1
        if self.direction < 0:
            self.direction = 3
    
    def look(self):
        print("look around")
        response = self.send_cmd("Look\n")
        self.look_interpreter(response)
        self.dump_vision_field()

    def look_interpreter(self, response):
        vision_field_limit = len(self.vision_field)
        cases = 0
        command = response[1:-2]

        cases = command.split(",")
        for index in range(1, vision_field_limit + 1):
            # TODO: check les incidences sur le bag
            self.vision_field[index] = cases[index - 1]

    def dump_vision_field(self):
        tmp_level = len(self.vision_field) - 1
        x = 0
        limit = 1
        index = 1
        pad = self.level + 1

        while tmp_level > 0:
            print("\t" * pad, end="")
            if index > tmp_level:
                break
            while x < limit:
                print("[" + self.vision_field[index] +"]", end="")
                index += 1
                x += 1
            print("")
            limit += 2
            x = 0
            tmp_level -= 1
            pad -= 1

    def take_object(self): # WIP
        print("Take object")
        self.send_cmd("Take object\n")

    def set_object(self): # WIP
        print("Set object down")
        self.send_cmd("Set object\n")

    def fork(self):
        print("Set object down")
        self.send_cmd("Fork\n")

    def eject(self):
        print("Fus ro dah!")
        self.send_cmd("Eject\n")

    def broadcast(self, text):
        self.send_cmd("Broadcast " + text + "\n")

    def inventory(self):
        buffer = self.send_cmd("Inventory\n")[1:-2].split(',')
        current_inventory = {}
        for elem in buffer:
            tmp = elem.lstrip().split(' ')
            current_inventory.update({tmp[0]: int(tmp[1])})
        current_inventory.update({ "deraumere": 7 })
        self.stones = current_inventory.copy()
        self.food = self.stones.pop("food", None)
        print(self.stones)
        print(self.food)

    def connect_number(self):
        response = self.send_cmd("Connect_nbr\n")
        self.unused_player_slot = int(response)

    # TODO: noise function, dead, ?set_object, ?take_object
