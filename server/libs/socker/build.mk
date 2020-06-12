##
## EPITECH PROJECT, 2020
## Socker
## File description:
## building rules
##

$(TARGET_LIB): $(OBJ_LIB)
	ar rc $(TARGET_LIB) $(OBJ_LIB)

$(PROJECT_ROOT)/include/libs/$(NAME)/%.h: include/%.h
	ln -fs $(ROOT_LIB)/$< $@