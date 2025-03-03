##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## Makefile
##

include sources.mk var.mk

all: ai_z server_z ## Build the binary and relinks if needed

libs:
	$(MAKE) -C server/libs/socker INCLUDES_PATH="$(INCLUDES_PATH_SRV)"

libs_debug:
	$(MAKE) -C server/libs/socker debug INCLUDES_PATH="$(INCLUDES_PATH_SRV)"

debug: CFLAGS+=-g
debug: libs_debug $(NAME_SRV) ai_z

include server.mk ai.mk

server_z: libs $(NAME_SRV) ## build the server binary (or you can substituate with the binary name wich has the same effect)

ai_z: $(NAME_AI) ## build the ai/client binary (or you can substituate with the binary name wich has the same effect)

tests_run: override LDLIBS	+=	-lcriterion --coverage
tests_run: all ## build and execute unit tests
	$(CC) $(CPPFLAGS) -o $(NAME_TEST) $(SRC_TEST) $(LDFLAGS) $(LDLIBS)
	./unit_tests --verbose

clean: ## Delete the relocatable files
	$(RM) $(BUILD_SRV) *.gcda *.gcno
	$(MAKE) clean -C server/libs/socker INCLUDES_PATH="$(INCLUDES_PATH_SRV)"

fclean: clean ## Delete the binary file and execute the above rule
	$(RM) $(NAME_SRV) $(NAME_AI) $(NAME_TEST) ai/build lib
	$(MAKE) fclean -C server/libs/socker INCLUDES_PATH="$(INCLUDES_PATH_SRV)"

re: fclean all ## Executes an fclean and rebuild

help: ## Display this help
	@printf "USAGE:\n\n"
	@grep -E "^[a-zA-Z\\_]+:.*##.*" Makefile | awk -F ":.*##" '{printf "$(BLUE)%-25s$(WHITE)%s\n", $$1, $$2}'

.PHONY: all clean fclean re
