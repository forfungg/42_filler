/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:10:46 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/26 17:56:17 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	print_map(t_map *map)
{
	int i;
	char *str = "01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";

	i = 0;
	ft_log("Plateau %d %d:\n", map->lines, map->columns);
	ft_log("%*.*s\n", map->columns + 4, map->columns, str);
	while (i < map->lines)
	{
		ft_log("%.3d %s\n", i, map->map[i]);
		i++;
	}
}

void	adjust_out(t_token *token, t_coords *place)
{
	t_coords anchor;

	anchor.y = 0;
	place->x -= token->tiles[0].x;
	place->y -= token->tiles[0].y;
	while (anchor.y < token->lines)
	{
		anchor.x = 0;
		while (anchor.x < token->columns)
		{
			if (IS_STAR(anchor.x, anchor.y))
			{
				place->x -= anchor.x;
				place->y -= anchor.y;
				return ;
			}
			anchor.x++;
		}
		anchor.y++;
	}

}