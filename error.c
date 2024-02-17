/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:33:33 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/11 16:21:50 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_error(char *msg1, char *msg2, char *msg3, t_solong *game)
{
	ft_putstr_fd(BOLD_RED, STDERR_FILENO);
	if (!game || !game->map->errstat)
		ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(msg1, STDERR_FILENO);
	ft_putstr_fd(msg2, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	ft_putstr_fd(YELLOW, STDERR_FILENO);
	ft_putendl_fd(msg3, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

void	error_logger(char *errmsg, t_solong *game)
{
	print_error(game->map->file, ": ", errmsg, game);
	game->map->errstat = true;
}

void	error_occured(int errcode, char *errmsg, t_solong *game)
{
	if (errmsg != NULL)
	{
		if (errcode == ERR_ARGC)
			print_error("Bad arguments", ": ", errmsg, NULL);
		else if (errcode == ERR_MLX)
			print_error (errmsg, ": ", (char *)mlx_strerror(mlx_errno), game);
		else if (errcode == ERR_MAP)
			print_error(game->map->file, ": ", errmsg, game);
		else
			print_error(errmsg, ": ", strerror(errno), game);
	}
	self_destruct(game);
	if (errcode == ERR_MLX)
		exit(mlx_errno);
	exit(errcode);
}
