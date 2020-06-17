from zappy_ai.trantorian import Trantorian
import asyncore, socket

class Error(Exception):
    pass

class CmdLineErrors(Error):
    def __init__(self, expression, message):
        self.expression = expression
        self.message = message

class ReceiverHandler(asyncore.dispatcher):
    def __init__(self, host, port):
        asyncore.dispatcher.__init__(self)
        self.sockfd = socket.create_connection((host, port))

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

def init_communication(sockfd, team_name):
    msg = sockfd.recv(1280).decode("Utf8")
    print("receive => " + msg)
    sockfd.send((team_name + "\n").encode("Utf8"))
    buffer = sockfd.recv(1280).decode("Utf8").split('\n')
    remaining_client = int(buffer[0])
    word_dimensions = list(map(int, buffer[1].split(' ')))
    return remaining_client, word_dimensions

def genese(player, word_dim):
    player.set_map_dimension(word_dim[0], word_dim[1])
    player.randomize_spawn()
    player.look()
    player.inventory()

def begin_ai(ac, av):
    response = ""
    port, name , host = arg_gestion(ac - 1, av[1:])
    host = socket.gethostbyname(host)
    # begin socket stuff here
    client = ReceiverHandler(host, port)
    sockfd = client.sockfd
    remaining_client, word_dim = init_communication(sockfd, name)
    if remaining_client < 1:
        print("No slot availiable, can't connect")
        sockfd.close()
        exit(0)

    player = Trantorian(name, sockfd)
    genese(player, word_dim)
    while player.level != 8 or response == "dead":
        # AI stuff here
        # TODO: test dead reponse with our server
        response = sockfd.recv(1280).decode("Utf8")
    sockfd.close()
