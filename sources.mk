# SRC_SHARED	=	share/src/

SRC_SRV		=	server/src/main.c				\
				server/src/game.c				\
				server/src/utils/get_opts.c		\
				server/src/utils/opt_handlers.c

SRC_AI		=	client/src/main.c				\
				# $(SRC_SHARED)

SRC_TEST	=	$(filter-out server/src/main.c, $(SRC_SRV))	\
				$(filter-out client/src/main.c, $(SRC_AI))	\
