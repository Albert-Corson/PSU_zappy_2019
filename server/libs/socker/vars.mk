##
## EPITECH PROJECT, 2020
## Socker
## File description:
## Makefile variables
##

FLAGS_DEBUG		=	-g -DDEBUG
FLAGS_INCLUDES	=	-I$(DIR_HEADERS)

override CFLAGS	+=	$(FLAGS_INCLUDES)		\
					-Wall					\
					-Wextra					\
					-g

ROOT_LIB		:=	$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

NAME		=	socker

NAME_LIB	=	lib$(NAME).a
TARGET_LIB	=	../$(NAME_LIB)

NAME_TEST	=	unit_tests
TARGET_TEST	=	tests/$(NAME_TEST)
