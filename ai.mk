include var.mk sources.mk

$(NAME_AI):
	cd ai ; pip3 install -r requirements.txt ; python3 setup.py build
	cp ai/build/exe.*/* ./ -r 
