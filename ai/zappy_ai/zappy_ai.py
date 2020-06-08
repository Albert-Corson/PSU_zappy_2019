from zappy_ai.trantorian import Trantorian
import socket

class Error(Exception):
    pass

class CmdLineErrors(Error):
    def __init__(self, expression, message):
        self.expression = expression
        self.message = message

#TODO: Vision handling and ressources managements

def arg_gestion(ac, av):
    dicto = { "-p": "", "-name": "", "-h": "" } 
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

    sockfd.send("look\n".encode("Utf8"))
    foo = sockfd.recv(1280).decode("Utf8")
    print(foo)
    # AI stuff here

    sockfd.close()
