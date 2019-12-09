/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:10:46 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 11:45:24 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	token_to_map(t_map *map, t_token *token)
{
	int		i;
	int		j;

	i = 0;
	while (i < token->lines)
	{
		j = 0;
		while (j < token->columns)
		{
			if (token->map[i][j] == '*')
				map->map[token->best.y + i][token->best.x + j] = map->player + 32;
			j++;
		}
		i++;
	}
}

void	print_map(t_map *map)
{
	int i;
	char *str = "01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
	FILE *map_file;

	i = 0;
	map_file = fopen("my_map", "w");
	fprintf(map_file, "Plateau %d %d:\n", map->lines, map->columns);
	ft_log("Plateau %d %d:\n", map->lines, map->columns);
	fprintf(map_file, "%*.*s\n", map->columns + 4, map->columns, str);
	ft_log("%*.*s\n", map->columns + 4, map->columns, str);
	while (i < map->lines)
	{
		fprintf(map_file, "%.3d %s\n", i, map->map[i]);
		ft_log("%.3d %s\n", i, map->map[i]);
		i++;
	}
	fclose(map_file);
}

void	adjust_out(t_token *token)
{
	t_coords anchor;

	anchor.y = 0;
	anchor_token(token, 0);
	while (anchor.y < token->lines)
	{
		anchor.x = 0;
		while (anchor.x < token->columns)
		{
			if (IS_STAR(anchor.x, anchor.y))
			{
				token->best.x -= anchor.x;
				token->best.y -= anchor.y;
				return ;
			}
			anchor.x++;
		}
		anchor.y++;
	}

}