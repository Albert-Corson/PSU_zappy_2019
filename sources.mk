SRC_SRV		=	server/src/commands/broadcast/command.c				\
				server/src/commands/command.c						\
				server/src/commands/connect_nbr/command.c			\
				server/src/commands/eject/command.c					\
				server/src/commands/fork/command.c					\
				server/src/commands/forward/command.c				\
				server/src/commands/incantation/command.c			\
				server/src/commands/incantation/preliminaries.c		\
				server/src/commands/inventory/command.c				\
				server/src/commands/left/command.c					\
				server/src/commands/look/command.c					\
				server/src/commands/right/command.c					\
				server/src/commands/set/command.c					\
				server/src/commands/take/command.c					\
				server/src/game/eggs.c								\
				server/src/game/flags.c								\
				server/src/game/game.c								\
				server/src/game/init.c								\
				server/src/game/players.c							\
				server/src/game/run.c								\
				server/src/recipes.c								\
				server/src/on_readable.c							\
				server/src/on_connect.c								\
				server/src/on_disconnect.c							\
				server/src/send_str.c								\
				server/src/loop.c									\
				server/src/main.c									\
				server/src/mqueue/mq_api.c							\
				server/src/mqueue/mq.c								\
				server/src/mqueue/mq_clear.c						\
				server/src/mqueue/mq_hooks.c						\
				server/src/mqueue/mq_init.c							\
				server/src/mqueue/mq_output.c						\
				server/src/mqueue/mq_pending.c						\
				server/src/pending_init.c							\
				server/src/sbuffer/allocate.c						\
				server/src/sbuffer/extract.c						\
				server/src/sbuffer/sbuffer.c						\
				server/src/sbuffer/writers.c						\
				server/src/spectators/send_elevation.c				\
				server/src/spectators/send_movement.c				\
				server/src/spectators/send_new.c					\
				server/src/spectators/send_others.c					\
				server/src/spectators/send_player_action.c			\
				server/src/struct/callback.c						\
				server/src/struct/egg.c								\
				server/src/struct/game.c							\
				server/src/struct/recipe.c							\
				server/src/struct/player.c							\
				server/src/struct/spectator/send_elevation.c		\
				server/src/struct/spectator/send_init.c				\
				server/src/struct/spectator/send_movement.c			\
				server/src/struct/spectator/send_new.c				\
				server/src/struct/spectator/send_player_action.c	\
				server/src/struct/spectator/spectator.c				\
				server/src/struct/team.c							\
				server/src/struct/vector.c							\
				server/src/utils/getelapsedms.c						\
				server/src/utils/randbetween.c						\
				server/src/utils/strtoelement.c

#SRC_SRV_AI		=	$(filter-out ai/src/main.cpp, $(SRC_AI))	\

SRC_TEST	=	$(filter-out server/src/main.c, $(SRC_SRV))	\
				$(filter-out client/src/main.c, $(SRC_AI))	\
				server/tests/sbuffer.c