# SRC_SHARED	=	share/src/

SRC_SRV		=	server/src/commands/broadcast/callback.c		\
				server/src/commands/broadcast/middleware.c		\
				server/src/commands/connect_nbr/middleware.c	\
				server/src/commands/eject/callback.c			\
				server/src/commands/eject/middleware.c			\
				server/src/commands/fork/callback.c				\
				server/src/commands/fork/middleware.c			\
				server/src/commands/forward/callback.c			\
				server/src/commands/forward/middleware.c		\
				server/src/commands/incantation/callback.c		\
				server/src/commands/incantation/middleware.c	\
				server/src/commands/inventory/callback.c		\
				server/src/commands/inventory/middleware.c		\
				server/src/commands/left/callback.c				\
				server/src/commands/left/middleware.c			\
				server/src/commands/look/callback.c				\
				server/src/commands/look/middleware.c			\
				server/src/commands/right/callback.c			\
				server/src/commands/right/middleware.c			\
				server/src/commands/set/callback.c				\
				server/src/commands/set/middleware.c			\
				server/src/commands/take/callback.c				\
				server/src/commands/take/middleware.c			\
				server/src/game.c								\
				server/src/main.c								\
				server/src/struct/callback.c					\
				server/src/struct/egg.c							\
				server/src/struct/player.c						\
				server/src/struct/team.c						\
				server/src/utils/get_opts.c						\
				server/src/utils/opt_handlers.c					\
				server/src/utils/randbetween.c					\
				server/src/utils/strtoelement.c					\
				server/src/utils/strtotab.c

SRC_AI		=	client/src/main.c				\
				# $(SRC_SHARED)

SRC_TEST	=	$(filter-out server/src/main.c, $(SRC_SRV))	\
				$(filter-out client/src/main.c, $(SRC_AI))	\


