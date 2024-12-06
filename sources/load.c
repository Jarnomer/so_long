/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:42:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/17 18:46:35 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static const char *const	g_textures[GAME_ASSETS] = {
	TEX_CORNER_UL,
	TEX_CORNER_UR,
	TEX_CORNER_DL,
	TEX_CORNER_DR,
	TEX_EDGE_UP,
	TEX_EDGE_DOWN,
	TEX_EDGE_LEFT,
	TEX_EDGE_RIGHT,
	TEX_FLOOR,
	TEX_WALL_1,
	TEX_WALL_2,
	TEX_WALL_3,
	TEX_PICKUP,
	TEX_EXIT_OPEN,
	TEX_EXIT_CLOSE,
	TEX_ENEMY,
	TEX_PLAYER,
	TEX_GLOW_1,
	TEX_GLOW_2,
	TEX_GLOW_3,
	TEX_GLOW_4,
	TEX_GLOW_5,
	TEX_GLOW_6,
	TEX_GLOW_7,
	TEX_GLOW_8
};

static void	load_textures(t_solong *game)
{
	mlx_texture_t	*tex;
	int				fd;
	int				i;

	i = 0;
	while (i < GAME_ASSETS)
	{
		fd = open(g_textures[i], O_RDONLY);
		if (fd == -1)
			error_occured(ERR_TEX, (char *)g_textures[i], game);
		tex = mlx_load_png(g_textures[i]);
		if (!tex)
			error_occured(ERR_MLX, MSG_MLX, game);
		game->asset[i] = mlx_texture_to_image(game->mlx, tex);
		if (!game->asset[i])
			error_occured(ERR_MLX, MSG_MLX, game);
		if (game->cellsize != CELL_SIZE && !mlx_resize_image(
				game->asset[i], game->cellsize, game->cellsize))
			error_occured(ERR_MLX, MSG_MLX, game);
		mlx_delete_texture(tex);
		close(fd);
		i++;
	}
}

static void	alter_window_settings(t_mapinfo *map, t_solong *game)
{
	if (game->screen_height / map->height < game->screen_width / map->width)
		game->cellsize = game->screen_height / map->height;
	else
		game->cellsize = game->screen_width / map->width;
	mlx_set_window_size(game->mlx,
		game->cellsize * map->width,
		game->cellsize * map->height);
	mlx_set_window_limit(game->mlx,
		game->cellsize * map->width,
		game->cellsize * map->height,
		game->screen_width, game->screen_height);
}

void	load_assets(t_solong *game)
{
	int	width;
	int	height;

	width = CELL_SIZE * game->map->width;
	height = CELL_SIZE * game->map->height;
	game->mlx = mlx_init(width, height, "so_long", false);
	if (!game->mlx)
		error_occured(ERR_MLX, MSG_MLX, game);
	mlx_get_monitor_size(0, &game->screen_width, &game->screen_height);
	if (width > game->screen_width || height > game->screen_height)
		alter_window_settings(game->map, game);
	load_textures(game);
}
