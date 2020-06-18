##
## EPITECH PROJECT, 2020
## Socker
## File description:
## building rules
##

$(TARGET_LIB): $(OBJ_LIB)
	ar rc $(TARGET_LIB) $(OBJ_LIB)

$(INCLUDES_PATH)/$(NAME)/%.h: $(DIR_HEADERS)/%.h
	ln -fs $(ROOT_LIB)/$< $@