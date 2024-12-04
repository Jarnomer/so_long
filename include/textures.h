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

# define GAME_ASSETS	16
# define CELL_SIZE		126

# define TEX_CORNER_UL		"../textures/mandatory/corner_up_left.png"
# define TEX_CORNER_UR		"../textures/mandatory/corner_up_right.png"
# define TEX_CORNER_DL		"../textures/mandatory/corner_down_left.png"
# define TEX_CORNER_DR		"../textures/mandatory/corner_down_right.png"
# define TEX_EDGE_UP		"../textures/mandatory/edge_up.png"
# define TEX_EDGE_DOWN		"../textures/mandatory/edge_down.png"
# define TEX_EDGE_LEFT		"../textures/mandatory/edge_left.png"
# define TEX_EDGE_RIGHT		"../textures/mandatory/edge_right.png"
# define TEX_FLOOR			"../textures/mandatory/floor.png"
# define TEX_WALL_1			"../textures/mandatory/wall1.png"
# define TEX_WALL_2			"../textures/mandatory/wall2.png"
# define TEX_WALL_3			"../textures/mandatory/wall3.png"
# define TEX_PICKUP			"../textures/mandatory/pickup.png"
# define TEX_EXIT_OPEN		"../textures/mandatory/exit_open.png"
# define TEX_EXIT_CLOSE		"../textures/mandatory/exit_closed.png"
# define TEX_PLAYER			"../textures/mandatory/player.png"

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
	IMG_PLAYER
}	t_image;

#endif
