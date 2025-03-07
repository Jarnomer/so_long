/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:19:15 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/18 20:30:55 by jmertane         ###   ########.fr       */
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

void	animate_player(void *param)
{
	t_solong	*game;
	t_animation	*anim;

	game = param;
	anim = &game->anim;
	anim->player_time += game->mlx->delta_time;
	if (anim->player_time >= PLAYER_FRAME_INTERVAL)
	{
		anim->player_time -= PLAYER_FRAME_INTERVAL;
		anim->player_frame += anim->direction;
		if (anim->player_frame >= MAX_FRAMES - 1
			|| anim->player_frame <= 0)
		{
			anim->direction *= -1;
			anim->player_frame += anim->direction;
		}
	}
	safe_draw(IMG_PLAYER + anim->player_frame,
		game->map->player_x, game->map->player_y, game);
}
