#!/usr/bin/env python3 
import sys

class Error(Exception):
    pass

class CmdLineErrors(Error):
    def __init__(self, expression, message):
        self.expression = expression
        self.message = message

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

def begin_ai(ac, av):
    ac-=1
    arg_gestion(ac, av[1:])
    # begin socket stuff here

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