/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:14:04 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/17 18:37:45 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/include/MLX42/MLX42.h"

# include <libft.h>
# include <textures.h>
# include <error.h>

# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef enum e_element
{
	PLAYER = 80,
	PICKUP = 67,
	FLOOR = 48,
	WALL = 49,
	EXIT = 69
}	t_element;

typedef struct s_mapinfo
{
	int		fd;
	int		width;
	int		height;
	int		pickups;
	int		players;
	int		exits;
	char	*file;
	char	*buff;
	char	*read;
	char	*temp;
	char	**matrix;
	char	**duplex;
	bool	is_escapable;
	int		exit_x;
	int		exit_y;
	int		play_x;
	int		play_y;
	int		moves;
}	t_mapinfo;

typedef struct s_solong
{
	int			width;
	int			height;
	int			cellsize;
	t_mapinfo	*map;
	mlx_t		*mlx;
	mlx_image_t	*img[GAME_ASSETS];
}	t_solong;

void	init_game(t_solong *game, char *file);
void	open_map(t_mapinfo *map, t_solong *game);
void	read_map(t_mapinfo *map, t_solong *game);
void	test_map(t_mapinfo *map, t_solong *game);
void	load_assets(t_solong *game);
void	draw_assets(t_solong *game);
void	draw_image(t_image index, int x, int y, t_solong *game);
void	play_game(t_solong *game);
void	error_occured(int errcode, char *errmsg, t_solong *game);
void	self_destruct(t_solong *game);

#endif
