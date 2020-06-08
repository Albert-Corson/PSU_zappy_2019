include var.mk sources.mk

$(NAME_AI):
	cd ai ; python3 setup.py build
	cp ai/build/exe.linux-x86_64-3.8/main ./zappy_ai
