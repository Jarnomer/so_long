/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:38:47 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/11 11:00:39 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_exit_info(int col, int row, t_mapinfo *map)
{
	map->exit_x = col;
	map->exit_y = row;
	map->exits++;
}

static void	update_player_info(int col, int row, t_mapinfo *map)
{
	map->play_x = col;
	map->play_y = row;
	map->players++;
}

static void	check_elements(t_mapinfo *map, int row, t_solong *game)
{
	int	i;

	i = 0;
	while (map->matrix[row][i])
	{
		if (map->matrix[row][i] == EMPTY
			|| map->matrix[row][i] == WALL)
			continue ;
		else if (map->matrix[row][i] == PICKUP)
			map->pickups++;
		else if (map->matrix[row][i] == PLAYER)
			update_player_info(i, row, map);
		else if (map->matrix[row][i] == EXIT)
			update_exit_info(i, row, map);
		else
			error_occured(ERR_MAP, MSG_ELEM, game);
		i++;
	}
}

static void	check_walls(t_mapinfo *map, int row, t_solong *game)
{
	int	i;

	i = 0;
	if (map->matrix[row][0] != WALL
		|| map->matrix[row][map->width - 1] != WALL)
		error_occured(ERR_MAP, MSG_WALL, game);
	else if (!row || !map->matrix[row + 1])
	{
		while (map->matrix[row][i])
		{
			if (map->matrix[row][i++] != WALL)
				error_occured(ERR_MAP, MSG_WALL, game);
		}
	}
}

void	read_map(t_mapinfo *map, t_solong *game)
{
	int	prev_len;

	prev_len = -1;
	while (map->matrix[map->height])
	{
		map->width = ft_strlen(map->matrix[map->height]);
		if (map->height > 0)
			prev_len = ft_strlen(map->matrix[map->height - 1]);
		if (prev_len != -1 && prev_len != (size_t)map->width)
			error_occured(ERR_MAP, MSG_RECT, game);
		check_walls(game->map, map->height, game);
		check_elements(game->map, map->height, game);
		map->height++;
	}
	if (map->players != 1)
		error_occured(ERR_MAP, MSG_PLAYER, game);
	else if (map->exits != 1)
		error_occured(ERR_MAP, MSG_EXIT, game);
	else if (!map->pickups)
		error_occured(ERR_MAP, MSG_PICKUP, game);
}
