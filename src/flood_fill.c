/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:14:27 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/02 14:44:11 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	**create_map_copy(t_game *game)
{
	char	**map_cpy;
	int		i;

	map_cpy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_cpy)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		map_cpy[i] = ft_strdup(game->map[i]);
		if (!map_cpy[i])
		{
			free_map(map_cpy, i);
			return (NULL);
		}
		i++;
	}
	map_cpy[i] = NULL;
	return (map_cpy);
}

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height
		|| map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}
