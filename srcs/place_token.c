/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:22:41 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/02 17:35:58 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	place_token(t_map *map, t_token *token)
{
	t_coords here;

	if (IS_ZERO_V(map->main_v))
		main_vector(map);
	ft_log_status(map, token);
	find_place(map, token, &here);
	// update my strat values;
	here = token->best;
	adjust_edge(map, token, &here);
	ft_log("Pre-adjust coords: %dx%d\n", token->best.y, token->best.x);
	adjust_out(token);
	ft_log("Placement @ %dx%d\n", token->best.y, token->best.x);
	ft_log("--------NEXT ROUND----------\n");
	token_to_map(map, token);
	if (MAP_LOG)
		print_map(map);
	ft_printf("%d %d\n", token->best.y, token->best.x);
	reset_game(map, token);
	token->map = NULL;
}

void	find_place(t_map *map, t_token *token, t_coords *i)
{
	t_coords l_top;
	t_coords r_bot;

	l_top = left_top(map, token);
	r_bot = right_bottom(map, token);
	while (!(l_top.x == 0 && l_top.y == 0 && r_bot.y == map->lines && r_bot.x == map->columns))
	{
		ft_log("Searching in area %dx%d from [%d, %d]\n", r_bot.y - l_top.y, r_bot.x - l_top.x, l_top.y, l_top.x);
		i->y = l_top.y;
		while (i->y < r_bot.y)
		{
			i->x = l_top.x;
			while (i->x < r_bot.x)
			{
				if (IS_MINE(map->map[i->y][i->x]))
					check_place(map, token, i);
				i->x++;
			}
			i->y++;
		}
		if (token->best.x < 0 || token->best.y < 0)
			resize_square(map, &l_top, &r_bot);
		else
			return ;
	}
	filler_error("GAME OVER!");
}

int		check_place(t_map *map, t_token *token, t_coords *here)
{
	int		i;
	
	i = 0;
	while (i < token->cnt_tiles)
	{
		anchor_token(token, i);
		if (is_fit(map, token, here))
			asses_position(map, token, here);
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
		if (TX(i) + here->x >= map->columns || TY(i) + here->y >= map->lines)
			return (0);
		if (!IS_ANCHOR(i) && !IS_FREE(TX(i) + here->x, TY(i) + here->y))
			return (0);
		i ++;
	}
	return (1);
}

void	asses_position(t_map *map, t_token *token, t_coords *here)
{
	// int i, a, b;
	int	dist;

	// ft_log("Assess @%dx%d\n", here->y, here->x);
	// mapcpy(map);
	// i = 0;
	// while(i < token->cnt_tiles)
	// {
	// 	a = token->tiles[i].y + here->y;
	// 	b = token->tiles[i].x + here->x;
	// 	map->move[a][b] = map->player;
	// 	i++;
	// }
	dist = 1; //player_distance(map);
	// ft_log("dist = %d |", dist);
	dist *= move_score(map, token, here);
	ft_log("total = %d \n", dist);
	//if (token->best_dist == -1 || (token->best_dist > dist && here->y >= map->lines / 2) || (token->best_dist >= dist && here->y < map->lines / 2))
	if (dist > token->best_dist)
	{
		token->best_dist = dist;
		token->best.x = here->x + token->tiles[0].x;
		token->best.y = here->y + token->tiles[0].y;
	}
	// movedel(map);
}
// Future "breaking the big map into smaller sections of interest"
// void	battlefiled(t_map *map, t_coords *start, t_coords *end)
// {
// 	int		i;
// 	int		j;
// 	int		tmp_s;
// 	int		tmp_e;

// 	ft_bzero(start, sizeof(t_coords));
// 	end->x = map->columns - 1;
// 	end->y = map->lines - 1;
// 	i = 0;
// 	tmp_s = 0;
// 	tmp_e = map->lines + map->columns;
// 	while (i < map->lines)
// 	{
// 		j = 0;
// 		while (j < map->columns)
// 		{
// 			if (IS_ENEMY(map->map[i][j]))
// 				if (i + j >= tmp_s && i >= start->y)
// 				{
// 					tmp_s = i + j;
// 					start->x = j;
// 					start->y = i;
// 				}
// 			if (IS_MINE(map->map[i][j]))
// 				if (i + j <= tmp_e && i <= end->y)
// 				{
// 					tmp_e = i + j;
// 					end->x = j;
// 					end->y = i;
// 				}
// 			j++;
// 		}
// 		i++;
// 	}

// }
int		player_distance(t_map *map)
{
	t_coords mine;
	t_coords enemy;

	find_enemy(map, &enemy);
	find_mine(map, &mine);
	return (ft_m_dist(&enemy, &mine));
}

void	find_enemy(t_map *map, t_coords *enemy)
{
	t_coords current;
	t_coords center;

	ft_bzero(enemy, sizeof(t_coords));
	ft_middle(map, &center);
	current.y = 0;
	while (current.y < map->lines)
	{
		current.x = 0;
		while (current.x < map->columns)
		{
			if (IS_ENEMY(map->map[current.y][current.x]) && ft_m_dist(&current, &center) < ft_m_dist(enemy, &center))
			{
				enemy->x = current.x;
				enemy->y = current.y;
			}
			current.x++;
		}
		current.y++;
	}
}

void	find_mine(t_map *map, t_coords *mine)
{
	t_coords current;
	t_coords center;

	ft_bzero(mine, sizeof(t_coords));
	ft_middle(map, &center);
	current.y = 0;
	while (current.y < map->lines)
	{
		current.x = 0;
		while (current.x < map->columns)
		{
			if (IS_MINE(map->map[current.y][current.x]) && ft_m_dist(&current, &center) < ft_m_dist(mine, &center))
			{
				mine->x = current.x;
				mine->y = current.y;
			}
			current.x++;
		}
		current.y++;
	}
}

