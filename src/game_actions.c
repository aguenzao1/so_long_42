/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:15:08 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/01 14:45:37 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void handle_win_condition(t_game *game)
{
    ft_putstr_fd("\nCongratulations! You won in ", 1);
    ft_putnbr_fd(game->moves + 1, 1);
    ft_putstr_fd(" moves.\n", 1);
    close_game(game);
}

int move_player(t_game *game, int x, int y)
{
    int new_x;
    int new_y;

    new_x = game->player.x + x;
    new_y = game->player.y + y;
    if (game->map[new_y][new_x] == '1')
        return (0);
    if (game->map[new_y][new_x] == 'E' && game->collected != game->collectibles)
        return (0);
    if (game->map[new_y][new_x] == 'C')
    {
        game->collected++;
        game->map[new_y][new_x] = '0';
    }
    if (game->map[new_y][new_x] == 'E' && game->collected == game->collectibles)
        return (handle_win_condition(game),1);
    game->map[game->player.y][game->player.x] = '0';
    game->map[new_y][new_x] = 'P';
    game->player.x = new_x;
    game->player.y = new_y;
    game->moves++;
    ft_putstr_fd("Moves: ", 1);
    ft_putnbr_fd(game->moves, 1);
    ft_putstr_fd("\n", 1);
    return (update_game(game), 1);
}

void	update_game(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

void	free_game(t_game *game)
{
	if (game->map)
		free_map(game->map, game->map_height);
	if (game->mlx && game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->mlx && game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->mlx && game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->mlx && game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->mlx && game->collect_img)
		mlx_destroy_image(game->mlx, game->collect_img);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		free(game->mlx);
	}
}
