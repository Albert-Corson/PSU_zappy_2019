include sources.mk

BLUE	=		\033[36m

WHITE	=		\033[0m

CC		=		gcc

LD		=		$(CC)

RM		=		rm -rf

BUILD_SRV	=	build_srv

BUILD_CLI	=	build_ai

NAME_SRV	=	zappy_server

NAME_CLI	=	zappy_ai

NAME_TEST	=	unit_tests

OBJ_SRV		=	$(SRC_SRV:%.c=$(BUILD_SRV)/%.o) 

OBJ_AI		=	$(SRC_AI:%.c=$(BUILD_AI)/%.o)

override LDFLAGS	+=

override LDLIBS		+= 

override CFLAGS		+=	-Wall \
						-Wextra \
						-ffreestanding \
						-Wshadow \
						-Wsign-compare \
						-Wno-unused-parameter \
						-Wno-unused-variable \

override CPPFLAGS	+=	-I./share/include		\
						-I./server/include		\

override DEPFLAGS	+=	-MT $@ -MMD -MP -MF $(@:.o=.d)
