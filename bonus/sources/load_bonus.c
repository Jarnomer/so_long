/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:42:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/17 18:46:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	alter_window_settings(t_mapinfo *map, t_solong *game)
{
	if (game->height / map->height < game->width / map->width)
		game->cellsize = game->height / map->height;
	else
		game->cellsize = game->width / map->width;
	mlx_set_window_size(game->window,
		game->cellsize * map->width,
		game->cellsize * map->height);
	mlx_set_window_limit(game->window,
		game->cellsize * map->width,
		game->cellsize * map->height,
		game->width, game->height);
}

static void	append_asset(t_asset **lst, t_asset *new, char *file)
{
	t_asset	*tmp;

	new->fd = -1;
	new->file = file;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void	create_asset_list(t_solong *game)
{
	t_asset	*new;
	int		i;

	i = 0;
	while (i < GAME_ASSETS)
	{
		new = ft_calloc(1, sizeof(t_asset));
		if (!new)
			error_occured(ERR_MEM, MSG_MEM, game);
		append_asset(&game->assets, new, game->images[i]);
		new->fd = open(new->file, O_RDONLY);
		if (new->fd == -1)
			error_occured(ERR_TEX, new->file, game);
		new->tex = mlx_load_png(new->file);
		if (!new->tex)
			error_occured(ERR_MLX, MSG_MLX, game);
		new->img = mlx_texture_to_image(game->window, new->tex);
		if (!new->img)
			error_occured(ERR_MLX, MSG_MLX, game);
		if (game->cellsize != CELL_SIZE && !mlx_resize_image(
				new->img, game->cellsize, game->cellsize))
			error_occured(ERR_MLX, MSG_MLX, game);
		i++;
	}
}

static void	insert_filenames(t_solong *game)
{
	game->images[0] = TEX_CORNER_UL;
	game->images[1] = TEX_CORNER_UR;
	game->images[2] = TEX_CORNER_DL;
	game->images[3] = TEX_CORNER_DR;
	game->images[4] = TEX_EDGE_UP;
	game->images[5] = TEX_EDGE_DOWN;
	game->images[6] = TEX_EDGE_LEFT;
	game->images[7] = TEX_EDGE_RIGHT;
	game->images[8] = TEX_EMPTY;
	game->images[9] = TEX_WALL_1;
	game->images[10] = TEX_WALL_2;
	game->images[11] = TEX_WALL_3;
	game->images[12] = TEX_PICKUP;
	game->images[13] = TEX_EXIT_OPEN;
	game->images[14] = TEX_EXIT_CLOSE;
	game->images[15] = TEX_ENEMY;
	game->images[16] = TEX_PLAYER;
	game->images[17] = TEX_GLOW_1;
	game->images[18] = TEX_GLOW_2;
	game->images[19] = TEX_GLOW_3;
	game->images[20] = TEX_GLOW_4;
	game->images[21] = TEX_GLOW_5;
	game->images[22] = TEX_GLOW_6;
	game->images[23] = TEX_GLOW_7;
	game->images[24] = TEX_GLOW_8;
}

void	load_assets(t_solong *game)
{
	game->window = mlx_init(
			CELL_SIZE * game->map->width,
			CELL_SIZE * game->map->height,
			WINDOW_TITLE, false);
	if (!game->window)
		error_occured(ERR_MLX, MSG_MLX, game);
	mlx_get_monitor_size(0, &game->width, &game->height);
	game->images = ft_calloc(GAME_ASSETS + 1, sizeof(char *));
	if (!game->images)
		error_occured(ERR_MEM, MSG_MEM, game);
	if ((game->map->width * CELL_SIZE > game->width)
		|| (game->map->height * CELL_SIZE > game->height))
		alter_window_settings(game->map, game);
	insert_filenames(game);
	create_asset_list(game);
}
