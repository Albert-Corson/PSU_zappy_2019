SRC_SRV		=	server/src/commands/broadcast/command.c			\
				server/src/commands/broadcast/is_exable.c		\
				server/src/commands/command.c					\
				server/src/commands/connect_nbr/command.c		\
				server/src/commands/eject/command.c				\
				server/src/commands/fork/command.c				\
				server/src/commands/forward/command.c			\
				server/src/commands/incantation/command.c		\
				server/src/commands/incantation/is_exable.c		\
				server/src/commands/inventory/command.c			\
				server/src/commands/left/command.c				\
				server/src/commands/look/command.c				\
				server/src/commands/right/command.c				\
				server/src/commands/set/command.c				\
				server/src/commands/set/is_exable.c				\
				server/src/commands/take/command.c				\
				server/src/commands/take/is_exable.c			\
				server/src/game/flags.c							\
				server/src/game/game.c							\
				server/src/game/game_init.c						\
				server/src/incantations.c						\
				server/src/listeners.c							\
				server/src/main.c								\
				server/src/mqueue/mq_api.c						\
				server/src/mqueue/mq.c							\
				server/src/mqueue/mq_clear.c					\
				server/src/mqueue/mq_hooks.c					\
				server/src/mqueue/mq_init.c						\
				server/src/mqueue/mq_message.c					\
				server/src/mqueue/mq_output.c					\
				server/src/mqueue/mq_reader.c					\
				server/src/mqueue/mq_writer.c					\
				server/src/pending_init.c						\
				server/src/struct/callback.c					\
				server/src/struct/egg.c							\
				server/src/struct/game.c						\
				server/src/struct/incantation.c					\
				server/src/struct/player.c						\
				server/src/struct/spectator.c					\
				server/src/struct/team.c						\
				server/src/utils/randbetween.c					\
				server/src/utils/strtoelement.c					\
				server/src/utils/strtotab.c						\
				server/src/write_str.c

SRC_AI		=	client/src/main.c

SRC_TEST	=	$(filter-out server/src/main.c, $(SRC_SRV))	\
				$(filter-out client/src/main.c, $(SRC_AI))	\
