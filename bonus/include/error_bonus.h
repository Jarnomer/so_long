/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:35:35 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/15 19:44:16 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_BONUS_H
# define ERROR_BONUS_H

# define MSG_ARGC		"./so_long maps/<filename>.ber"
# define MSG_EXTN		"Incorrect file extension <ber>"
# define MSG_FLDR		"Is a directory"
# define MSG_EMPTY		"Map is empty"
# define MSG_LINE		"Map has empty line(s)"
# define MSG_RECT		"Map is not rectangular"
# define MSG_PLAYER		"Map has no or more than one player(s)"
# define MSG_EXIT		"Map has no or more than one exit(s)"
# define MSG_PICKUP		"Map has no pickup(s)"
# define MSG_ELEM		"Map has invalid character(s)"
# define MSG_WALL		"Map has no properly closed walls"
# define MSG_PATH		"Map has no valid path to exit"
# define MSG_PICK		"Map has no valid path to pickup(s)"
# define MSG_MEM		"Could not allocate memory"
# define MSG_MLX		"MLX42 error"

enum e_errcodes
{
	NOERROR,
	ERR_ARGC,
	ERR_MAP,
	ERR_TEX,
	ERR_MEM,
	ERR_MLX
};

#endif
