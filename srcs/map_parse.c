/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:18:31 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/28 18:36:53 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

void	chop_frame(t_map *map)
{
	t_coords min;
	t_coords max;
	int i;
	int j;

	min.x = map->columns;
	min.y = map->lines;
	ft_bzero(&max, sizeof(t_coords));
	i = 0;
	while (i < map->lines)
	{
		j = 0;
		while (j < map->columns)
		{
			if(map->map[i][j] != '.')
			{
				i < min.y ? min.y = i : 0;
				i > max.y ? max.y = i : 0;
				j < min.x ? min.x = j : 0;
				j > max.x ? max.x = j : 0;
			}
			j++;
		}
		i++;
	}
}

/*
** Needs to include min & max points
*/

void	extract_sub(char **src, char **dst, t_coords min, t_coords max)
{

}