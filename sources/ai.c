/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:00:22 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/17 14:00:24 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	set_game_over(void *param)
{
	t_solong	*game;

	game = param;
	ft_printf("%sYou lost the game, the skeletons got you!\n%s",
		BOLD_RED, RESET);
	mlx_close_window(game->mlx);
	self_destruct(game);
	exit(NOERROR);
}

static void	draw_floor(int dst_y, int dst_x, t_solong *game)
{
	draw_image(IMG_FLOOR, dst_x, dst_y, game);
	game->map->matrix[dst_y][dst_x] = MAP_FLOOR;
}

static void	move_enemy(int dst_y, int dst_x, int direction, t_solong *game)
{
	if (dst_y == game->map->play_y && dst_x == game->map->play_x)
		set_game_over(game);
	else if (game->map->matrix[dst_y][dst_x] != MAP_FLOOR)
		return ;
	else if (direction == MOVE_UP)
		draw_floor(dst_y - 1, dst_x, game);
	if (direction == MOVE_DOWN)
		draw_floor(dst_y + 1, dst_x, game);
	else if (direction == MOVE_LEFT)
		draw_floor(dst_y, dst_x + 1, game);
	else if (direction == MOVE_RIGHT)
		draw_floor(dst_y, dst_x - 1, game);
	draw_image(IMG_ENEMY, dst_x, dst_y, game);
	game->map->matrix[dst_y][dst_x] = MAP_ENEMY;
}

static void	randomize_movement(int y, int x, t_solong *game)
{
	int	direction;

	direction = rand() % 5;
	if (direction == MOVE_UP)
		move_enemy(y - 1, x, direction, game);
	else if (direction == MOVE_DOWN)
		move_enemy(y + 1, x, direction, game);
	else if (direction == MOVE_LEFT)
		move_enemy(y, x + 1, direction, game);
	else if (direction == MOVE_RIGHT)
		move_enemy(y, x - 1, direction, game);
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
			if (game->map->matrix[y][x] == MAP_ENEMY)
			{
				while (rand() % 4 != 0)
					randomize_movement(y, x, game);
			}
		}
	}
}
