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

#include "so_long.h"

static void	clean_assets(t_asset **lst, t_solong *game)
{
	t_asset	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->fd != -1)
			close((*lst)->fd);
		if ((*lst)->img != NULL)
			mlx_delete_image(game->window, (*lst)->img);
		if ((*lst)->tex != NULL)
			mlx_delete_texture((*lst)->tex);
		free(*lst);
		*lst = tmp;
	}
	free(*lst);
	*lst = NULL;
}

static void	free_douple(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

static void	destruct_map(t_mapinfo *map)
{
	if (!map)
		return ;
	if (map->fd != -1)
		close(map->fd);
	if (map->matrix != NULL)
		free_douple(&map->matrix);
	if (map->duplex != NULL)
		free_douple(&map->duplex);
	free(map->buff);
	map->buff = NULL;
	free(map->read);
	map->read = NULL;
	free(map);
	map = NULL;
}

void	self_destruct(t_solong *game)
{
	if (!game)
		return ;
	if (game->images != NULL)
		free(game->images);
	if (game->assets != NULL)
		clean_assets(&game->assets, game);
	if (game->window != NULL)
		mlx_terminate(game->window);
	if (game->map != NULL)
		destruct_map(game->map);
}
