/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:13:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/11 15:52:13 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	main(int argc, char **argv)
{
	t_solong	game;

	if (argc != 2)
		error_occured(ERR_ARGC, MSG_ARGC, NULL);
	init_game(&game, argv[1]);
	open_map(game.map, &game);
	read_map(game.map, &game);
	test_map(game.map, &game);
	load_assets(&game);
	draw_assets(&game);
	play_game(&game);
	self_destruct(&game);
	return (NOERROR);
}
