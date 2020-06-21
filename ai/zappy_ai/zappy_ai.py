from zappy_ai.trantorian import Trantorian
import sys
import asyncore, socket

class Error(Exception):
    pass

class CmdLineErrors(Error):
    def __init__(self, expression, message):
        self.expression = expression
        self.message = message

class ReceiverHandler(asyncore.dispatcher):
    player = None
    def __init__(self, host, port):
        asyncore.dispatcher.__init__(self)
        self.sockfd = socket.create_connection((host, port))

    def handle_close(self):
        self.close()
        sys.exit(0)

    def handle_read(self):
        print("ASYNC RECEIVER")
        print(self.recv(3000))
        length_checker = len("message")
        response = self.recv(3000)
        
        print("################")
        print(response)
        print("################")
        if response == "dead":
            self.handle_close()
        elif len(response) >= length_checker and response[:length_checker] == "message":
            self.player.check_broadcast_msg(response)

#TODO: Vision handling and ressources managements

def arg_gestion(ac, av):
    dicto = { "-p": "", "-n": "", "-h": "" } 
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
    if dicto.get("-n") == "" or dicto.get("-p") == "":
        raise CmdLineErrors("You need to specify both '-p' and '-n' as parameter, see -help.", "")
    try:
        int(dicto["-p"])
    except ValueError:
        raise CmdLineErrors("The port must be a number", "")
    #[print(x + " => " + dicto[x]) for x in dicto]
    return dicto["-p"], dicto["-n"], dicto["-h"]

def init_communication(sockfd, team_name):
    msg = sockfd.recv(1280).decode("Utf8")
    print("receive => " + msg)
    sockfd.send((team_name + "\n").encode("Utf8"))
    buffer = sockfd.recv(1280).decode("Utf8").split('\n')
    print(buffer)
    if not buffer[0] or buffer[0] == 'ko':
        raise CmdLineErrors("The team specify may not exist, please verify command line argument", "")
    remaining_client = int(buffer[0])
    word_dimensions = list(map(int, buffer[1].split(' ')))
    return remaining_client, word_dimensions

def genese(player, word_dim):
    player.set_map_dimension(word_dim[0], word_dim[1])
    player.randomize_spawn() # Maybe useless
    player.look()
    player.inventory()

def begin_ai(ac, av):
    port, name , host = arg_gestion(ac - 1, av[1:])
    host= socket.gethostbyname(host)
    # begin socket stuff here
    try: 
        client = ReceiverHandler(host, port)
        sockfd = client.sockfd
        remaining_client, word_dim = init_communication(sockfd, name)
        player = Trantorian(name, sockfd)
        client.player = player
        genese(player, word_dim)
        #asyncore.loop()
        while player.level != 8:
            # AI stuff here
            # TODO: test dead reponse with our server
            player.work()
    except KeyboardInterrupt: # ctrl-c or delete
        print("Player is dying off..")
        # TODO: check with server side if this event is catch on their side
        sockfd.close()
        sys.exit(84)
    sockfd.close()

