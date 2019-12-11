/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:36:03 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 18:27:07 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	ft_bzero(game, sizeof(t_game));
	game->board.mlx_p = mlx_init();
	game->board.win = mlx_new_window(game->board.mlx_p, 1200, 1000,\
		"Filler Match - Drawn by jnovotny");
	fetch_player(&(game->map));
	mlx_hook(game->board.win, 2, 0, key_press, game);
	mlx_loop_hook(game->board.mlx_p, feed_data, game);
	mlx_loop(game->board.mlx_p);
	return (0);
}
