/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:13:23 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/02 14:07:18 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	update_game_elements(t_game *game, int i, int j, char cell)
{
	if (cell == 'C')
		game->collectibles++;
	else if (cell == 'P')
	{
		game->player.x = j;
		game->player.y = i;
	}
	else if (cell == 'E')
	{
		game->exit.x = j;
		game->exit.y = i;
	}
}

int	check_map_chars(t_game *game)
{
	int		i;
	int		j;
	char	cell;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			cell = game->map[i][j];
			if (cell != '0' && cell != '1' && cell != 'C'
				&& cell != 'E' && cell != 'P')
				return (0);
			update_game_elements(game, i, j, cell);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_width)
	{
		if (game->map[0][i] != '1' || game->map[game->map_height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1' || game->map[i][game->map_width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_player_exit_collectible(t_game *game)
{
	int	player_count;
	int	exit_count;
	int	i;
	int	j;

	player_count = 0;
	exit_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'P')
				player_count++;
			else if (game->map[i][j] == 'E')
				exit_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1 || exit_count != 1 || game->collectibles < 1)
		return (0);
	return (1);
}

int	check_valid_path(t_game *game)
{
	char	**map_cpy;
	int		valid;
	int		i;
	int		j;

	map_cpy = create_map_copy(game);
	if (!map_cpy)
		return (0);
	flood_fill(map_cpy, game->player.x, game->player.y, game);
	valid = (map_cpy[game->exit.y][game->exit.x] == 'F');
	i = 0;
	while (i < game->map_height && valid)
	{
		j = 0;
		while (j < game->map_width && valid)
		{
			if (map_cpy[i][j] == 'C')
				valid = 0;
			j++;
		}
		i++;
	}
	free_map(map_cpy, game->map_height);
	return (valid);
}
