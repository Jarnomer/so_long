/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:19:15 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/15 19:46:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	free_strings(char **cnt, char **res, t_solong *game)
{
	free(*cnt);
	*cnt = NULL;
	free(*res);
	*res = NULL;
	if (game != NULL)
		error_occured(ERR_MEM, MSG_MEM, game);
}

void	print_moves(int moves, t_solong *game)
{
	char	*cnt;
	char	*str;

	if (game->counter != NULL)
		mlx_delete_image(game->window, game->counter);
	cnt = ft_itoa(moves);
	str = ft_strjoin("Moves: ", cnt);
	if (!cnt || !str)
		free_strings(&cnt, &str, game);
	game->counter = mlx_put_string(game->window, str,
			game->cellsize / 6, game->cellsize / 3);
	if (!game->counter)
		free_strings(&cnt, &str, game);
	free_strings(&cnt, &str, NULL);
}

static int	update_animation(t_solong *game)
{
	static float	mod = ANIMATE_TIMER;

	game->uptime = mlx_get_time();
	if (game->uptime >= game->timer)
	{
		game->timer += mod;
		return (0);
	}
	return (1);
}

void	animate_eyes(void *param)
{
	static bool	increase = true;
	static int	i = 0;
	t_solong	*game;

	game = param;
	if (update_animation(game) == 0)
	{
		if (increase == true)
		{
			draw_image(game->images[++i + 15],
				game->map->play_x, game->map->play_y, game);
			if (i + 15 == GAME_ASSETS - 1)
				increase = false;
		}
		else
		{
			draw_image(game->images[i-- + 15],
				game->map->play_x, game->map->play_y, game);
			if (i == 0)
				increase = true;
		}
	}
}
