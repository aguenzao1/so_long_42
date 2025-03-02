NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = src/main.c \
	  get_next_line/get_next_line.c \
	  get_next_line/get_next_line_utils.c \
	  src/map_parser.c \
	  src/map_validation.c \
	  src/flood_fill.c \
	  src/game_actions.c \
	  src/utils.c \
	  src/utils2.c

OBJ = $(SRC:.c=.o)

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: mlx $(NAME)

mlx:
	@make -C libmlx.a

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS)

%.o: %.c so_long.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@make -C mlx clean

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re