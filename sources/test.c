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

#include <so_long.h>

static void	verify(int c, char *errmsg, t_mapinfo *map, t_solong *game)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (ft_strchr(map->duplex[i], c))
			error_occured(ERR_MAP, errmsg, game);
		i++;
	}
}

static void	clear_exit(char **duplex, int x, int y)
{
	static const char	*cleared_or_exit = "XE";
	static const char	exit_mark = 'Y';

	duplex[y][x] = exit_mark;
	if (ft_strchr(cleared_or_exit, duplex[y + 1][x]))
		clear_exit(duplex, x, y + 1);
	if (ft_strchr(cleared_or_exit, duplex[y - 1][x]))
		clear_exit(duplex, x, y - 1);
	if (ft_strchr(cleared_or_exit, duplex[y][x + 1]))
		clear_exit(duplex, x + 1, y);
	if (ft_strchr(cleared_or_exit, duplex[y][x - 1]))
		clear_exit(duplex, x - 1, y);
	return ;
}

static void	clear_pickups(char **duplex, int x, int y)
{
	static const char	*pickup_or_floor = "0C";
	static const char	pickup_mark = 'X';

	duplex[y][x] = pickup_mark;
	if (ft_strchr(pickup_or_floor, duplex[y + 1][x]))
		clear_pickups(duplex, x, y + 1);
	if (ft_strchr(pickup_or_floor, duplex[y - 1][x]))
		clear_pickups(duplex, x, y - 1);
	if (ft_strchr(pickup_or_floor, duplex[y][x + 1]))
		clear_pickups(duplex, x + 1, y);
	if (ft_strchr(pickup_or_floor, duplex[y][x - 1]))
		clear_pickups(duplex, x - 1, y);
	return ;
}

void	test_map(t_mapinfo *map, t_solong *game)
{
	clear_pickups(map->duplex, map->play_x, map->play_y);
	verify(PICKUP, MSG_PICKUP, map, game);
	clear_exit(map->duplex, map->play_x, map->play_y);
	verify(EXIT, MSG_EXIT, map, game);
}
