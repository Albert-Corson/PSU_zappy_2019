import collections
import sys
from enum import Enum, unique
from random import randrange
import socket

@unique
class Direction(Enum): # this Enum is now maybe useless
    NORTH = 0
    EST = 1
    SOUTH = 2
    WEST = 3

class Trantorian:
    # Space stuff 
    direction = Direction.NORTH #useless
    x, y = 0, 0
    map_dimension = {'x': 0, 'y': 0}
    pyramid_nbr = []

    # Time stuff
    life_unit = 10
    time_unit = 1260

    # Player stuff
    food = 0
    player_gathered = 0
    level = 1
    #stones = { "linemate": 0, "deraumere": 0, "sibur": 0,
    #            "mendiane": 0, "phiras": 0, "thystame": 0 }
    stone_ref = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
    stones = {}
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

    vision_field = {0: "empty", 1: "empty", 2: "empty", 3: "empty"} # This is suppose to be the vision of a 1 level trantorian

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
        actual_state = list(self.stones.values())
        require_state = self.elev_table[self.level - 1][1:]
        print("required ###### =>")
        print(require_state)

        for _ in range(len(require_state)):
            print(actual_state[_])
            if require_state[_] > actual_state[_]:
                return False
        print("All ressources are reunited")
        return True

    def send_cmd(self, msg):
        self.sockfd.send(msg.encode("Utf8"))
        response = self.sockfd.recv(3000).decode("Utf8")

        msg_case = "message"
        print("HERE")
        print("[" + response[:len(msg_case)] + "]")

        if len(response) > len(msg_case) and response[:len(msg_case)] == msg_case:
            print("THERE")
            self.check_broadcast_msg(response)
        response = self.sockfd.recv(3000).decode("Utf8")
        print(response)
        return response

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
        print("Forward")
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
        print("Turn Right")
        self.send_cmd("Right\n")
        self.direction += 1
        if self.direction > 3:
            self.direction = 0

    def left(self):
        print("Turn Left")
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
        print(cases)
        for index in range(vision_field_limit):
            if not cases[index]:
                cases[index] = "empty"
            # TODO: check les incidences sur le bag
            self.vision_field[index] = cases[index]

    def dump_vision_field(self):
        tmp_level = len(self.vision_field) - 1
        x = 0
        limit = 1
        index = 0
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

    def take_object(self, obj): # WIP
        print("Take object => " + obj)
        self.send_cmd("Take "+ obj +"\n")

    def set_object(self, obj): # WIP
        print("Set object down => " + obj)
        self.send_cmd("Set "+ obj +"\n")

    def fork(self):
        print("Set object down")
        self.send_cmd("Fork\n")

    def eject(self):
        print("Fus ro dah!")
        self.send_cmd("Eject\n")

    def broadcast(self, text):
        print("Broadcasting..")
        self.send_cmd("Broadcast " + text + "\n")

    def inventory(self):
        response = self.send_cmd("Inventory\n")
        buffer = response[1:-2].split(',')
        current_inventory = {}
        print(response)
        print(buffer)
        print("~~~~~~~~~~~~~~~~~~~~")
        for elem in buffer:
            tmp = elem.lstrip().split(' ')
            print(tmp)
            current_inventory.update({tmp[0]: int(tmp[1])})
        print("~~~~~~~~~~~~~~~~~~~~")
        self.stones = current_inventory.copy()
        self.food = self.stones.pop("food", None)
        print(self.stones)
        print(self.food)

    def check_broadcast_msg(self, broadcasted):
        # "message K, txt"
        tmp = broadcasted.split(",")
        tmp_bis = tmp.split(" ")
        coord_from_me = int(tmp_bis[1])
        message = tmp[1]
        print("someone said : << %s >> at %d" %(message, coord_from_me))
        #TODO: calculate la distance la plus courte avec la methode de Manhatan

    # TODO: finish it
    def shortest_path_k(self, k): # k is supposed to be a number 
        print("foo")
        # TODO: find the coordinate of the point K
        # k=|Xk−X0|+|Yk−Y0|=|Xk|+|Yk|

    def connect_number(self):
        response = self.send_cmd("Connect_nbr\n")
        self.unused_player_slot = int(response)

    # algo

    # renvoie l'index d'ou le ressouces a ete trouver ou -1 sinon
    def check_in_vision_field(self, obj):
        tmp = []
        calc_middle = lambda x : (x * x) - x

        begs = [1, 4, 9, 16, 25, 36] # TODO: Maybe increase the array until levl 8 view
        efficient_path = [calc_middle(x) for x in range(2, 8)]
        print("&&&&&&&&&&&&&&&&&&&&&")
        print(efficient_path)
        print("&&&&&&&&&&&&&&&&&&&&&")
        delta = 0
        tmp = None

        for x in range(len(self.vision_field)):
            if x in efficient_path:
                continue
            if x in begs:
                tmp = self.vision_field[efficient_path[delta]].split(' ')
                if obj in tmp:
                    print("@@@@@ obj find at index %d" %(efficient_path[delta]))
                    return efficient_path[delta]
                delta += 1
            tmp = self.vision_field[x].split(' ')
            if obj in tmp:
                print("@@@@@ obj find at index %d" %(x))
                return x
        return -1
        
    def find_col_from_tile(self, tile_nbr):
        tmp_level = len(self.vision_field) - 1
        x = 0
        limit = 1
        index = 0
        count = 0

        while tmp_level > 0:
            if index > tmp_level:
                break
            while x < limit:
                if index == tile_nbr:
                    print("###### %d" %(count))
                    return count
                index += 1
                x += 1
            limit += 2
            x = 0
            tmp_level -= 1
            count += 1
        print("######~ %d" %(count))
        return count

    def get_stone_book_from_level(self, level):
        recipe = {}
        buffer = self.elev_table[level][1:]

        for i in range(len(self.stone_ref)):
            recipe.update({ self.stone_ref[i]: buffer[i] })
        print(recipe)
        return recipe

    # WIP: HERE
    def check_other_needed_resources(self):
        print("#########################")
        self.look()
        print("===> ")
        recipe = self.get_stone_book_from_level(self.level - 1)
        current_tile = self.vision_field.get(0).split(' ')
        print(recipe)
        print(current_tile)
        #n TODO: now we need to move organise stone we need from current_tile and take each of them
        for obj in current_tile:
            if obj in recipe and recipe.get(obj) > 0:
                self.take_object(obj)
        print("#########################")
    
    # ici on se deplace vers l'item en prenant d'autres item requis si on passe dessus
    def go_take_it(self, tile_nbr, obj):
        col_nbr = self.find_col_from_tile(tile_nbr)
        calc_middle = lambda x : (x * x) - x
        alpha = calc_middle(col_nbr + 1)
        delta = alpha - tile_nbr

        print("alpha => %d" %(alpha ))
        print("col_nbr => %d" %(col_nbr))
        for x in range(col_nbr):
            self.check_other_needed_resources()
            self.forward()
        if delta < 0:
            self.right()
        elif delta > 0:
            self.left()
        print("delta => %d" %(delta ))
        for y in range(abs(delta)):
            self.check_other_needed_resources() 
            self.forward()
        self.take_object(obj)
        self.look()
        print(self.vision_field.get(0).split(" "))
        other_obj = self.vision_field.get(0).split(" ").count(obj)
        [self.take_object(obj) for _ in range(other_obj)]
        print("~~~~~~~~")
        self.inventory()
        print("~~~~~~~~")

    def work(self):
        print("Up")
        index_vision = -1
        # regarder les ressources actuelles
        index_level = self.level - 1
        required_stones = self.elev_table[index_level][1:]
        print(required_stones)
        corresp_stone = list(self.stones.values())
        ref_table = required_stones
        print(corresp_stone)
        # trouve la ressouce la plus nécessaire
        most_wanted = ref_table.index(max(ref_table))
        print(self.stone_ref[most_wanted])
        # si on a tout bah on broadcast 
        if self.check_ressources() == True:
            # si assez de joueurs reunis on incante
            if self.level != 1:
                self.broadcast("Avengers Rassemblement!")
            if self.player_gathered == self.elev_table[index_level][0] - 1:
                print("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#####################")
                self.incantation()
                return
        # regarde dans sa vision_field and move forward if most wanted
        self.look()
        index_vision = self.check_in_vision_field(self.stone_ref[most_wanted])
        if index_vision != -1:
            self.go_take_it(index_vision, self.stone_ref[most_wanted])
        else:
            [self.forward() for x in range(3)]
        print("Working")

    # TODO: noise function, dead, ?set_object, ?take_object
