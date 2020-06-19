include var.mk sources.mk

$(NAME_AI):
	cd ai ; pip install -r requirements.txt ; python3 setup.py build
	cp ai/build/exe.linux-x86_64-3.7/main ./zappy_ai
