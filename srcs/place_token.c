/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:22:41 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/11 11:27:06 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	place_token(t_game *game)
{
	t_coords here;
	int best;

	if (is_zero_v(&(game->map.main_v)))
		main_vector(&(game->map));
	adjust_left_crit(&(game->map));
	adjust_right_crit(&(game->map));
	ft_log_status(&(game->map), &(game->token));
	find_place(game, &here, 'r');
	find_place(game, &here, 'l');
	find_place_edge(game, &here);
	if (game->token.best_left_dist > game->token.best_right_dist)
		best = game->token.best_left_dist;
	else
		best = game->token.best_right_dist;
	if (game->token.best_edge_dist > best)
		best = game->token.best_edge_dist;
	if (best == game->token.best_left_dist)
		game->token.best = game->token.best_left;
	else if (best == game->token.best_right_dist)
		game->token.best = game->token.best_right;
	else
	 	game->token.best = game->token.best_edge;
	// game->token.best = game->token.best_left_dist > game->token.best_right_dist ? game->token.best_left : game->token.best_right;
	ft_log("left %d @[%d, %d] | right %d @[%d, %d] | edge %d @[%d, %d] | res[%d, %d]\n", game->token.best_left_dist, game->token.best_left.y, game->token.best_left.x, game->token.best_right_dist, game->token.best_right.y, game->token.best_right.x,game->token.best_edge_dist, game->token.best_edge.y, game->token.best_edge.x, game->token.best.y, game->token.best.x);
	here = game->token.best;
	adjust_edge(&(game->map), &(game->token), &here);
	ft_log("Pre-adjust coords: %dx%d\n", here.y, here.x);
	adjust_out(&(game->token));
	ft_log("Placement @ %dx%d\n", game->token.best.y, game->token.best.x);
	token_to_map(&(game->map), &(game->token));
	game->map.my_score++;
	map_to_visual(&(game->map), &(game->board));
	show_score(game);
	if (MAP_LOG)
		print_map(&(game->map));
	ft_printf("%d %d\n", game->token.best.y, game->token.best.x);
	reset_game(&(game->map), &(game->token));
	game->token.map = NULL;
	ft_log("--------NEXT ROUND----------\n");
}

void	find_place(t_game *game, t_coords *i, char side)
{
	t_coords l_top;
	t_coords r_bot;

	l_top = left_top(&(game->map), &(game->token), side);
	r_bot = right_bottom(&(game->map), &(game->token), side);
	while (1)
	{
		i->y = l_top.y;
		while (i->y < r_bot.y)
		{
			i->x = l_top.x;
			while (i->x < r_bot.x)
			{
				if (IS_MINEG(game->map.map[i->y][i->x]))
					check_place(&(game->map), &(game->token), i, side);
				i->x++;
			}
			i->y++;
		}
		if (side == 'r' && (game->token.best_right.x < 0 || game->token.best_right.y < 0))
			resize_square(game, &l_top, &r_bot);
		else if (side == 'l' && (game->token.best_left.x < 0 || game->token.best_left.y < 0))
			resize_square(game, &l_top, &r_bot);
		else
			return ;
	}
}

int		check_place(t_map *map, t_token *token, t_coords *here, char side)
{
	int		i;

	i = 0;
	while (i < token->cnt_tiles)
	{
		anchor_token(token, i);
		if (is_fit(map, token, here))
			asses_position(map, token, here, side);
		i++;
	}
	return (1);
}

int		is_fit(t_map *map, t_token *token, t_coords *here)
{
	int		i;

	i = 0;
	while (i < token->cnt_tiles)
	{
		if (TX(i) + here->x >= map->columns || TY(i) + here->y >= map->lines\
			|| TX(i) + here->x < 0 || TY(i) + here->y < 0)
			return (0);
		if (!IS_ANCHOR(i) && !IS_FREE(TX(i) + here->x, TY(i) + here->y))
			return (0);
		i++;
	}
	return (1);
}

void	asses_position(t_map *map, t_token *token, t_coords *here, char side)
{
	int	dist;

	dist = 1;
	dist *= move_score(map, token, here, side);
	if (side == 'r' && dist > token->best_right_dist)
	{
		token->best_right_dist = dist;
		token->best_right.x = here->x + token->tiles[0].x;
		token->best_right.y = here->y + token->tiles[0].y;
	}
	else if (side == 'l' && dist > token->best_left_dist)
	{
		token->best_left_dist = dist;
		token->best_left.x = here->x + token->tiles[0].x;
		token->best_left.y = here->y + token->tiles[0].y;
	}
	else if (side == 'e' && dist > token->best_edge_dist)
	{
		token->best_edge_dist = dist;
		token->best_edge.x = here->x + token->tiles[0].x;
		token->best_edge.y = here->y + token->tiles[0].y;
	}
	
}
