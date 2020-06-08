""" Installation file of our zappy_ai """

from cx_Freeze import setup, Executable

#WIP: compilation will change to py_compile later
setup(
    name = "zappy_ai",
    version = "0.1.dev",
    description = "This package is the one use for the zappy's AI from EPITECH 2nd end-year project",
    author = "Fahad Assoumani and Mathias Vigier",
    executables = [Executable("./main.py")]
)

"""import setuptools

#TODO: add Markedown to the ai directory and gives the Albert's github link


#with open("README.md", "r") as fh:
#    long_description = fh.read()

setuptools.setup(
        name="zappy_ai",
        version="0.1.dev",
        author="Fahad Assoumani and Mathias Vigier",
        author_email="fahad.assoumani@epitech.eu and mathias.vigier@epitech.eu",
        description="This package is the one use for the zappy's AI from EPITECH 2nd end-year project",
#        long_description=long_description,
#        long_description_content_type="text/markdown",
        url="none",
        packages=setuptools.find_packages(),
        classifiers=[
            "Programming Language :: Python :: 3",
            "Operating System :: OS Independent",
            ],
        python_requires='>=3.6'
        )"""
