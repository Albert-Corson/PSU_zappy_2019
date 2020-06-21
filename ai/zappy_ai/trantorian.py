import collections
import re
import sys
from enum import IntEnum, unique
from random import randrange, randint
import socket

@unique
class Actions(IntEnum):
    NONE = 0
    FORWARD = 1
    ROTATE_LEFT = 2
    ROTATE_RIGHT = 3

@unique
class Direction(IntEnum): # this Enum is now maybe useless
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

    #broadcast stuff
    DIAGONAL_LEFT = [Actions.FORWARD, Actions.ROTATE_LEFT, Actions.FORWARD, Actions.ROTATE_RIGHT]
    DIAGONAL_RIGHT = [Actions.FORWARD, Actions.ROTATE_RIGHT, Actions.FORWARD, Actions.ROTATE_LEFT]

    directions_broadcast = [
        [[Actions.NONE], [Actions.NONE]],
        [[Actions.NONE], [Actions.FORWARD]],
        [[Actions.NONE], DIAGONAL_LEFT],
        [[Actions.ROTATE_LEFT],[Actions.FORWARD]],
        [[Actions.ROTATE_LEFT], DIAGONAL_LEFT],
        [[Actions.ROTATE_LEFT, Actions.ROTATE_LEFT],[Actions.FORWARD]],
        [[Actions.ROTATE_RIGHT], DIAGONAL_RIGHT],
        [[Actions.ROTATE_RIGHT], [Actions.FORWARD]],
        [[Actions.NONE], DIAGONAL_RIGHT]
    ]

    #player attributes
    hunger_indices = 0

    # Time stuff
    life_unit = 10
    time_unit = 1260

    # Player stuff
    food = 0
    player_gathered = 0
    level = 1
    stone_ref = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
    #stones = { "linemate": 0, "deraumere": 0, "sibur": 0,
    #            "mendiane": 0, "phiras": 0, "thystame": 0 }
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
        print("Initial position x: %d -- y: %d --> direction: %d " %(self.x, self.y, self.direction))

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

    def reset_stones(self): # take into account the remaining pebbles if more than 
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
        tmp_x, tmp_y = self.x, self.y
        self.sockfd.send(msg.encode("Utf8"))
        print("HERE")
        response = self.sockfd.recv(3000).decode("Utf8")

        if response == "dead\n":
            self.sockfd.close()
            sys.exit(0)
        while re.search("^message.*", response) != None:
            if response == "dead\n":
                self.sockfd.close()
                sys.exit(0)
            if msg == 'Forward\n':
                self.check_broadcast_msg(response, tmp_x, tmp_y)
            else:
                self.check_broadcast_msg(response)
            response = self.sockfd.recv(3000).decode("Utf8")
     #   print("[" + response[:len(msg_case)] + "]")

    #    if len(response) > len(msg_case) and response[:len(msg_case)] == msg_case:
     #       print("THERE")
     #       self.check_broadcast_msg(response)
     #   response = self.sockfd.recv(3000).decode("Utf8")
        print(response)
        return response

    def incantation(self):
        self.sockfd.send("Incantation\n".encode("Utf8"))
        response = self.sockfd.recv(3000).decode("Utf8")
        print("Ritual begins...")
        print(response)
        print("----------------")
        while re.search("^Current level:.*", response) == None:
            if response == "dead\n":
                self.sockfd.close()
                sys.exit(0)
            if response == "ko":
                print("ouspi doupsi")
                return
            response = self.sockfd.recv(3000).decode("Utf8")
        print(response)
        self.level += 1
        self.upgrade_vision_field()
        print("Now elevating to %d" %(self.level))

    def forward(self):
        print("Forward")
        self.send_cmd("Forward\n")
        if self.direction == Direction.NORTH:
            if self.y + 1 > self.map_dimension['y']:
                self.y = 0
            else:
                self.y += 1
        elif self.direction == Direction.SOUTH:
            if self.y - 1 < 0:
                self.y = 10
            else:
                self.y -= 1
        elif self.direction == Direction.EST:
            if self.x + 1 > self.map_dimension['x']:
                self.x = 0
            else:
                self.x += 1
        elif self.direction == Direction.WEST:
            if self.x - 1 < 0:
                self.x = 10
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
        if len(cases) != vision_field_limit:
            print(len(cases)) #
            print(vision_field_limit) #
            print("Can't look...")
            return
        print(cases)
        print(vision_field_limit)
        for index in range(vision_field_limit -1):
            if not cases[index] or cases[index] == "" or cases[index] == " ":
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
        print("Fork")
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

    def check_level_broadcasted(self, message):
        tmp = message.split(' ')
        tmp_lvl = int(tmp[-1])

        if tmp_lvl == self.level:
            print("We have the same level")
            return True
        print("We dont have the same level")
        return False

    def check_broadcast_msg(self, broadcasted, *args):
        # "message K, txt"
        past_x = None
        past_y = None

        tmp = broadcasted.split(",")
        tmp_bis = tmp[0].split(" ")
        coord_from_me = int(tmp_bis[1])
        message = tmp[1]

        if len(args) == 2:
            print("Get Back...")
            past_x = args[0]
            past_y = args[1]
            [self.left() for _ in range(2)]
            self.forward()
        print('============================')
        print("{" + message + "}")
        print(re.search("^Avengers Rassemblement!.*", message))
        print(self.check_level_broadcasted(message))
        print(self.check_ressources())
        print('============================')
        if re.search("^Avengers Rassemblement!.*", message) != None and self.check_level_broadcasted(message) == True and self.check_ressources() == True:
            print("<< GO JOIN MY FRIEND!! >>")
            self.sockfd.send("j'arrive".encode("Utf8"))
            self.shortest_path_k(coord_from_me)
            return "abort"
        print("someone said : << %s >> at %d" %(message, coord_from_me))
        return "continue"

    # TODO: finish it
    def launch_action(self, action_value):
        if action_value == Actions.FORWARD:
            self.forward()
        elif action_value == Actions.ROTATE_LEFT:
            self.left()
        elif action_value == Actions.ROTATE_RIGHT:
            self.right()

    def shortest_path_k(self, k): # k is supposed to be a number 
        if k < 0 or k > 9:
            return
        init_action, repeted_action = self.directions_broadcast[k]
        for action in init_action :
            self.launch_action(action)
        for action in repeted_action :
            self.launch_action(action)
        
        print("<< Arrive at destination! >>")
        # TODO: find the coordinate of the point K
        # k=|Xk−X0|+|Yk−Y0|=|Xk|+|Yk|

    def connect_number(self):
        response = self.send_cmd("Connect_nbr\n")
        self.unused_player_slot = int(response)

    ## algo
    # Returns the index of where the resource was found or -1 otherwise.
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
                print("vision field: =>")
                print(self.vision_field)
                print("efficient path: =>")
                print(efficient_path)
                print("delta: =>")
                print(delta)
                print(efficient_path[delta])
                if efficient_path[delta] > len(self.vision_field):
                    break
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
    
    # here we move to the item by taking other items required if we pass over it.
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

    # pick the available item (master first, slave if master ain't available)
    def choose_item_with_priority(self, master, slave):
        if master[1] != -1:
            return master
        elif slave[1] != -1:
            return slave
        return None

    # pick the most needed item (food or stone)
    def choose_item(self, index_level):
        # 2 - 5 => FOOD ** Other *
        # 5 - 10 => FOOD * Other *
        # 10 - + => FOOD * Other **
        # get inventory and find out what are the most wanted items (food and stone)
        self.inventory()
        # check current ressources
        required_stones = self.elev_table[index_level][1:]
        print(required_stones)
        corresp_stone = list(self.stones.values())
        ref_table = required_stones
        print(corresp_stone)
        most_wanted = ref_table.index(max(ref_table))

        # locate food and most wanted stone (if in sight)
        stone_index = self.check_in_vision_field(self.stone_ref[most_wanted])
        food_index = self.check_in_vision_field("food")
        # create tuple for items priorities
        food = ("food", food_index)
        stone = (self.stone_ref[most_wanted], stone_index)

        print(self.stone_ref[most_wanted])

        if self.food > 10: # prioritize stone
            return self.choose_item_with_priority(stone, food)
        elif self.food > 5: # no priority
            random_value = randint(0, 1)
            if random_value == 0:
                self.choose_item_with_priority(stone, food)
            else:
                self.choose_item_with_priority(food, stone)
        else: # prioritize food
            return  self.choose_item_with_priority(food, stone)

# TODO: recup de la bouf

    def work(self):
        print("Up")
        # fork if necessary
        self.connect_number()
        if self.unused_player_slot == 0:
            self.fork()

        # choose item to take
        index_level = self.level - 1
        item = self.choose_item(index_level)

        # found the most needed ressources
        # if we have everything we broadcast
        if self.check_ressources() == True:
            # if enough player gather we do incantation
            if self.level != 1:
                self.broadcast("Avengers Rassemblement! for level %d" %(self.level))
            if self.player_gathered == self.elev_table[index_level][0] - 1:
                print("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#####################")
                self.incantation()
                return
        # check in vision_field and move toward most wanted
        self.look()
        if item != None:
            self.go_take_it(item[1], item[0])
        else:
            [self.forward() for x in range(3)]
        print("Working")
