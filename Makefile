DIR_OBJ = .objs
DIR_SRC = src
DIR_INC = ./inc
DIR_LIBFT = ./libft
SRCS = 	$(DIR_SRC)/gnl/get_next_line.c \
		$(DIR_SRC)/gnl/get_next_line_utils.c \
		$(DIR_SRC)/ft_print_error_cubfile.c \
		$(DIR_SRC)/ft_check_map_cubfile_utils.c \
		$(DIR_SRC)/ft_check_map_cubfile.c \
		$(DIR_SRC)/ft_get_map_cubfile.c \
		$(DIR_SRC)/ft_malloc_map.c \
		$(DIR_SRC)/ft_get_info_value.c \
		$(DIR_SRC)/ft_cubfile.c \
		$(DIR_SRC)/ft_cubfile_utils.c

NAME = main
OBJ = $(patsubst $(DIR_SRC)/%.c, $(DIR_OBJ)/%.o, $(SRCS))
CC = clang
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -lft
AR = ar -rc
RM = rm -f
LIBFT = $(DIR_LIBFT)/libft.a

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) -I$(DIR_INC) -I$(DIR_LIBFT) -L$(DIR_LIBFT) $(LFLAGS) -fsanitize=address -o $@ -g

$(DIR_OBJ)/%.o:	$(DIR_SRC)/%.c
				mkdir -p $(DIR_OBJ)
				mkdir -p $(DIR_OBJ)/gnl
				$(CC) $(CFLAGS) -c $< -I$(DIR_INC) -I$(DIR_MLX) -fsanitize=address -g -o $@

$(LIBFT):
			$(MAKE) -C $(DIR_LIBFT)

all:	$(NAME)

clean:
	$(MAKE) -C $(DIR_LIBFT) clean
	$(RM) $(OBJ)

fclean:	clean
		$(MAKE) -C $(DIR_LIBFT) fclean
		$(RM) $(NAME)

re:	fclean all

debug:	$(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) -I$(DIR_INC) -L$(DIR_LIBFT) $(LFLAGS) -fsanitize=address -o $@ -g


.PHONY:	all clean fclean re
