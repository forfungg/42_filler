/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 15:15:14 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 14:48:26 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	map_to_visual(t_map *map,t_brd *board)
{
	int	i;
	int	j;
	int e_turn;
	char *who;

	i = 0;
	e_turn = 0;
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
			{
				mlx_put_image_to_window(board->mlx_p, board->win, board->p1_new.img, board->brdoff_l + 1 + j * (board->empty.width + 1), board->brdoff_t + 1 + i * (board->empty.height + 1));
				map->enemy == 'O' ? e_turn = 1 : 0;
			}
			else if (map->map[i][j] == 'X')
				mlx_put_image_to_window(board->mlx_p, board->win, board->p2_old.img, board->brdoff_l + 1 + j * (board->empty.width + 1), board->brdoff_t + 1 + i * (board->empty.height + 1));
			else if (map->map[i][j] == 'x')
			{
				mlx_put_image_to_window(board->mlx_p, board->win, board->p2_new.img, board->brdoff_l + 1 + j * (board->empty.width + 1), board->brdoff_t + 1 + i * (board->empty.height + 1));
				map->enemy == 'X' ? e_turn = 1 : 0;
			}
			j++;
		}
		i++;
	}
	if (!e_turn)
	{
		game_over_show(board);
		if (map->my_score > map->en_score)
			who = "I WON";
		else if (map->my_score == map->en_score)
			who = "DRAW";
		else
			who = "ENEMY WON";
		mlx_string_put(board->mlx_p, board->win, 595, 650, MLX_BLUE, who);
	}
	else
		map->en_score++;
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
	init_gameover(board);
	init_coverscore(board);
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
	mlx_string_put(board->mlx_p, board->win, 225, 10, MLX_RED, "PLAYER 1");
	mlx_string_put(board->mlx_p, board->win, 925, 10, MLX_GREEN, "PLAYER 2");
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

void	init_gameover(t_brd *board)
{
	board->game_over.width = 20;
	board->game_over.height = 20;
	board->game_over.color = MLX_BLUE;
	square_img(board->mlx_p, &(board->game_over));
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

void	game_over_show(t_brd *board)
{
	t_coords	start;

	start.x = board->bg.width / 2 - 420;
	start.y = board->bg.height / 2 + board->header.height - 40;

	/* G */
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 20, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 40, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 40, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 60, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 60, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 20, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 40, start.y + 80);

	/* A */
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 120, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 140, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 100, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 160, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 100, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 120, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 140, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 160, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 100, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 160, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 100, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 160, start.y + 80);

	/* M */
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 200, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 280, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 200, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 220, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 260, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 280, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 200, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 240, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 280, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 200, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 280, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 200, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 280, start.y + 80);

	/* E */
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 320, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 340, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 360, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 380, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 320, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 320, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 340, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 360, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 320, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 320, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 340, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 360, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 380, start.y + 80);

	/* O */
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 480, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 500, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 460, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 520, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 460, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 520, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 460, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 520, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 480, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 500, start.y + 80);

	/* V */
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 560, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 640, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 560, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 640, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 580, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 620, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 580, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 620, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 600, start.y + 80);

	/* E */
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 680, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 700, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 720, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 740, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 680, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 680, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 700, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 720, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 680, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 680, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 700, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 720, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 740, start.y + 80);

	/* R */
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 780, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 800, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 820, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 780, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 840, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 780, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 800, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 820, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 780, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 820, start.y + 60);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 780, start.y + 80);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 840, start.y + 80);
	
	/* ! */
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 900, start.y);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 900, start.y + 20);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 900, start.y + 40);
	mlx_put_image_to_window(board->mlx_p, board->win, board->game_over.img, start.x + 900, start.y + 80);
}

void	init_coverscore(t_brd *board)
{
	board->cover_score.width = 100;
	board->cover_score.height = 30;
	board->cover_score.color = MLX_BLUE;
	square_img(board->mlx_p, &(board->cover_score));
}

void	show_score(t_game *game)
{
	char *mine;
	char *enemy;

	mine = ft_itoa(game->map.my_score);
	enemy = ft_itoa(game->map.en_score);
	mlx_put_image_to_window(game->board.mlx_p, game->board.win, game->board.cover_score.img, 235, 30);
	mlx_put_image_to_window(game->board.mlx_p, game->board.win, game->board.cover_score.img, 935, 30);
	mlx_string_put(game->board.mlx_p, game->board.win, 245, 40, MLX_WHITE, game->map.player == 'O' ? mine : enemy);
	mlx_string_put(game->board.mlx_p, game->board.win, 945, 40, MLX_WHITE, game->map.player == 'X' ? mine : enemy);
	ft_log("Score: me(%s) vs enemy(%s)\n", mine, enemy);
	free(mine);
	free(enemy);
}