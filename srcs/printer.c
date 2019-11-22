/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:10:46 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/22 10:00:48 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	print_map(t_map *map)
{
	int i;

	i = 0;
	ft_printf("\n{GREEN}{U}P%d Current board{EOC}\n", map->player);
	ft_printf("Lines: %d | Columns: %d\n", map->lines, map->columns);
	while (i < map->lines)
	{
		ft_printf("%.3d %s\n", i, map->map[i]);
		i++;
	}
}