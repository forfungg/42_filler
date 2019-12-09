/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gg_img2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 15:55:06 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 16:26:39 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	place_o(t_brd *board, t_coords *start)
{
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y + 80);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y + 80);
}

void	place_v(t_brd *board, t_coords *start)
{
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 80, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 80, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y + 80);
}

void	place_r(t_brd *board, t_coords *start)
{
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 20, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 40, start->y + 60);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 80);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x + 60, start->y + 80);
}

void	place_excl(t_brd *board, t_coords *start)
{
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 20);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 40);
	mlx_put_image_to_window(MLX_P, MLX_W, GG_IMG, start->x, start->y + 80);
}
