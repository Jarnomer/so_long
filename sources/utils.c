/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:19:15 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/18 20:30:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	random_number(int modulator)
{
	srand((unsigned int)time(NULL));
	return (rand() % modulator);
}

void	safe_draw(t_image i, int x, int y, t_solong *game)
{
	x *= game->cellsize;
	y *= game->cellsize;
	if (mlx_image_to_window(game->mlx, game->asset[i], x, y) == -1)
		error_exit(ERR_MLX, MSG_MLX, game);
}

void	close_window(void *param)
{
	t_solong	*game;

	game = param;
	mlx_close_window(game->mlx);
	self_destruct(game);
	exit(NOERROR);
}

int	get_floor_tiles(char **matrix)
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
