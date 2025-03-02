/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:12:17 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/02 14:50:49 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	process_line(char *line, int *width, int *height)
{
	char	*newline;

	if (line[0] != '\n')
	{
		newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';
		*width = ft_strlen(line);
		(*height)++;
	}
}

void	count_map_size(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		height;
	int		width;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	height = 0;
	width = 0;
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, &width, &height);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game->map_width = width;
	game->map_height = height;
}

static int	read_map_lines(int fd, t_game *game)
{
	char	*line;
	int		i;
	char	*newline;

	i = 0;
	line = get_next_line(fd);
	while (line && i < game->map_height)
	{
		if (line[0] != '\n')
		{
			newline = ft_strchr(line, '\n');
			if (newline)
				*newline = '\0';
			game->map[i] = ft_strdup(line);
			if (!game->map[i])
				return (free(line), close(fd), 0);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	close(fd);
	return (1);
}

int	parse_map(char *filename, t_game *game)
{
	int	fd;

	count_map_size(filename, game);
	if (game->map_height == 0 || game->map_width == 0)
	{
		print_error("Error\nInvalid map size");
		return (0);
	}
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	if (!read_map_lines(fd, game))
	{
		print_error("Error\nFailed to read map data");
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	game->collectibles = 0;
	if (!check_map_rectangular(game))
		return (print_error("Error\nMap is not rectangular"), 0);
	if (!check_map_chars(game))
		return (print_error("Error\nMap contains invalid characters"), 0);
	if (!check_map_walls(game))
		return (print_error("Error\nMap is not surrounded by walls"), 0);
	if (!check_player_exit_collectible(game))
	{
		print_error ("Error\nMap must have 1 "
			"player, 1 exit and at least 1 collectible");
		return (0);
	}
	if (!check_valid_path(game))
	{
		print_error ("Error\nNo valid path from"
			" player to exit or a collectible");
		return (0);
	}
	return (1);
}
