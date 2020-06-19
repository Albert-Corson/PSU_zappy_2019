""" Installation file of our zappy_ai """

from cx_Freeze import setup, Executable

#WIP: compilation will change to py_compile later
setup(
    name = "zappy_ai",
    version = "0.1.dev",
    description = "This package is the one use for the zappy's AI from EPITECH 2nd end-year project",
    author = "Fahad Assoumani and Mathias Vigier",
    executables = [Executable("./main.py", targetName="zappy_ai")]
)
