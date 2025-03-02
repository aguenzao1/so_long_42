/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:47:53 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/02 14:32:47 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map_rectangular(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if (ft_strlen(game->map[i]) != (size_t)game->map_width)
			return (0);
		i++;
	}
	return (1);
}

int	check_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(&filename[len - 4], ".ber", 4) != 0)
		return (0);
	return (1);
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

int	check_for_invalid_newlines(char *filename)
{
	int		fd;
	char	*line;
	int		i;
	int		empty_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error("Error\nFailed to open map file"), 1);
	empty_line = 0;
	i = 0;
	line = get_next_line(fd);
	if (line && line[0] == '\n')
		empty_line = 1;
	while (line)
	{
		if (i > 0 && line[0] == '\n')
			empty_line = 1;
		else if (i > 0 && line[0] != '\0' && line[1] == '\n'
			&& ft_strlen(line) == 2)
			empty_line = 1;
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (close(fd), empty_line);
}
