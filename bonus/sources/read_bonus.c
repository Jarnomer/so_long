/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:38:47 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/11 21:18:27 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	update_exit_info(int row, int col, t_mapinfo *map)
{
	map->exit_x = col;
	map->exit_y = row;
	map->exits++;
}

static void	update_player_info(int row, int col, t_mapinfo *map)
{
	map->play_x = col;
	map->play_y = row;
	map->players++;
}

static void	check_chars(t_mapinfo *map, int row, t_solong *game)
{
	int	i;

	i = -1;
	while (map->matrix[row][++i])
	{
		if (map->matrix[row][i] == EMPTY
			|| map->matrix[row][i] == WALL)
			continue ;
		else if (map->matrix[row][i] == PICKUP)
			map->pickups++;
		else if (map->matrix[row][i] == PLAYER)
			update_player_info(row, i, map);
		else if (map->matrix[row][i] == EXIT)
			update_exit_info(row, i, map);
		else
			error_logger(MSG_ELEM, game);
	}
}

static void	check_walls(t_mapinfo *map, int row, t_solong *game)
{
	int	i;

	i = 0;
	if (map->matrix[row][0] != WALL
		|| map->matrix[row][map->width - 1] != WALL)
		error_logger(MSG_WALL, game);
	else if (!row || !map->matrix[row + 1])
		while (map->matrix[row][i])
			if (map->matrix[row][i++] != WALL)
				error_logger(MSG_WALL, game);
}

void	read_map(t_mapinfo *map, t_solong *game)
{
	while (map->matrix[map->height])
	{
		map->width = ft_strlen(map->matrix[map->height]);
		if (map->height != 0)
			if (ft_strlen(map->matrix[map->height - 1])
				!= (size_t)map->width)
				error_logger(MSG_RECT, game);
		check_walls(game->map, map->height, game);
		check_chars(game->map, map->height, game);
		map->height++;
	}
	if (map->players != 1)
		error_logger(MSG_PLAYER, game);
	if (map->exits != 1)
		error_logger(MSG_EXIT, game);
	if (!map->pickups)
		error_logger(MSG_PICKUP, game);
	if (map->errstat == true)
		error_occured(ERR_MAP, NULL, game);
}
