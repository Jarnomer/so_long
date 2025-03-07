/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:27:48 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/17 18:47:24 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	draw_enemies(t_solong *game)
{
	int	amount;
	int	x;
	int	y;
	int	i;

	i = 0;
	amount = get_floor_tiles(game->map->matrix) / ENEMY_FREQUENCY;
	while (i < amount)
	{
		x = random_number(game->map->width);
		y = random_number(game->map->height);
		if (game->map->matrix[y][x] != MAP_FLOOR)
			continue ;
		safe_draw(IMG_ENEMY, x, y, game);
		game->map->matrix[y][x] = MAP_ENEMY;
		i++;
	}
}

static void	randomize_wall(int x, int y, t_solong *game)
{
	int	i;

	i = random_number(3);
	if (i % 3 == 0)
		safe_draw(IMG_WALL_1, x, y, game);
	else if (i % 3 == 1)
		safe_draw(IMG_WALL_2, x, y, game);
	else
		safe_draw(IMG_WALL_3, x, y, game);
}

static void	draw_map(t_solong *game)
{
	int	x;
	int	y;

	y = 0;
	while (++y < game->map->height - 1)
	{
		x = 0;
		while (++x < game->map->width - 1)
		{
			if (game->map->matrix[y][x] == MAP_WALL)
				randomize_wall(x, y, game);
			else if (game->map->matrix[y][x] == MAP_FLOOR)
				safe_draw(IMG_FLOOR, x, y, game);
			else if (game->map->matrix[y][x] == MAP_PICKUP)
				safe_draw(IMG_PICKUP, x, y, game);
			else if (game->map->matrix[y][x] == MAP_EXIT)
				safe_draw(IMG_EXIT_CLOSE, x, y, game);
			else if (game->map->matrix[y][x] == MAP_PLAYER)
				safe_draw(IMG_PLAYER, x, y, game);
		}
	}
}

static void	draw_frame(t_solong *game)
{
	int	i;

	i = 0;
	while (++i < game->map->width - 1)
	{
		safe_draw(IMG_EDGE_UP, i, 0, game);
		safe_draw(IMG_EDGE_DOWN, i, game->map->height - 1, game);
	}
	safe_draw(IMG_CORNER_UL, 0, 0, game);
	safe_draw(IMG_CORNER_UR, i, 0, game);
	i = 0;
	while (++i < game->map->height - 1)
	{
		safe_draw(IMG_EDGE_LEFT, 0, i, game);
		safe_draw(IMG_EDGE_RIGHT, game->map->width - 1, i, game);
	}
	safe_draw(IMG_CORNER_DL, 0, i, game);
	safe_draw(IMG_CORNER_DR, game->map->width - 1, i, game);
}

void	draw_assets(t_solong *game)
{
	draw_frame(game);
	draw_map(game);
	draw_enemies(game);
}
