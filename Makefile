# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 21:32:05 by sikpenou          #+#    #+#              #
#    Updated: 2020/04/02 14:31:53 by skpn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CC = $(COMPILER) $(COMPILATION_FLAGS) $(DEBUG_FLAGS) $(INCLUDE_FLAGS)

COMPILER = gcc

COMPILATION_FLAGS = -Wall -Werror -Wextra

DEBUG_FLAGS = -g3 -fsanitize=address -fsanitize=leak

INCLUDE_FLAGS = $(foreach dir, $(INC_DIR), -I $(dir) )

SRC_DIR = $(shell find src -mindepth 1 -type d)

LIB_DIR = $(shell find lib -mindepth 1 -maxdepth 1 -type d)

INC_DIR = $(shell find . -name 'inc' -type d)

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

SRCS +=	\
		main_lem.c \
	
SRCS +=	\
		exit_lem.c \
		free_lem_paths.c \
		init_lem_structs.c \
		init_lem_structs_display.c

SRCS +=	\
		get_anthill.c \
		get_rooms.c \
		get_tubes.c \
		parser_lem.c

SRCS +=	\
		set_graph.c \
		set_lvl.c \

SRCS +=	\
		clean_graph.c \
		load_balancing.c \
		manage_config.c \
		seek_paths.c \
		try_path.c \
		update_best_config.c

SRCS +=	\
		display_lem.c \
		set_display.c

SRCS +=	\
		debug_lem.c \
		debug_lem_paths.c \
		debug_lem_rooms.c

INCS += \
		lem_in.h \
		libft.h

LIBS += \
		libft.a

vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR)
vpath %.a $(LIB_DIR)

all: $(NAME)

$(NAME): $(LIBS) $(OBJS) Makefile
	/bin/echo compiling $(NAME)
	echo $(CC) -o $(NAME) $(OBJS) $(LIBS)
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o : %.c $(INCS) $(LIBS) Makefile
	mkdir -p $(OBJ_DIR)
	$(CC) -o $@ -c $<

$(LIBS): FORCE
	make -C $(LIB_DIR)

clean: FORCE
	rm -rf $(OBJS)

fclean: clean FORCE
	rm -rf $(NAME)

re: fclean all FORCE

show:
	echo "comp   : $(CC)\n"
	echo "src_dir: $(SRC_DIR)\n"
	echo "inc_dir: $(INC_DIR)\n"
	echo "lib_dir: $(LIB_DIR)\n"
	echo "srcs   : $(SRCS)\n"
	echo "incs   : $(INCS)\n"
	echo "libs   : $(LIBS)\n"

FORCE:

.SILENT: