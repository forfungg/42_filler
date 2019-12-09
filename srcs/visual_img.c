/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 15:15:14 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 18:47:55 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	init_players(t_brd *board)
{
	int	w;
	int h;

	w = (board->bg.width - 22) / board->columns - 1;
	h = (board->bg.height - 22) / board->lines - 1;
	if (w < h)
		p_tile_size(board, w);
	else
		p_tile_size(board, h);
}

void	p_tile_size(t_brd *board, int size)
{
	board->empty.width = size;
	board->empty.height = size;
	board->empty.color = MLX_WHITE;
	square_img(MLX_P, &(board->empty));
	board->p1_old.width = size;
	board->p1_old.height = size;
	board->p1_old.color = MLX_RED;
	square_img(MLX_P, &(board->p1_old));
	board->p1_new.width = size;
	board->p1_new.height = size;
	board->p1_new.color = MLX_PINK;
	square_img(MLX_P, &(board->p1_new));
	board->p2_old.width = size;
	board->p2_old.height = size;
	board->p2_old.color = MLX_GREEN;
	square_img(MLX_P, &(board->p2_old));
	board->p2_new.width = size;
	board->p2_new.height = size;
	board->p2_new.color = MLX_YELLOW;
	square_img(MLX_P, &(board->p2_new));
}

void	init_gameover(t_brd *board)
{
	board->game_over.width = 20;
	board->game_over.height = 20;
	board->game_over.color = MLX_BLUE;
	square_img(MLX_P, &(board->game_over));
}

void	init_coverscore(t_brd *board)
{
	board->cover_score.width = 100;
	board->cover_score.height = 30;
	board->cover_score.color = MLX_BLUE;
	square_img(MLX_P, &(board->cover_score));
}
