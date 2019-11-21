/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datafeed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:45:30 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/21 18:27:33 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	fetch_player(t_map *map)
{
	char *str;

	get_next_line(0, &str);
	if (ft_strnequ(str, "$$$ exec", 8) && map->player == 0)
	{
		if (ft_strstr(str, "p1"))
			map->player = 1;
		else if (ft_strstr(str, "p2"))
			map->player = 2;
		else
			filler_error("Player order not found!");
	}
	free(str);
}

void	feed_data(t_map *map, t_token *token)
{
	char *str;

	get_next_line(0, &str);
	if (ft_strnequ(str, "Plateau", 7))
	{	
		fetch_mapsize(map, str);
		fetch_map(map);
	}
	else if (ft_strnequ(str, "Piece", 5))
	{
		fetch_tokensize(token);
		fetch_token(token);
	}
	else
		feed_data(map, token);
	free(str);
}

void	fetch_mapsize(t_map *map, char *str)
{
	size_t	i;

	i = 0;
	while (!IS_DIGIT(str[i]))
		i++;
	map->lines = ft_atoi(&str[i]);
	while (IS_DIGIT(str[i]))
		i++;
	map->columns = ft_atoi(&str[i]);
}

void	fetch_map(t_map *map)
{
	char	*str;


}