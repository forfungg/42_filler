/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datafeed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:45:30 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 18:26:08 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		feed_data(t_game *game)
{
	char *str;

	if (get_next_line(0, &str) < 0)
		filler_error("Read error!");
	if (ft_strnequ(str, "Plateau", 7))
	{
		fetch_mapsize(&(game->map), str);
		if (G_B_LINES != G_M_LINES || G_B_COLUMNS != G_M_COLUMNS)
			init_board(&(game->map), &(game->board));
		fetch_map(&(game->map));
	}
	else if (ft_strnequ(str, "Piece", 5))
	{
		fetch_tokensize(&(game->token), str);
		fetch_token(&(game->token));
		place_token(game);
	}
	return (1);
}

void	transcribe_token(t_token *token)
{
	t_coords	i;
	int			t;

	init_tiles(token);
	i.y = 0;
	t = 0;
	while (i.y < token->lines)
	{
		i.x = 0;
		while (i.x < token->columns)
		{
			if (token->map[i.y][i.x] == '*')
			{
				token->tiles[t] = i;
				t++;
			}
			i.x++;
		}
		i.y++;
	}
	anchor_token(token, 0);
	token_best_reset(token);
}

void	token_best_reset(t_token *token)
{
	token->best.x = -1;
	token->best.y = -1;
	token->best_left.x = -1;
	token->best_left.y = -1;
	token->best_left_dist = -10000000;
	token->best_right.x = -1;
	token->best_right.y = -1;
	token->best_right_dist = -10000000;
	token->best_edge.x = -1;
	token->best_edge.y = -1;
	token->best_edge_dist = -10000000;
}

void	init_tiles(t_token *token)
{
	int i;
	int j;

	token->cnt_tiles = 0;
	i = 0;
	while (i < token->lines)
	{
		j = 0;
		while (j < token->columns)
		{
			token->map[i][j] == '*' ? token->cnt_tiles++ : 0;
			j++;
		}
		i++;
	}
	token->tiles = (t_coords *)malloc(sizeof(t_coords) * token->cnt_tiles);
}
