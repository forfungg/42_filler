/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:22:41 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 17:57:12 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	place_token(t_game *game)
{
	t_coords here;

	if (IS_ZERO_V(game->map.main_v))
		main_vector(&(game->map));
	ft_log_status(&(game->map), &(game->token));
	find_place(game, &here);
	here = game->token.best;
	adjust_edge(&(game->map), &(game->token), &here);
	ft_log("Pre-adjust coords: %dx%d\n", game->token.best.y,\
		game->token.best.x);
	adjust_out(&(game->token));
	ft_log("Placement @ %dx%d\n", game->token.best.y, game->token.best.x);
	token_to_map(&(game->map), &(game->token));
	game->map.my_score++;
	map_to_visual(&(game->map), &(game->board));
	show_score(game);
	ft_printf("%d %d\n", game->token.best.y, game->token.best.x);
	reset_game(&(game->map), &(game->token));
	game->token.map = NULL;
	ft_log("--------NEXT ROUND----------\n");
}

void	find_place(t_game *game, t_coords *i)
{
	t_coords l_top;
	t_coords r_bot;

	l_top = left_top(&(game->map), &(game->token));
	r_bot = right_bottom(&(game->map), &(game->token));
	while (1)
	{
		i->y = l_top.y;
		while (i->y < r_bot.y)
		{
			i->x = l_top.x;
			while (i->x < r_bot.x)
			{
				if (IS_MINEG(game->map.map[i->y][i->x]))
					check_place(&(game->map), &(game->token), i);
				i->x++;
			}
			i->y++;
		}
		if (game->token.best.x < 0 || game->token.best.y < 0)
			resize_square(game, &l_top, &r_bot);
		else
			return ;
	}
}

int		check_place(t_map *map, t_token *token, t_coords *here)
{
	int		i;

	i = 0;
	while (i < token->cnt_tiles)
	{
		anchor_token(token, i);
		if (is_fit(map, token, here))
		{
			ft_log("Tile[%d][%d] @t%.2d: ", here->y, here->x, i);
			asses_position(map, token, here);
		}
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

void	asses_position(t_map *map, t_token *token, t_coords *here)
{
	int	dist;

	dist = 1;
	dist *= move_score(map, token, here);
	ft_log("%d\n", dist);
	if (dist > token->best_dist)
	{
		token->best_dist = dist;
		token->best.x = here->x + token->tiles[0].x;
		token->best.y = here->y + token->tiles[0].y;
	}
}
