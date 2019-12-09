/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gg_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 15:55:06 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 16:26:54 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	game_over_show(t_brd *board)
{
	t_coords	start;

	start.x = board->bg.width / 2 - 420;
	start.y = board->bg.height / 2 + board->header.height - 40;
	place_g(board, &start);
	start.x += 100;
	place_a(board, &start);
	start.x += 100;
	place_m(board, &start);
	start.x += 120;
	place_e(board, &start);
	start.x += 160;
	place_o(board, &start);
	start.x += 100;
	place_v(board, &start);
	start.x += 120;
	place_e(board, &start);
	start.x += 100;
	place_r(board, &start);
	start.x += 100;
	place_excl(board, &start);
}

void	place_g(t_brd *board, t_coords *start)
{
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y + 80);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y + 80);
}

void	place_a(t_brd *board, t_coords *start)
{
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 80);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 80);
}

void	place_m(t_brd *board, t_coords *start)
{
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 80, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 80, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 80, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 80, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 80);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 80, start->y + 80);
}

void	place_e(t_brd *board, t_coords *start)
{
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 80);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y + 80);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y + 80);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 80);
}
