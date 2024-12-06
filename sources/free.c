/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:32:49 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/11 11:48:53 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

static void	destruct_map(t_mapinfo *map)
{
	ft_free_double((void ***)&map->matrix);
	ft_free_double((void ***)&map->duplex);
	ft_free_single((void **)&map->buff);
	ft_free_single((void **)&map->read);
	if (map->fd != -1)
		close(map->fd);
	free(map);
}

static void	clean_assets(t_solong *game)
{
	int	i;

	i = 0;
	while (i < GAME_ASSETS)
	{
		if (game->asset[i] != NULL)
			mlx_delete_image(game->mlx, game->asset[i]);
		i++;
	}
}

void	self_destruct(t_solong *game)
{
	if (!game)
		return ;
	if (game->mlx != NULL)
	{
		clean_assets(game);
		mlx_terminate(game->mlx);
	}
	if (game->map != NULL)
		destruct_map(game->map);
}
