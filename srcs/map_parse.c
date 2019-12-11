/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:18:31 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 18:27:19 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_coords	left_top(t_map *map, t_token *token, char side)
{
	t_coords	lt;

	if (side == 'r')
	{
		lt.x = map->right.edge.x - token->columns;
		lt.y = map->right.edge.y - token->lines;
	}
	else if (side == 'l')
	{
		lt.x = map->left.edge.x - token->columns;
		lt.y = map->left.edge.y - token->lines;
	}
	else
	{
		lt.x = map->edge.edge.x - token->columns;
		lt.y = map->edge.edge.y - token->lines;
	}
	lt.x < 0 ? lt.x = 0 : 0;
	lt.y < 0 ? lt.y = 0 : 0;
	return (lt);
}

t_coords	right_bottom(t_map *map, t_token *token, char side)
{
	t_coords	rb;

	if (side == 'r')
	{
		rb.x = map->right.edge.x + token->columns;
		rb.y = map->right.edge.y + token->lines;
	}
	else if (side == 'l')
	{
		rb.x = map->left.edge.x + token->columns;
		rb.y = map->left.edge.y + token->lines;
	}
	else
	{
		rb.x = map->edge.edge.x + token->columns;
		rb.y = map->edge.edge.y + token->lines;
	}
	rb.x >= map->columns ? rb.x = map->columns - 1 : 0;
	rb.y >= map->lines ? rb.y = map->lines - 1 : 0;
	return (rb);
}

void		resize_square(t_game *game, t_coords *l_top, t_coords *r_bot)
{
	if (l_top->x == 0 && l_top->y == 0 && r_bot->x == game->map.columns - 1\
		&& r_bot->y == game->map.lines - 1)
		filler_over(game);
	l_top->x = l_top->x > 0 ? l_top->x - 1 : 0;
	l_top->y = l_top->y > 0 ? l_top->y - 1 : 0;
	r_bot->x = r_bot->x < game->map.columns - 1 ? r_bot->x + 1 :\
		game->map.columns - 1;
	r_bot->y = r_bot->y < game->map.lines - 1 ? r_bot->y + 1 :\
		game->map.lines - 1;
}
