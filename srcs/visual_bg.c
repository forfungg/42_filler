/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_bg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 15:15:14 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 18:48:55 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	init_header(t_brd *board)
{
	char *str;

	board->header.width = 1200;
	board->header.height = 80;
	board->header.color = MLX_BLUE;
	square_img(MLX_P, &(board->header));
	mlx_put_image_to_window(MLX_P, MLX_W, board->header.img, 0, 0);
	mlx_string_put(MLX_P, MLX_W, 535, 10, MLX_WHITE, "FILLER MATCH");
	str = brd_s_str(board->columns, board->lines);
	mlx_string_put(MLX_P, MLX_W, 565, 40, MLX_WHITE, str);
	mlx_string_put(MLX_P, MLX_W, 225, 10, MLX_RED, "PLAYER 1");
	mlx_string_put(MLX_P, MLX_W, 925, 10, MLX_GREEN, "PLAYER 2");
}

void	init_bg(t_brd *board)
{
	board->bg.width = 1200;
	board->bg.height = 920;
	board->bg.color = MLX_WHITE;
	square_img(MLX_P, &(board->bg));
	mlx_put_image_to_window(MLX_P, MLX_W, board->bg.img, 0, 80);
	mlx_string_put(MLX_P, MLX_W, 10, 980, 0, "(ESC) Exit");
}

void	init_game_board(t_brd *board)
{
	board->game_board.width = (board->empty.width + 1) * board->columns + 2;
	board->game_board.height = (board->empty.height + 1) * board->lines + 2;
	board->brdoff_l = (board->bg.width - board->game_board.width) / 2;
	board->brdoff_t = (board->bg.height - board->game_board.height) / 2\
		+ board->header.height;
	square_img(MLX_P, &(board->game_board));
	mlx_put_image_to_window(MLX_P, MLX_W, board->game_board.img,\
		board->brdoff_l, board->brdoff_t);
}

char	*brd_s_str(int width, int height)
{
	char *res;
	char *str_w;
	char *str_h;
	char *tmp;

	str_w = ft_itoa(width);
	str_h = ft_itoa(height);
	tmp = ft_strjoin(str_w, " x ");
	res = ft_strjoin(tmp, str_h);
	free(str_w);
	free(str_h);
	free(tmp);
	return (res);
}

void	show_score(t_game *game)
{
	char *mine;
	char *enemy;

	mine = ft_itoa(game->map.my_score);
	enemy = ft_itoa(game->map.en_score);
	mlx_put_image_to_window(game->board.mlx_p, game->board.win,\
		game->board.cover_score.img, 235, 30);
	mlx_put_image_to_window(game->board.mlx_p, game->board.win,\
		game->board.cover_score.img, 935, 30);
	mlx_string_put(game->board.mlx_p, game->board.win, 245, 40,\
		MLX_WHITE, game->map.player == 'O' ? mine : enemy);
	mlx_string_put(game->board.mlx_p, game->board.win, 945, 40,\
		MLX_WHITE, game->map.player == 'X' ? mine : enemy);
	free(mine);
	free(enemy);
}
