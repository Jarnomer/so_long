/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:50:15 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/11 21:31:14 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static bool	game_over(t_mapinfo *map, t_solong *game)
{
	if (map->matrix[map->player_y][map->player_x] == MAP_ENEMY)
	{
		ft_printf("%sYou lost the game, the skeletons got you!\n%s",
			BOLD_RED, RESET);
		return (true);
	}
	else if (map->is_escapable == true
		&& map->matrix[map->player_y][map->player_x] == MAP_EXIT)
	{
		ft_printf("%sYou won the game with %d moves!\n%s",
			BOLD_GREEN, game->moves_count, RESET);
		return (true);
	}
	return (false);
}

static void	close_window(void *param)
{
	t_solong	*game;

	game = param;
	mlx_close_window(game->mlx);
	self_destruct(game);
	exit(NOERROR);
}

static void	move_player(int dst_y, int dst_x, t_solong *game)
{
	if (game->map->matrix[dst_y][dst_x] == MAP_WALL
		|| (game->map->matrix[dst_y][dst_x] == MAP_EXIT
		&& game->map->is_escapable == false))
		return ;
	draw_image(IMG_FLOOR, game->map->player_x, game->map->player_y, game);
	draw_image(IMG_PLAYER, dst_x, dst_y, game);
	print_moves(++game->moves_count, game);
	game->map->player_x = dst_x;
	game->map->player_y = dst_y;
	if (game->map->matrix[dst_y][dst_x] == MAP_PICKUP)
	{
		game->map->matrix[dst_y][dst_x] = MAP_FLOOR;
		game->map->pickups--;
		if (!game->map->pickups)
		{
			draw_image(IMG_EXIT_OPEN, game->map->exit_x,
				game->map->exit_y, game);
			game->map->is_escapable = true;
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
		if (keydata.key == MLX_KEY_W)
			move_player(map->player_y - 1, map->player_x, game);
		if (keydata.key == MLX_KEY_A)
			move_player(map->player_y, map->player_x - 1, game);
		if (keydata.key == MLX_KEY_S)
			move_player(map->player_y + 1, map->player_x, game);
		if (keydata.key == MLX_KEY_D)
			move_player(map->player_y, map->player_x + 1, game);
	}
	if (game_over(game->map, game))
		close_window(game);
}

void	play_game(t_solong *game)
{
	mlx_close_hook(game->mlx, &close_window, game);
	mlx_key_hook(game->mlx, &control_keys, game);
	mlx_loop_hook(game->mlx, animate_player, game);
	mlx_loop_hook(game->mlx, move_enemies, game);
	mlx_loop(game->mlx);
}
