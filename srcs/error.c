/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:58:40 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 15:24:35 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	filler_error(char *str)
{
	ft_printf("{RED}%s{EOC}\n", str);
	ft_log("Exit: %s\n", str);
	// while(1){}
	exit(-1);
}

void	filler_over(t_game *game)
{
	char *who;

	game_over_show(&(game->board));
	if (game->map.my_score > game->map.en_score)
		who = "I WON";
	else if (game->map.my_score == game->map.en_score)
		who = "DRAW";
	else
		who = "ENEMY WON";
	mlx_string_put(game->board.mlx_p, game->board.win, 595, 650, MLX_BLUE, who);
	mlx_hook(game->board.win, 2, 0, key_press, game);
	mlx_loop(game->board.mlx_p);
	exit (0);
}