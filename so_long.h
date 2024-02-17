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

# include "./mlx/include/MLX42/MLX42.h"

# include "./libft/libft.h"
# include "textures.h"
# include "styles.h"
# include "error.h"

# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define WINDOW_TITLE	"so_long"

enum e_mapcodes
{
	PLAYER = 80,
	PICKUP = 67,
	EMPTY = 48,
	WALL = 49,
	EXIT = 69
};

typedef struct s_asset
{
	int				fd;
	void			*tex;
	void			*img;
	char			*file;
	struct s_asset	*next;
}	t_asset;

typedef struct s_mapinfo
{
	int		fd;
	int		width;
	int		height;
	int		exits;
	int		players;
	int		pickups;
	int		moves;
	char	*file;
	char	*buff;
	char	*read;
	char	*temp;
	char	**matrix;
	char	**duplex;
	bool	errstat;
	bool	escstat;
	int		play_x;
	int		play_y;
	int		exit_x;
	int		exit_y;
}	t_mapinfo;

typedef struct s_solong
{
	char				**images;
	void				*window;
	int					width;
	int					height;
	int					cellsize;
	struct s_mapinfo	*map;
	struct s_asset		*assets;
}	t_solong;

void	init_game(t_solong *game, char *file);
void	open_map(t_mapinfo *map, t_solong *game);
void	read_map(t_mapinfo *map, t_solong *game);
void	test_map(t_mapinfo *map, t_solong *game);
void	load_assets(t_solong *game);
void	draw_assets(t_solong *game);
void	draw_image(char *tex, int x, int y, t_solong *game);
void	play_game(t_solong *game);
void	error_logger(char *errmsg, t_solong *game);
void	error_occured(int errcode, char *errmsg, t_solong *game);
void	self_destruct(t_solong *game);

#endif
