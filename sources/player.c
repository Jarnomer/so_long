/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:19:15 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/15 19:46:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	free_strings(char **cnt, char **res, t_solong *game)
{
	ft_free_single((void **)cnt);
	ft_free_single((void **)res);
	if (game != NULL)
		error_exit(ERR_MEM, MSG_MEM, game);
}

void	print_moves(int moves, t_solong *game)
{
	char	*cnt;
	char	*str;

	if (game->moves_display != NULL)
		mlx_delete_image(game->mlx, game->moves_display);
	cnt = ft_itoa(moves);
	str = ft_strjoin("Moves: ", cnt);
	if (!cnt || !str)
		free_strings(&cnt, &str, game);
	ft_printf("Moves: %d\n", moves);
	game->moves_display = mlx_put_string(game->mlx, str,
			game->cellsize / 6, game->cellsize / 3);
	if (!game->moves_display)
		free_strings(&cnt, &str, game);
	free_strings(&cnt, &str, NULL);
}

static bool	draw_next_frame(t_solong *game)
{
	static double	accumulator = 0.0;
	static const double	frame_interval = 0.15;

	accumulator += game->mlx->delta_time;
	if (accumulator >= frame_interval)
	{
		accumulator -= frame_interval;
		return (true);
	}
	return (false);
}

void	animate_player(void *param)
{
	static bool	increment = true;
	static int	frame = 0;
	t_solong	*game;

	game = param;
	if (draw_next_frame(game))
	{
		if (increment == true)
		{
			draw_image(++frame + IMG_PLAYER,
				game->map->play_x, game->map->play_y, game);
			if (frame + IMG_PLAYER == GAME_ASSETS - 1)
				increment = false;
		}
		else
		{
			draw_image(frame-- + IMG_PLAYER,
				game->map->play_x, game->map->play_y, game);
			if (!frame)
				increment = true;
		}
	}
}
