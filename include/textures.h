/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:37:09 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/15 19:38:03 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# define GAME_ASSETS	25
# define CELL_SIZE		126

# define PLAYER_FRAME_INTERVAL  0.075
# define GLOW_FRAME_INTERVAL    0.05
# define MAX_FRAMES             8

# define TEX_CORNER_UL		"./textures/corner_up_left.png"
# define TEX_CORNER_UR		"./textures/corner_up_right.png"
# define TEX_CORNER_DL		"./textures/corner_down_left.png"
# define TEX_CORNER_DR		"./textures/corner_down_right.png"
# define TEX_EDGE_UP		"./textures/edge_up.png"
# define TEX_EDGE_DOWN		"./textures/edge_down.png"
# define TEX_EDGE_LEFT		"./textures/edge_left.png"
# define TEX_EDGE_RIGHT		"./textures/edge_right.png"
# define TEX_FLOOR			"./textures/empty.png"
# define TEX_WALL_1			"./textures/wall1.png"
# define TEX_WALL_2			"./textures/wall2.png"
# define TEX_WALL_3			"./textures/wall3.png"
# define TEX_PICKUP			"./textures/pickup.png"
# define TEX_EXIT_OPEN		"./textures/exit_open.png"
# define TEX_EXIT_CLOSE		"./textures/exit_closed.png"
# define TEX_ENEMY			"./textures/enemy.png"
# define TEX_PLAYER			"./textures/player.png"
# define TEX_GLOW_1			"./textures/glow1.png"
# define TEX_GLOW_2			"./textures/glow2.png"
# define TEX_GLOW_3			"./textures/glow3.png"
# define TEX_GLOW_4			"./textures/glow4.png"
# define TEX_GLOW_5			"./textures/glow5.png"
# define TEX_GLOW_6			"./textures/glow6.png"
# define TEX_GLOW_7			"./textures/glow7.png"
# define TEX_GLOW_8			"./textures/glow8.png"

typedef struct s_animation
{
	double	player_time;
	int		player_frame;
	int		direction;
	double	exit_time;
	int		exit_frame;
	bool	exit_active;
	double	effect_duration;
}	t_animation;

typedef enum e_image
{
	IMG_CORNER_UL,
	IMG_CORNER_UR,
	IMG_CORNER_DL,
	IMG_CORNER_DR,
	IMG_EDGE_UP,
	IMG_EDGE_DOWN,
	IMG_EDGE_LEFT,
	IMG_EDGE_RIGHT,
	IMG_FLOOR,
	IMG_WALL_1,
	IMG_WALL_2,
	IMG_WALL_3,
	IMG_PICKUP,
	IMG_EXIT_OPEN,
	IMG_EXIT_CLOSE,
	IMG_ENEMY,
	IMG_PLAYER,
	IMG_GLOW_1,
	IMG_GLOW_2,
	IMG_GLOW_3,
	IMG_GLOW_4,
	IMG_GLOW_5,
	IMG_GLOW_6,
	IMG_GLOW_7,
	IMG_GLOW_8
}	t_image;

#endif
