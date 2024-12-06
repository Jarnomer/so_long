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

static void	randomize_wall(int x, int y, t_solong *game)
{
	int	i;

	i = rand() % 3;
	if (i % 3 == 0)
		draw_image(IMG_WALL_1, x, y, game);
	else if (i % 3 == 1)
		draw_image(IMG_WALL_2, x, y, game);
	else
		draw_image(IMG_WALL_3, x, y, game);
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
			if (game->map->matrix[y][x] == WALL)
				randomize_wall(x, y, game);
			else if (game->map->matrix[y][x] == FLOOR)
				draw_image(IMG_FLOOR, x, y, game);
			else if (game->map->matrix[y][x] == PICKUP)
				draw_image(IMG_PICKUP, x, y, game);
			else if (game->map->matrix[y][x] == EXIT)
				draw_image(IMG_EXIT_CLOSE, x, y, game);
			else if (game->map->matrix[y][x] == PLAYER)
				draw_image(IMG_PLAYER, x, y, game);
		}
	}
}

static void	draw_frame(t_solong *game)
{
	int	i;

	i = 0;
	while (++i < game->map->width - 1)
	{
		draw_image(IMG_EDGE_UP, i, 0, game);
		draw_image(IMG_EDGE_DOWN, i, game->map->height - 1, game);
	}
	draw_image(IMG_CORNER_UL, 0, 0, game);
	draw_image(IMG_CORNER_UR, i, 0, game);
	i = 0;
	while (++i < game->map->height - 1)
	{
		draw_image(IMG_EDGE_LEFT, 0, i, game);
		draw_image(IMG_EDGE_RIGHT, game->map->width - 1, i, game);
	}
	draw_image(IMG_CORNER_DL, 0, i, game);
	draw_image(IMG_CORNER_DR, game->map->width - 1, i, game);
}

void	draw_image(t_image i, int x, int y, t_solong *game)
{
	x *= game->cellsize;
	y *= game->cellsize;
	if (mlx_image_to_window(game->mlx, game->asset[i], x, y) == -1)
		error_exit(ERR_MLX, MSG_MLX, game);
}

void	draw_assets(t_solong *game)
{
	draw_frame(game);
	draw_map(game);
	draw_enemies(game);
}
