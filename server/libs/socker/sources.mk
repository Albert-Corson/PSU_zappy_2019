##
## EPITECH PROJECT, 2020
## Socker
## File description:
## Makefile sources
##

SRC_LIB		=	src/socket/converts.c		\
				src/socket/error.c			\
				src/socket/info.c			\
				src/socket/io.c				\
				src/socket/socket.c			\
				src/socket/stream.c			\
				src/select/select.c			\
				src/events/bind.c			\
				src/events/emit.c			\
				src/events/entry.c			\
				src/events/list.c			\
				src/socker/events.c			\
				src/socker/init.c			\
				src/socker/run.c			\
				src/socker/select.c			\
				src/socker/socket.c

OBJ_LIB		=	$(SRC_LIB:.c=.o)

DIR_HEADERS	=	include
SRC_HEADERS	=	socker.h	\
				events.h	\
				types.h		\
				logger.h	\
				stream.h

HEADERS	=	$(SRC_HEADERS:%.h=$(INCLUDES_PATH)/$(NAME)/%.h)

SRC_TEST	=	$(SRC_LIB)
OBJ_TEST	=	$(SRC_TEST:.c=.o)
GCNO_TEST	=	$(SRC_TEST:.c=.gcno)
GCDA_TEST	=	$(SRC_TEST:.c=.gcda)