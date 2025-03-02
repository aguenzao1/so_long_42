/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:05:00 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/01 15:23:59 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../get_next_line/get_next_line.h"

# define TILE_SIZE 32
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_width;
	int			map_height;
	int			collectibles;
	int			collected;
	int			moves;
	t_position	player;
	t_position	exit;
	void		*wall_img;
	void		*floor_img;
	void		*player_img;
	void		*exit_img;
	void		*collect_img;
	int			img_width;
	int			img_height;
}	t_game;

int			parse_map(char *filename, t_game *game);
int			validate_map(t_game *game);
void		count_map_size(char *filename, t_game *game);
int			check_valid_path(t_game *game);
void		flood_fill(char **map_cpy, int x, int y, t_game *game);
char		**create_map_copy(t_game *game);
void		free_map(char **map, int height);
int			check_extension(char *filename);
int			check_map_chars(t_game *game);
int			check_map_walls(t_game *game);
int			check_map_rectangular(t_game *game);
int			check_player_exit_collectible(t_game *game);
int			check_for_invalid_newlines(char *filename);
int			init_game(t_game *game);
int			load_images(t_game *game);
void		render_map(t_game *game);
int			key_hook(int keycode, t_game *game);
int			move_player(t_game *game, int x, int y);
void		update_game(t_game *game);
int			close_game(t_game *game);
void		free_game(t_game *game);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		print_error(char *error_msg);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memset(void *b, int c, size_t len);

#endif