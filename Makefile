NAME = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror -I./includes -I./get_next_line

GNL_HEADER = get_next_line/get_next_line.h

SO_HEADER = includes/so_long.h

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

MLX_FLAGS =  -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS)

%.o: %.c $(SO_HEADER) $(GNL_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean