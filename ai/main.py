""" Main zappy_ai """
import sys

from zappy_ai.zappy_ai import CmdLineErrors, begin_ai

def displayHelp():
    print("USAGE: ./zappy_ai -p port -name -h machine ")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")

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
