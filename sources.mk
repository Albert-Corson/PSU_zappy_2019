# SRC_SHARED	=	share/src/

SRC_AI		=	ai/src/__init__.py
				# $(SRC_SHARED)

SRC_SRV		=	server/src/main.c				\
				# $(SRC_SHARED)

SRC_SRV_TEST	=	$(filter-out server/src/main.c, $(SRC_SRV))	\

#SRC_SRV_AI		=	$(filter-out ai/src/main.cpp, $(SRC_AI))	\
