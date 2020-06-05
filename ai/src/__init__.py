#!/usr/bin/env python3 
import sys

import socket

class Error(Exception):
    pass

class CmdLineErrors(Error):
    def __init__(self, expression, message):
        self.expression = expression
        self.message = message

#TODO: Vision handling and ressources managements

class Trantorian:
    x, y = 0, 0
    level = 1
    stones = { "linemate": 0, "deraumere": 0, "sibur": 0,
                "mendiane": 0, "phiras": 0, "thystame": 0 }

    def __init__(self, name):
        print("A Traitorian has been invoked")
        self.name = name

    def collect_stone(self, stone):
        if stone in self.stones:
            print(self.name + " just picked up a " + stone + " stone!")
            self.stones[stone] += 1
        else:
            print("Dunno this stone, duh..")

    def dump_stone(self):
        print("### Stone recap ###\n")
        [print("# [" + x + "]" + ":\t%d  #" %(self.stones[x])) for x in self.stones]
        print("\n### end ###")

    def reset_stones(self):
        for _ in self.stones:
            self.stones[_] = 0

    def elevate(self):
        print("This member function is for elevation")
        self.level += 1
        print("Now elevating to %d" %(self.level))

def displayHelp():
    print("USAGE: ./zappy_ai -p port -name -h machine ")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")

def arg_gestion(ac, av):
    dicto = { "-p": "", "-name": "", "-h": "" } 
    port = 0
    i = 0

    if ac % 2 != 0:
        raise CmdLineErrors("Wrong number of argument", "")
    while i < ac:
        if i % 2 == 0:
            if av[i] in dicto:
                dicto[av[i]] = av[i+1]
            else:
                raise CmdLineErrors("Dunno this parameter: "+ av[i], "")
        i += 1

    if dicto.get('-h') == "":
        dicto["-h"] = "localhost"
    if dicto.get("-name") == "" or dicto.get("-p") == "":
        raise CmdLineErrors("You need to specify both '-p' and '-name' as parameter, see -help.", "")
    try:
        int(dicto["-p"])
    except ValueError:
        raise CmdLineErrors("The port must be a number", "")
    #[print(x + " => " + dicto[x]) for x in dicto]
    return dicto["-p"], dicto["-name"], dicto["-h"]

def init_communication(sockfd, player):
    msg = sockfd.recv(1280).decode("Utf8")
    print("receive => " + msg)
    sockfd.send((player.name + "\n").encode("Utf8"))
    buffer = sockfd.recv(1280).decode("Utf8").split('\n')
    remaining_client = int(buffer[0])
    word_dimensions = list(map(int, buffer[1].split(' ')))
    return remaining_client, word_dimensions

def begin_ai(ac, av):
    
    port, name , host = arg_gestion(ac - 1, av[1:])
    host = socket.gethostbyname(host)
    player = Trantorian(name)

    # begin socket stuff here
    sockfd = socket.create_connection((host, port))
    remaining_client, word_dim = init_communication(sockfd, player)
    
    # AI stuff here

    sockfd.close()

def main():
    av = sys.argv
    ac = len(av)

    if ac == 2 and av[1] == "-help":
        displayHelp()
        sys.exit(0)
    if ac <= 1:
        print("Wrong number of arguments", file=sys.stderr)
        sys.exit(84)
    try:
        begin_ai(ac, av)
    except CmdLineErrors as err:
        print(err.expression, file=sys.stderr)
        sys.exit(84)


if __name__ == '__main__':
    main()