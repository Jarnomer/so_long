/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:00:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/17 14:00:24 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	close_window(void *param)
{
	t_solong	*game;

	game = param;
	mlx_close_window(game->window);
	self_destruct(game);
	exit(NOERROR);
}

static void	draw_empty(int y, int x, t_solong *game)
{
	draw_image(TEX_EMPTY, x, y, game);
	game->map->matrix[y][x] = EMPTY;
}

static void	move_enemy(int dst_y, int dst_x, int direct, t_solong *game)
{
	if (dst_y == game->map->play_y && dst_x == game->map->play_x)
		close_window(game);
	else if (game->map->matrix[dst_y][dst_x] != EMPTY)
		return ;
	if (direct == 0)
		draw_empty(dst_y + 1, dst_x, game);
	else if (direct == 1)
		draw_empty(dst_y, dst_x + 1, game);
	else if (direct == 2)
		draw_empty(dst_y - 1, dst_x, game);
	else if (direct == 3)
		draw_empty(dst_y, dst_x - 1, game);
	draw_image(TEX_ENEMY, dst_x, dst_y, game);
	game->map->matrix[dst_y][dst_x] = ENEMY;
}

static void	randomize_movement(int y, int x, t_solong *game)
{
	int	direct;

	if (rand() % 100 != 0)
		return ;
	direct = rand() % 4;
	if (direct == 0)
		move_enemy(y - 1, x, direct, game);
	else if (direct == 1)
		move_enemy(y, x - 1, direct, game);
	else if (direct == 2)
		move_enemy(y + 1, x, direct, game);
	else if (direct == 3)
		move_enemy(y, x + 1, direct, game);
}

void	move_enemies(void *param)
{
	t_solong	*game;
	int			x;
	int			y;

	y = 0;
	game = (t_solong *)param;
	while (++y < game->map->height - 1)
	{
		x = 0;
		while (++x < game->map->width - 1)
		{
			if (game->map->matrix[y][x] == ENEMY)
				while (rand() % 4 != 0)
					randomize_movement(y, x, game);
		}
	}
}
