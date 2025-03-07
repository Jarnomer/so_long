/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:00:38 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/17 14:00:44 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static inline int	randomize_coordinates(int treshold)
{
	return (rand() % treshold);
}

static int	get_floor_tiles(char **matrix)
{
	int	amount;
	int	i;
	int	j;

	amount = 0;
	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == MAP_FLOOR)
				amount++;
			j++;
		}
		i++;
	}
	return (amount);
}

void	draw_enemies(t_solong *game)
{
	int	amount;
	int	x;
	int	y;
	int	i;

	i = 0;
	amount = get_floor_tiles(game->map->matrix) / ENEMY_FREQUENCY;
	while (i < amount)
	{
		x = randomize_coordinates(game->map->width);
		y = randomize_coordinates(game->map->height);
		if (game->map->matrix[y][x] != MAP_FLOOR)
			continue ;
		else if (rand() % 4 != 0)
		{
			draw_image(IMG_ENEMY, x, y, game);
			game->map->matrix[y][x] = MAP_FLOOR;
		}
		i++;
	}
}
