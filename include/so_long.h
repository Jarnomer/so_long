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

# include <MLX42.h>
# include <libft.h>
# include <textures.h>
# include <error.h>

# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <time.h>

# define ENEMY_FREQUENCY 20  // 20 -> 1 enemy / 20 floor tiles ...
# define ENEMY_MOVE_CHANCE 3 // 2 = 50%, 3 = 67%, 4 = 75% ...

typedef enum e_element
{
	MAP_PLAYER = 80,
	MAP_ENEMY = 88,
	MAP_PICKUP = 67,
	MAP_FLOOR = 48,
	MAP_WALL = 49,
	MAP_EXIT = 69
}	t_element;

typedef enum e_movement
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
}	t_movement;

typedef struct s_mapinfo
{
	int		width;
	int		height;
	int		fd;
	char	*file;
	int		pickups;
	int		players;
	int		exits;
	char	*buff;
	char	*read;
	char	*temp;
	char	**matrix;
	char	**duplex;
	bool	is_escapable;
	int		exit_x;
	int		exit_y;
	int		player_x;
	int		player_y;
}	t_mapinfo;

typedef struct s_solong
{
	int			screen_width;
	int			screen_height;
	int			cellsize;
	t_mapinfo	*map;
	mlx_t		*mlx;
	int			moves_count;
	mlx_image_t	*moves_display;
	mlx_image_t	*asset[GAME_ASSETS];
	t_animation	anim;
}	t_solong;

void	init_game(t_solong *game, char *file);
void	open_map(t_mapinfo *map, t_solong *game);
void	read_map(t_mapinfo *map, t_solong *game);
void	test_map(t_mapinfo *map, t_solong *game);
void	load_assets(t_solong *game);
void	draw_assets(t_solong *game);
void	play_game(t_solong *game);
void	error_exit(int errcode, char *errmsg, t_solong *game);
void	self_destruct(t_solong *game);
void	print_moves(int moves, t_solong *game);
void	animate_player(void *param);
void	move_enemies(void *param);
void	close_window(void *param);
int		random_number(int modulator);
void	safe_draw(t_image i, int x, int y, t_solong *game);
int		get_floor_tiles(char **matrix);

#endif
