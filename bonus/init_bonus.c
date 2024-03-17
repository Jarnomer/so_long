/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:32:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/15 19:45:30 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	init_mapinfo(t_mapinfo *map, char *file)
{
	ft_bzero(map, sizeof(*map));
	map->fd = -1;
	map->file = file;
	map->read = ft_strdup("");
	if (!map->read)
		return (1);
	return (0);
}

void	init_game(t_solong *game, char *file)
{
	ft_bzero(game, sizeof(*game));
	game->map = malloc(sizeof(t_mapinfo));
	if (!game->map || init_mapinfo(game->map, file))
		error_occured(ERR_MEM, MSG_MEM, game);
	game->cellsize = CELL_SIZE;
	game->timer = ANIMATE_TIMER;
}
