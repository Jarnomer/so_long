/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:50:15 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/12 07:10:28 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool	game_over(t_mapinfo *map)
{
	if (map->matrix[map->play_y][map->play_x] == ENEMY
		|| (map->matrix[map->play_y][map->play_x] == EXIT
		&& map->escstat == true))
		return (true);
	return (false);
}

static void	close_window(void *param)
{
	t_solong	*game;

	game = param;
	mlx_close_window(game->window);
	self_destruct(game);
	exit(NOERROR);
}

static void	move_player(int dst_y, int dst_x, t_solong *game)
{
	if (game->map->matrix[dst_y][dst_x] == WALL
		|| (game->map->matrix[dst_y][dst_x] == EXIT
		&& game->map->escstat == false))
		return ;
	draw_image(TEX_EMPTY, game->map->play_x, game->map->play_y, game);
	draw_image(TEX_PLAYER, dst_x, dst_y, game);
	print_moves(++game->map->moves, game);
	game->map->play_x = dst_x;
	game->map->play_y = dst_y;
	if (game->map->matrix[dst_y][dst_x] == PICKUP)
	{
		game->map->matrix[dst_y][dst_x] = EMPTY;
		game->map->pickups--;
		if (!game->map->pickups)
		{
			draw_image(TEX_EXIT_OPEN, game->map->exit_x,
				game->map->exit_y, game);
			game->map->escstat = true;
		}
	}
}

static void	control_keys(mlx_key_data_t keydata, void *param)
{
	t_solong	*game;
	t_mapinfo	*map;

	game = param;
	map = game->map;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			close_window(game);
		else if (keydata.key == MLX_KEY_W)
			move_player(map->play_y - 1, map->play_x, game);
		else if (keydata.key == MLX_KEY_A)
			move_player(map->play_y, map->play_x - 1, game);
		else if (keydata.key == MLX_KEY_S)
			move_player(map->play_y + 1, map->play_x, game);
		else if (keydata.key == MLX_KEY_D)
			move_player(map->play_y, map->play_x + 1, game);
	}
	if (game_over(game->map))
		close_window(game);
}

void	play_game(t_solong *game)
{
	mlx_close_hook(game->window, &close_window, game);
	mlx_key_hook(game->window, &control_keys, game);
	mlx_loop_hook(game->window, animate_eyes, game);
	mlx_loop_hook(game->window, move_enemies, game);
	mlx_loop(game->window);
}
