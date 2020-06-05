include var.mk sources.mk

$(NAME_AI):
	cp ./$(SRC_AI) $@
	chmod +x $@