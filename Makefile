##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## Makefile
##


all: ai_z server_z ## Build the binary and relinks if needed

include server.mk ai.mk

server_z: $(NAME_SRV)

ai_z: $(NAME_AI)

tests_run: override LDLIBS	+=	-lcriterion --coverage
tests_run: all ## build and execute unit tests
	$(CC) $(CPPFLAGS) -o $(NAME_TEST) $(SRC_TEST) $(LDFLAGS) $(LDLIBS)
	./unit_tests --verbose

clean: ## Delete the relocatable files
	$(RM) $(BUILD_SRV) *.gcda *.gcno

fclean: clean ## Delete the binary file and execute the above rule
	$(RM) $(NAME_SRV) $(NAME_TEST)
	$(RM) $(NAME_AI)

re: fclean all ## Executes an fclean and rebuild

help: ## Display this help
	@printf "USAGE:\n\n"
	@grep -E "^[a-zA-Z\\_]+:.*##.*" Makefile | awk -F ":.*##" '{printf "$(BLUE)%-25s$(WHITE)%s\n", $$1, $$2}'

.PHONY: all clean fclean re

