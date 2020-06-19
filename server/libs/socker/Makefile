##
## EPITECH PROJECT, 2020
## Socker
## File description:
## Makefile
##

ifeq ($(INCLUDES_PATH),)
$(error INCLUDES_PATH is not set)
endif

include vars.mk sources.mk

all: 	$(TARGET_LIB) $(HEADERS)

include build.mk tests.mk

clean:
	$(RM) $(OBJ_LIB)
	$(RM) $(OBJ_TEST) $(GCNO_TEST) $(GCDA_TEST)

fclean: clean
	$(RM) $(TARGET_LIB)
	$(RM) $(TARGET_TEST)
	$(RM) $(HEADERS)

re: fclean all

tests_run: all $(TARGET_TEST)
	./$(TARGET_TEST) --verbose

debug: CFLAGS += $(FLAGS_DEBUG)
debug: all

.PHONY: all clean fclean re tests_run debug
