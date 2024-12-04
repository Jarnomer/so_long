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

#include <so_long.h>

static void	log_error(char *msg1, char *msg2, char *msg3)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(msg1, STDERR_FILENO);
	ft_putstr_fd(msg2, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	ft_putstr_fd(YELLOW, STDERR_FILENO);
	ft_putendl_fd(msg3, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

void	error_occured(int errcode, char *errmsg, t_solong *game)
{
	if (errmsg != NULL)
	{
		if (errcode == ERR_ARGC)
			log_error("Bad arguments", ": ", errmsg);
		else if (errcode == ERR_MLX)
			log_error(errmsg, ": ", (char *)mlx_strerror(mlx_errno));
		else if (errcode == ERR_MAP)
			log_error(game->map->file, ": ", errmsg);
		else
			log_error(errmsg, ": ", strerror(errno));
	}
	self_destruct(game);
	if (errcode == ERR_MLX)
		exit(mlx_errno);
	exit(errcode);
}
