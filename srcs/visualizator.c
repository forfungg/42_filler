/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 15:15:14 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/07 20:00:20 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	map_to_visual(t_map *map,t_brd *board)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->lines)
	{
		j = 0;
		while (j < map->columns)
		{
			if (map->map[i][j] == '.')
				mlx_put_image_to_window(board->mlx_p, board->win, board->empty.img, board->brdoff_l + 1 + j * (board->empty.width + 1), board->brdoff_t + 1 + i * (board->empty.height + 1));
			else if (map->map[i][j] == 'O')
				mlx_put_image_to_window(board->mlx_p, board->win, board->p1_old.img, board->brdoff_l + 1 + j * (board->empty.width + 1), board->brdoff_t + 1 + i * (board->empty.height + 1));
			else if (map->map[i][j] == 'o')
				mlx_put_image_to_window(board->mlx_p, board->win, board->p1_new.img, board->brdoff_l + 1 + j * (board->empty.width + 1), board->brdoff_t + 1 + i * (board->empty.height + 1));
			else if (map->map[i][j] == 'X')
				mlx_put_image_to_window(board->mlx_p, board->win, board->p2_old.img, board->brdoff_l + 1 + j * (board->empty.width + 1), board->brdoff_t + 1 + i * (board->empty.height + 1));
			else if (map->map[i][j] == 'x')
				mlx_put_image_to_window(board->mlx_p, board->win, board->p2_new.img, board->brdoff_l + 1 + j * (board->empty.width + 1), board->brdoff_t + 1 + i * (board->empty.height + 1));
			j++;
		}
		i++;
	}
}

void	square_img(void *mlx_ptr, t_bimg *elem)
{
	int		i;

	elem->img = mlx_new_image(mlx_ptr, elem->width,elem->height);
	elem->img_p = mlx_get_data_addr(elem->img, &(elem->bpp), &(elem->line_s), &(elem->endian));
	i = 0;
	while (i < elem->width * elem->height)
	{
		*(int *)(elem->img_p + (int)(i * (elem->bpp/8))) = elem->color;
		i++;
	}
}

void	init_board(t_map *map,t_brd *board)
{
	board->lines = map->lines;
	board->columns = map->columns;
	ft_log("** Visualiser Init\n");
	ft_log("** size: %d x %d\n", board->columns, board->lines);
	init_header(board);
	ft_log("** Header (%d x %d): color = %d\n", board->header.width, board->header.height, board->header.color);
	init_bg(board);
	ft_log("** Background (%d x %d): color = %d\n", board->bg.width, board->bg.height, board->bg.color);
	init_players(board);
	ft_log("** Empty (%d x %d): color = %d\n", board->empty.width, board->empty.height, board->empty.color);
	ft_log("** p1_old (%d x %d): color = %d\n", board->p1_old.width, board->p1_old.height, board->p1_old.color);
	ft_log("** p1_new (%d x %d): color = %d\n", board->p1_new.width, board->p1_new.height, board->p1_new.color);
	ft_log("** p2_old (%d x %d): color = %d\n", board->p2_old.width, board->p2_old.height, board->p2_old.color);
	ft_log("** p2_new (%d x %d): color = %d\n", board->p2_new.width, board->p2_new.height, board->p2_new.color);
	init_game_board(board);
	ft_log("** game_board (%d x %d): color = %d\n", board->game_board.width, board->game_board.height, board->game_board.color);
	ft_log("** brdoff_l = %d | brdoff_t = %d\n\n", board->brdoff_l, board->brdoff_t);
}

void	init_header(t_brd *board)
{
	char *str;
	
	board->header.width = 1200;
	board->header.height = 80;
	board->header.color = MLX_BLUE;
	square_img(board->mlx_p, &(board->header));
	ft_log("here\n");
	mlx_put_image_to_window(board->mlx_p, board->win, board->header.img, 0, 0);
	mlx_string_put(board->mlx_p, board->win, 535, 10, MLX_WHITE, "FILLER MATCH");
	str = brd_s_str(board->columns, board->lines);
	mlx_string_put(board->mlx_p, board->win, 565, 40, MLX_WHITE, str);
	mlx_string_put(board->mlx_p, board->win, 265, 40, MLX_RED, "PLAYER 1");
	mlx_string_put(board->mlx_p, board->win, 865, 40, MLX_GREEN, "PLAYER 2");
}

void	init_bg(t_brd *board)
{
	board->bg.width = 1200;
	board->bg.height = 920;
	board->bg.color = MLX_WHITE;
	square_img(board->mlx_p, &(board->bg));
	mlx_put_image_to_window(board->mlx_p, board->win, board->bg.img, 0, 80);
}

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

void	init_game_board(t_brd *board)
{
	board->game_board.width = (board->empty.width + 1) * board->columns + 2;
	board->game_board.height = (board->empty.height + 1) * board->lines + 2;
	board->brdoff_l = (board->bg.width - board->game_board.width) / 2;
	board->brdoff_t = (board->bg.height - board->game_board.height) / 2 + board->header.height;
	square_img(board->mlx_p, &(board->game_board));
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_board.img, board->brdoff_l, board->brdoff_t);
}

void	p_tile_size(t_brd *board, int size)
{
	board->empty.width = size;
	board->empty.height = size;
	board->empty.color = MLX_WHITE;
	square_img(board->mlx_p, &(board->empty));
	board->p1_old.width = size;
	board->p1_old.height = size;
	board->p1_old.color = MLX_RED;
	square_img(board->mlx_p, &(board->p1_old));
	board->p1_new.width = size;
	board->p1_new.height = size;
	board->p1_new.color = MLX_PINK;
	square_img(board->mlx_p, &(board->p1_new));
	board->p2_old.width = size;
	board->p2_old.height = size;
	board->p2_old.color = MLX_GREEN;
	square_img(board->mlx_p, &(board->p2_old));
	board->p2_new.width = size;
	board->p2_new.height = size;
	board->p2_new.color = MLX_YELLOW;
	square_img(board->mlx_p, &(board->p2_new));
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
