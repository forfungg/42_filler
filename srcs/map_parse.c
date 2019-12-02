/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:18:31 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/02 10:06:16 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_coords	left_top(t_map *map, t_token *token)
{
	t_coords lt;
	int		qd;

	qd = (map->main_v.direction.x > 0 && map->main_v.direction.y > 0) || (map->main_v.direction.x < 0 && map->main_v.direction.y < 0) ? 1 : -1;
	if (token->h_delta > token->v_delta)
	{
		lt.x = qd == 1 ? map->left.edge.x - token->columns : map->right.edge.x - token->columns;
		lt.y = qd == 1 ? map->left.edge.y - token->lines : map->right.edge.y - token->lines;
	}
	else
	{
		lt.x = qd == -1 ? map->left.edge.x - token->columns : map->right.edge.x - token->columns;
		lt.y = qd == -1 ? map->left.edge.y - token->lines : map->right.edge.y - token->lines;
	}
	lt.x < 0 ? lt.x = 0 : 0;
	lt.y < 0 ? lt.y = 0 : 0;
	return (lt);
}

t_coords	right_bottom(t_map *map, t_token *token)
{
	t_coords rb;
	int		qd;

	qd = (map->main_v.direction.x > 0 && map->main_v.direction.y > 0) || (map->main_v.direction.x < 0 && map->main_v.direction.y < 0) ? 1 : -1;
	if (token->h_delta > token->v_delta)
	{
		rb.x = qd == 1 ? map->left.edge.x + token->columns : map->right.edge.x + token->columns;
		rb.y = qd == 1 ? map->left.edge.y + token->lines : map->right.edge.y + token->lines;
	}
	else
	{
		rb.x = qd == -1 ? map->left.edge.x + token->columns : map->right.edge.x + token->columns;
		rb.y = qd == -1 ? map->left.edge.y + token->lines : map->right.edge.y + token->lines;
	}
	rb.x >= map->columns ? rb.x = map->columns - 1 : 0;
	rb.y >= map->lines ? rb.y = map->lines - 1 : 0;
	return (rb);
}

void		resize_square(t_map *map, t_coords *l_top, t_coords *r_bot)
{
	l_top->x = l_top->x > 0 ? l_top->x - 1: 0;
	l_top->y = l_top->y > 0 ? l_top->y - 1: 0;
	r_bot->x = r_bot->x < map->columns - 1 ? r_bot->x + 1: map->columns - 1;
	r_bot->y = r_bot->y < map->lines - 1 ? r_bot->y + 1: map->lines - 1;
	ft_log("Map of interest resized (%d x %d)\n", r_bot->y - l_top->y, r_bot->x - l_top->x);
}

/*
** Chop Start -> find first players' tile and last players' tile chop the size to include those points
** e.g Map 4x4 > 3x3
	....
	.O..	=>		O..
	....	=>		...
	...X	=>		..X
** Chop Chop -> split map into 4 pieces (vertical middle and horizontal middle)
		-> check for both players presence
			-> if 0 then ignore if 4x0 then use the original (guaranteed for presence of both)
			-> if 1 then Chop Chop the map
			-> if 1xN && N > 1 then process all maps (maybe implment some choice logic) and compare their results

	e.g
	MAP 10x12
	OO..........
	.OOO.......X
	...OO....XXX
	....O.....X.
	...OO....XXX
	....OOO.XX..
	....O....XXX
	........XXXX
	......XXXX..
	.........XXX

		=>

	OO....|......
	.OOO..|.....X
	...OO.|...XXX
	....O.|....X.
	...OO.|...XXX
	------+------
	....OO|O.XX..
	....O.|...XXX
	......|..XXXX		<--- Map of interest, ignore rest
	......|XXXX..
	......|...XXX

		If map_size < token_size then 1 step back

	Map score multiplicator?
	fight in the middle < fight at borders
*/

// void	chop_frame(t_map *map)
// {
// 	t_coords min;
// 	t_coords max;
// 	int i;
// 	int j;

// 	min.x = map->columns;
// 	min.y = map->lines;
// 	ft_bzero(&max, sizeof(t_coords));
// 	i = 0;
// 	while (i < map->lines)
// 	{
// 		j = 0;
// 		while (j < map->columns)
// 		{
// 			if(map->map[i][j] != '.')
// 			{
// 				i < min.y ? min.y = i : 0;
// 				i > max.y ? max.y = i : 0;
// 				j < min.x ? min.x = j : 0;
// 				j > max.x ? max.x = j : 0;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// /*
// ** Needs to include min & max points
// */

// void	extract_sub(char **src, char **dst, t_coords min, t_coords max)
// {

// }