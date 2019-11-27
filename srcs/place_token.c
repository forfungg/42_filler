/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:22:41 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/27 11:02:56 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	place_token(t_map *map, t_token *token)
{
	t_coords here;

	find_place(map, token, &here);
	ft_log("Pre-adjust coords: %dx%d\n", here.y, here.x);
	adjust_out(token, &here);
	ft_log("Placement @ %dx%d\n", here.y, here.x);
	token_to_map(map, token, &here);
	print_map(map);
	ft_printf("%d %d", here.y, here.x);
	reset_game(map, token);
	token->map = NULL;
}

void	find_place(t_map *map, t_token *token, t_coords *i)
{

	i->y = 0;
	while (i->y < map->lines)
	{
		i->x = 0;
		while (i->x < map->columns)
		{
			if (IS_MINE(map->map[i->y][i->x]))
				if(check_place(map, token, i->y, i->x))
					return ;
			i->x++;
		}
		i->y++;
	}
	filler_error("GAME OVER!");
}

int		check_place(t_map *map, t_token *token, int y, int x)
{
	int		i;
	
	i = 0;
	while (!is_fit(map, token, y, x))
	{
		i++;
		if (i == token->cnt_tiles)
			return (0);
		anchor_token(token, i);
	}
	return (1);
}

int		is_fit(t_map *map, t_token *token, int y, int x)
{
	int		i;

	i = 0;
	while (i < token->cnt_tiles)
	{
		if (TX(i) + x >= map->columns || TY(i) + y >= map->lines)
			return (0);
		if (!IS_ANCHOR(i) && !IS_FREE(TX(i) + x, TY(i) + y))
			return (0);
		i ++;
	}
	return (1);
}