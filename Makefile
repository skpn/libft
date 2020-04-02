# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 21:32:05 by sikpenou          #+#    #+#              #
#    Updated: 2020/04/02 10:44:26 by skpn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = $(COMPILER) $(COMPILATION_FLAGS) $(DEBUG_FLAGS) $(INCLUDE_FLAGS)

COMPILER = gcc

COMPILATION_FLAGS = -Wall -Werror -Wextra

DEBUG_FLAGS = -g3 -fsanitize=address -fsanitize=leak

INCLUDE_FLAGS = -I $(INC_DIR)

SRC_DIR = $(shell find src -type d)

INC_DIR = $(shell find inc -type d)

OBJ_DIR = objects

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

SRCS +=	main_lem.c \
		init_structs_lem.c \
		init_display_structs_lem.c \
		exit_lem.c \
		free_lem_paths.c \
		parser_lem.c \
		set_graph.c \
		set_lvl.c \
		clean_graph.c \
		seek_paths.c \
		try_path.c \
		manage_config.c \
		update_best_config.c \
		load_balancing.c \
		debug_display_config_lem_lvl_lem.c \
		debug_rooms_lem.c \
		debug_paths.c \
		set_display.c \
		display_lem.c \
		get_anthill.c \
		get_rooms.c \
		get_tubes.c

INCS += \
		lem_in.h \
		libft.h

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
vpath %.h $(foreach dir, $(INC_DIR), $(dir):)
vpath %.a $(foreach dir, $(LIB_DIR), $(dir):)

all: $(NAME)

$(NAME): $(INCS) $(LIBS) $(OBJS) Makefile
	/bin/echo compiling $(NAME)
	ar rc $(NAME) $(OBJS)

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