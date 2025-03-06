/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:32:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/17 18:42:08 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static int	init_mapinfo(t_mapinfo *map, char *file)
{
	map->fd = -1;
	map->file = file;
	map->read = ft_strdup("");
	if (!map->read)
		return (-1);
	return (0);
}

void	init_game(t_solong *game, char *file)
{
	ft_bzero(game, sizeof(*game));
	game->map = ft_calloc(1, sizeof(t_mapinfo));
	if (!game->map || init_mapinfo(game->map, file) == -1)
		error_exit(ERR_MEM, MSG_MEM, game);
	game->cellsize = CELL_SIZE;
	ft_bzero(&game->anim, sizeof(t_animation));
	game->anim.direction = 1;
}
