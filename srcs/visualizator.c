/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 15:15:14 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/10 20:05:58 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	map_to_visual(t_map *map, t_brd *board)
{
	t_coords	i;
	int			e_turn;

	i.y = 0;
	e_turn = 0;
	while (i.y < map->lines)
	{
		i.x = 0;
		while (i.x < map->columns)
		{
			put_tile(board, map->map[i.y][i.x], &i);
			if (map->map[i.y][i.x] == 'o')
				map->enemy == 'O' ? e_turn = 1 : 0;
			else if (map->map[i.y][i.x] == 'x')
				map->enemy == 'X' ? e_turn = 1 : 0;
			i.x++;
		}
		i.y++;
	}
	enemy_turn(map, board, e_turn);
}

void	put_tile(t_brd *board, char c, t_coords *place)
{
	t_coords adjusted;

	adjusted.x = board->brdoff_l + 1 + place->x * (board->empty.width + 1);
	adjusted.y = board->brdoff_t + 1 + place->y * (board->empty.height + 1);
	if (c == '.')
		mlx_put_image_to_window(MLX_P, MLX_W,\
			board->empty.img, adjusted.x, adjusted.y);
	else if (c == 'O')
		mlx_put_image_to_window(MLX_P, MLX_W,\
			board->p1_old.img, adjusted.x, adjusted.y);
	else if (c == 'o')
		mlx_put_image_to_window(MLX_P, MLX_W,\
			board->p1_new.img, adjusted.x, adjusted.y);
	else if (c == 'X')
		mlx_put_image_to_window(MLX_P, MLX_W,\
			board->p2_old.img, adjusted.x, adjusted.y);
	else if (c == 'x')
		mlx_put_image_to_window(MLX_P, MLX_W,\
			board->p2_new.img, adjusted.x, adjusted.y);
}

void	enemy_turn(t_map *map, t_brd *board, int t)
{
	char	*who;

	if (!t && map->en_score > 0)
	{
		game_over_show(board);
		if (map->my_score > map->en_score)
			who = "I WON";
		else if (map->my_score == map->en_score)
			who = "DRAW";
		else
			who = "ENEMY WON";
		mlx_string_put(MLX_P, MLX_W, 595, 650, MLX_BLUE, who);
	}
	else
		map->en_score++;
}

void	square_img(void *mlx_ptr, t_bimg *elem)
{
	int		i;

	elem->img = mlx_new_image(mlx_ptr, elem->width, elem->height);
	elem->img_p = mlx_get_data_addr(elem->img, &(elem->bpp),\
		&(elem->line_s), &(elem->endian));
	i = 0;
	while (i < elem->width * elem->height)
	{
		*(int *)(elem->img_p + (int)(i * (elem->bpp / 8))) = elem->color;
		i++;
	}
}

void	init_board(t_map *map, t_brd *board)
{
	board->lines = map->lines;
	board->columns = map->columns;
	init_header(board);
	init_bg(board);
	init_players(board);
	init_game_board(board);
	init_gameover(board);
	init_coverscore(board);
}
