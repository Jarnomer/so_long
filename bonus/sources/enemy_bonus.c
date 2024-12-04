/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:00:38 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/17 14:00:44 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static inline int	randomize_coordinates(int treshold)
{
	return (rand() % treshold);
}

static int	get_empties(char **matrix)
{
	int	cnt;
	int	i;
	int	j;

	cnt = 0;
	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == EMPTY)
				cnt++;
			j++;
		}
		i++;
	}
	return (cnt);
}

void	draw_enemies(t_solong *game)
{
	int	cnt;
	int	x;
	int	y;
	int	i;

	i = 0;
	cnt = get_empties(game->map->matrix) / ENEMY_FREQUENCY;
	while (i < cnt)
	{
		x = randomize_coordinates(game->map->width);
		y = randomize_coordinates(game->map->height);
		if (game->map->matrix[y][x] != EMPTY)
			continue ;
		else if (rand() % 4 != 0)
		{
			draw_image(TEX_ENEMY, x, y, game);
			game->map->matrix[y][x] = ENEMY;
		}
		i++;
	}
}
