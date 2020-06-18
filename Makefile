##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## Makefile
##

include sources.mk var.mk

all:    libs $(NAME_SRV) ## Build the binary and relinks if needed

include server.mk

libs:
	$(MAKE) -C server/libs/socker INCLUDES_PATH="$(INCLUDES_PATH_SRV)"

debug: CFLAGS+=-g
debug: all

tests_run: override LDLIBS              +=      -lcriterion --coverage
tests_run: all ## build and execute unit tests
	$(CC) $(CPPFLAGS) -o $(NAME_TEST) $(SRC_TEST) $(LDFLAGS) $(LDLIBS)
	./unit_tests --verbose

clean: ## Delete the relocatable files
	$(RM) $(BUILD_SRV) *.gcda *.gcno
	$(MAKE) clean -C server/libs/socker INCLUDES_PATH="$(INCLUDES_PATH_SRV)"

fclean: clean ## Delete the binary file and execute the above rule
	$(RM) $(NAME_SRV) $(NAME_TEST)
	$(MAKE) fclean -C server/libs/socker INCLUDES_PATH="$(INCLUDES_PATH_SRV)"

re: fclean all ## Executes an fclean and rebuild

help: ## Display this help
	@printf "USAGE:\n\n"
	@grep -E "^[a-zA-Z\\_]+:.*##.*" Makefile | awk -F ":.*##" '{printf "$(BLUE)%-25s$(WHITE)%s\n", $$1, $$2}'

.PHONY: all clean fclean re

