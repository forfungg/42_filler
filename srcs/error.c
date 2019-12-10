/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:58:40 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/10 17:03:18 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	filler_error(char *str)
{
	ft_printf("{RED}%s{EOC}\n", str);
	ft_log("Exit: %s\n", str);
	exit(-1);
}

void	filler_over(t_game *game)
{
	game_over_show(&(game->board));
	mlx_hook(game->board.win, 2, 0, key_press, game);
	mlx_loop(game->board.mlx_p);
	exit(0);
}
