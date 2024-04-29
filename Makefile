NAME = cub3D

SRC_C =	tools/ft_isnum.c \
		tools/ft_split.c \
		tools/ft_strcmp.c \
		tools/ft_strncmp.c \
		tools/ft_atoi.c \
		tools/ft_strdup.c \
		tools/ft_is_space.c \
		tools/ft_strlen.c \
		tools/ft_substr.c \
		tools/ft_strjoin.c \
		tools/ft_strjoinx.c \
		tools/ft_strchr.c \
		tools/cpy_map.c \
		tools/utils1.c \
		check_map_contant.c \
		check_map.c \
		check_name.c \
		check_textures_and_colors.c \
		error.c \
		execution.c \
		ft_get_next_line.c \
		main.c \
		parsing.c \
		readfilecontant.c \
		parsing_utilitis.c \
		parsing_utilitis2.c \
		parsing_utilitis3.c \
		parsing_utilitis4.c \
		execution_utilitis.c

COMM_PILER = cc

FLAGS = -Wall -Wextra -Werror -g

OBJC = $(SRC_C:.c=.o)

all: $(NAME)

$(NAME): $(OBJC)
	$(COMM_PILER) $(FLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJC) -o $(NAME)

%.o : %.c cub3d.h
	$(COMM_PILER) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJC) $(OBJ_BC)

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)

re: fclean all
