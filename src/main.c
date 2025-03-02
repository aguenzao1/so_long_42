/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:05:52 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/01 15:12:43 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long");
	if (!game->win)
		return (0);
	game->collected = 0;
	game->moves = 0;
	return (1);
}

int	load_images(t_game *game)
{
	game->img_width = TILE_SIZE;
	game->img_height = TILE_SIZE;
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&game->img_width, &game->img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
			&game->img_width, &game->img_height);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&game->img_width, &game->img_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&game->img_width, &game->img_height);
	game->collect_img = mlx_xpm_file_to_image(game->mlx, "textures/collect.xpm",
			&game->img_width, &game->img_height);
	if (!game->wall_img || !game->floor_img || !game->player_img
		|| !game->exit_img || !game->collect_img)
		return (0);
	return (1);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor_img, 
				x * TILE_SIZE, y * TILE_SIZE);
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win,
					game->wall_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win,
					game->player_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win,
					game->exit_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win,
					game->collect_img, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		move_player(game, 0, -1);
	else if (keycode == KEY_A)
		move_player(game, -1, 0);
	else if (keycode == KEY_S)
		move_player(game, 0, 1);
	else if (keycode == KEY_D)
		move_player(game, 1, 0);
	return (0);
}

void l()
{
	system("leaks so_long");
}

int    main(int argc, char **argv)
{
    t_game    game;

	atexit(l);
    if (argc != 2)
    {
        print_error("Error\nUsage: ./so_long map.ber");
        return (1);
    }
    if (!check_extension(argv[1]))
        return (print_error("Error\nMap file must have .ber extension"),1);
    if (access(argv[1], F_OK) == -1)
        return (print_error("Error\nFailed to open map file"), 1);
    if (check_for_invalid_newlines(argv[1]))
        return (print_error("Error\nMap contains invalid newlines"),1);
    ft_memset(&game, 0, sizeof(game));
    if (!parse_map(argv[1], &game) || !validate_map(&game))
        return (free_game(&game),1);
    if (!init_game(&game) || !load_images(&game))
        return (free_game(&game), 1);
    render_map(&game);
    mlx_key_hook(game.win, key_hook, &game);
    mlx_hook(game.win, 17, 0, close_game, &game);
    mlx_loop(game.mlx);
    return (0);
}
