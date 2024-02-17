/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:44:48 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/11 11:05:47 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_remains(t_mapinfo *map, t_solong *game)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (ft_strchr(map->duplex[i], PICKUP)
			&& map->escstat == false)
			error_logger(MSG_PICK, game);
		else if (ft_strchr(map->duplex[i], EXIT)
			&& map->escstat == true)
			error_logger(MSG_PATH, game);
		i++;
	}
}

static void	clear_exit(char **temp, int x, int y)
{
	temp[y][x] = 'Y';
	if (ft_strchr("XE", temp[y + 1][x]))
		clear_exit(temp, x, y + 1);
	if (ft_strchr("XE", temp[y - 1][x]))
		clear_exit(temp, x, y - 1);
	if (ft_strchr("XE", temp[y][x + 1]))
		clear_exit(temp, x + 1, y);
	if (ft_strchr("XE", temp[y][x - 1]))
		clear_exit(temp, x - 1, y);
	return ;
}

static void	clear_pickups(char **temp, int x, int y)
{
	temp[y][x] = 'X';
	if (ft_strchr("0C", temp[y + 1][x]))
		clear_pickups(temp, x, y + 1);
	if (ft_strchr("0C", temp[y - 1][x]))
		clear_pickups(temp, x, y - 1);
	if (ft_strchr("0C", temp[y][x + 1]))
		clear_pickups(temp, x + 1, y);
	if (ft_strchr("0C", temp[y][x - 1]))
		clear_pickups(temp, x - 1, y);
	return ;
}

static void	duplicate_map(t_mapinfo *map, t_solong *game)
{
	int	i;

	map->duplex = ft_calloc((map->height + 1), sizeof(char *));
	if (!map->duplex)
		error_occured(ERR_MEM, MSG_MEM, game);
	i = 0;
	while (i < map->height)
	{
		map->duplex[i] = ft_strdup(map->matrix[i]);
		if (!map->duplex[i])
			error_occured(ERR_MEM, MSG_MEM, game);
		i++;
	}
}

void	test_map(t_mapinfo *map, t_solong *game)
{
	duplicate_map(map, game);
	clear_pickups(map->duplex, map->play_x, map->play_y);
	check_remains(map, game);
	map->escstat = true;
	clear_exit(map->duplex, map->play_x, map->play_y);
	check_remains(map, game);
	if (map->errstat == true)
		error_occured(ERR_MAP, NULL, game);
	map->escstat = false;
}
