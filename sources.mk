# SRC_SHARED	=	share/src/

SRC_SRV		=	server/src/main.c				\
				# $(SRC_SHARED)

SRC_AI		=	client/src/main.c				\
				# $(SRC_SHARED)

SRC_TEST	=	$(filter-out server/src/main.c, $(SRC_SRV))	\
				$(filter-out client/src/main.c, $(SRC_AI))	\
