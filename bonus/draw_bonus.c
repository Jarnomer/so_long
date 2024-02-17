/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:27:48 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/15 14:31:15 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	randomize_wall(int x, int y, t_solong *game)
{
	static int	i = 0;

	if (i % 3 == 0)
		draw_image(TEX_WALL_1, x, y, game);
	else if (i % 3 == 1)
		draw_image(TEX_WALL_2, x, y, game);
	else
		draw_image(TEX_WALL_3, x, y, game);
	i++;
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
			else if (game->map->matrix[y][x] == EMPTY)
				draw_image(TEX_EMPTY, x, y, game);
			else if (game->map->matrix[y][x] == PICKUP)
				draw_image(TEX_PICKUP, x, y, game);
			else if (game->map->matrix[y][x] == EXIT)
				draw_image(TEX_EXIT_CLOSE, x, y, game);
			else if (game->map->matrix[y][x] == PLAYER)
				draw_image(TEX_PLAYER, x, y, game);
		}
	}
}

static void	draw_frame(t_solong *game)
{
	int	i;

	i = 0;
	while (++i < game->map->width - 1)
	{
		draw_image(TEX_EDGE_UP, i, 0, game);
		draw_image(TEX_EDGE_DOWN, i, game->map->height - 1, game);
	}
	draw_image(TEX_CORNER_UL, 0, 0, game);
	draw_image(TEX_CORNER_UR, i, 0, game);
	print_moves(game->map->moves, game);
	i = 0;
	while (++i < game->map->height - 1)
	{
		draw_image(TEX_EDGE_LEFT, 0, i, game);
		draw_image(TEX_EDGE_RIGHT, game->map->width - 1, i, game);
	}
	draw_image(TEX_CORNER_DL, 0, i, game);
	draw_image(TEX_CORNER_DR, game->map->width - 1, i, game);
}

void	draw_image(char *tex, int x, int y, t_solong *game)
{
	t_asset	*tmp;
	int		len;

	if (x != 0)
		x *= game->cellsize;
	if (y != 0)
		y *= game->cellsize;
	tmp = game->assets;
	len = ft_strlen(tex);
	while (tmp)
	{
		if (!ft_strncmp(tex, tmp->file, len))
			break ;
		tmp = tmp->next;
	}
	if (!tmp || !tmp->img)
		error_occured(ERR_TEX, tmp->file, game);
	if (mlx_image_to_window(game->window, tmp->img, x, y) == -1)
		error_occured(ERR_MLX, MSG_MLX, game);
}

void	draw_assets(t_solong *game)
{
	draw_frame(game);
	draw_map(game);
}
