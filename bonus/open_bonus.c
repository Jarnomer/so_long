/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:47:45 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/14 21:40:58 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	read_file(t_mapinfo *map, t_solong *game)
{
	while (true)
	{
		map->buff = get_next_line(map->fd);
		if (!map->buff)
			break ;
		if (*map->buff == '\n')
			error_logger(MSG_LINE, game);
		map->temp = ft_strjoin(map->read, map->buff);
		if (!map->temp)
			error_occured(ERR_MEM, MSG_MEM, game);
		free(map->read);
		map->read = map->temp;
		free(map->buff);
	}
	if (!*map->read)
		error_occured(ERR_MAP, MSG_EMPTY, game);
	else if (map->read[ft_strlen(map->read) - 1] == '\n')
		error_logger(MSG_LINE, game);
}

void	open_map(t_mapinfo *map, t_solong *game)
{
	map->fd = open(map->file, O_DIRECTORY);
	if (map->fd != -1)
		error_occured(ERR_MAP, MSG_FLDR, game);
	map->fd = open(map->file, O_RDONLY);
	if (map->fd == -1)
		error_occured(ERR_MAP, strerror(errno), game);
	map->temp = ft_strrchr(map->file, '.');
	if (!map->temp || ft_strncmp(map->temp, ".ber", 5))
		error_occured(ERR_MAP, MSG_EXTN, game);
	read_file(map, game);
	map->matrix = ft_split(map->read, '\n');
	if (!map->matrix)
		error_occured(ERR_MEM, MSG_MEM, game);
}
