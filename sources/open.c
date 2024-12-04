/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:47:45 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/14 21:39:47 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	read_file(t_mapinfo *map, t_solong *game)
{
	while (true)
	{
		map->buff = get_next_line(map->fd);
		if (!map->buff)
			break ;
		if (*map->buff == '\n')
			error_occured(ERR_MAP, MSG_LINE, game);
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
		error_occured(ERR_MAP, MSG_LINE, game);
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
	if (!map->temp || ft_strcmp(map->temp, ".ber"))
		error_occured(ERR_MAP, MSG_EXTN, game);
	else if (!ft_strcmp(map->temp, ".ber"))
		error_occured(ERR_MAP, MSG_NAME, game);
	read_file(map, game);
	map->matrix = ft_split(map->read, '\n');
	map->duplex = ft_split(map->read, '\n');
	if (!map->matrix || !map->duplex)
		error_occured(ERR_MEM, MSG_MEM, game);
}
