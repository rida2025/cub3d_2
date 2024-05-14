NAME = cub3D

BONUS_NAME = cub3D_bonus

SRC_C =	Mandatory/ft_isnum.c \
		Mandatory/ft_split.c \
		Mandatory/ft_strcmp.c \
		Mandatory/ft_strncmp.c \
		Mandatory/ft_atoi.c \
		Mandatory/ft_strdup.c \
		Mandatory/ft_is_space.c \
		Mandatory/ft_strlen.c \
		Mandatory/ft_substr.c \
		Mandatory/ft_strjoin.c \
		Mandatory/ft_strjoinx.c \
		Mandatory/ft_strchr.c \
		Mandatory/cpy_map.c \
		Mandatory/utils1.c \
		Mandatory/check_map_contant.c \
		Mandatory/check_map.c \
		Mandatory/check_name.c \
		Mandatory/check_textures_and_colors.c \
		Mandatory/error.c \
		Mandatory/execution.c \
		Mandatory/ft_get_next_line.c \
		Mandatory/main.c \
		Mandatory/parsing.c \
		Mandatory/readfilecontant.c \
		Mandatory/parsing_utilitis.c \
		Mandatory/parsing_utilitis2.c \
		Mandatory/parsing_utilitis3.c \
		Mandatory/parsing_utilitis4.c \
		Mandatory/execution_utilitis.c \
		Mandatory/execution2.c \
		Mandatory/execution3.c \
		Mandatory/execution4.c \
		Mandatory/execution5.c \

BSRC_C = Bonus/ft_isnum_bonus.c \
		Bonus/ft_split_bonus.c \
		Bonus/ft_strcmp_bonus.c \
		Bonus/ft_strncmp_bonus.c \
		Bonus/ft_atoi_bonus.c \
		Bonus/ft_strdup_bonus.c \
		Bonus/ft_is_space_bonus.c \
		Bonus/ft_strlen_bonus.c \
		Bonus/ft_substr_bonus.c \
		Bonus/ft_strjoin_bonus.c \
		Bonus/ft_strjoinx_bonus.c \
		Bonus/ft_strchr_bonus.c \
		Bonus/cpy_map_bonus.c \
		Bonus/utils1_bonus.c \
		Bonus/check_map_contant_bonus.c \
		Bonus/check_map_bonus.c \
		Bonus/check_name_bonus.c \
		Bonus/check_textures_and_colors_bonus.c \
		Bonus/error_bonus.c \
		Bonus/execution_bonus.c \
		Bonus/ft_get_next_line_bonus.c \
		Bonus/main_bonus.c \
		Bonus/parsing_bonus.c \
		Bonus/readfilecontant_bonus.c \
		Bonus/parsing_utilitis_bonus.c \
		Bonus/parsing_utilitis2_bonus.c \
		Bonus/parsing_utilitis3_bonus.c \
		Bonus/parsing_utilitis4_bonus.c \
		Bonus/execution_utilitis_bonus.c \
		Bonus/execution2_bonus.c \
		Bonus/execution3_bonus.c \
		Bonus/execution4_bonus.c \
		Bonus/execution5_bonus.c \
		Bonus/execution6_bonus.c \
		Bonus/execution7_bonus.c \
		Bonus/help_execution_bonus.c \

COMPILER = cc

FLAGS = -Wall -Wextra -Werror -I mlx/ -Ofast -O3

OBJC = $(SRC_C:.c=.o)
BOBJC = $(BSRC_C:_bonus.c=_bonus.o)

all: $(NAME)

$(NAME): $(OBJC)
	$(COMPILER) $(FLAGS) mlx/libmlx.a -framework OpenGL -framework AppKit $(OBJC) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BOBJC)
	echo "here"
	$(COMPILER) $(FLAGS) mlx/libmlx.a -framework OpenGL -framework AppKit $(BOBJC) -o $(BONUS_NAME)

./Mandatory/%.o : ./Mandatory/%.c ./Mandatory/cub3d.h
	$(COMPILER) $(FLAGS) -c $< -o $@

./Bonus/%.o : ./Bonus/%.c ./Bonus/cub3d_bonus.h
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJC) $(BOBJC)

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)

re: fclean all
