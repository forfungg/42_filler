/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:25:47 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/03 17:20:58 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	skip_line(int fd)
{
	char *str;

	get_next_line(fd, &str);
	if (str)
		free(str);
}

void	anchor_token(t_token *token, int i)
{
	int		x;
	int		y;

	x = TX(i);
	y = TY(i);
	i = 0;
	while (i < token->cnt_tiles)
	{
		TX(i) -= x;
		TY(i) -= y;
		i++;
	}
}

void	reset_game(t_map *map, t_token *token)
{
	tokendel(token);
	mapdel(map);
	map->lines = 0;
	map->columns = 0;
}

void	mapcpy(t_map *map)
{
	int i;

	i = 0;
	map->move = (char **)malloc(sizeof(char*) * map->lines);
	while (i < map->lines)
	{
		map->move[i] = ft_strdup(map->map[i]);
		i++;
	}
}

void	mapdel(t_map *map)
{
	int i;

	i = 0;
	while (i < map->lines)
	{
		if (map->map[i])
			ft_strdel(&(map->map[i]));
		i++;
	}
	map->map = NULL;
}

void	movedel(t_map *map)
{
	int i;

	i = 0;
	while (i < map->lines)
	{
		if (map->move[i])
			ft_strdel(&(map->move[i]));
		i++;
	}
	map->move = NULL;
}

void	tokendel(t_token *token)
{
	int i;

	i = 0;
	while (i < token->lines)
	{
		if (token->map[i])
			ft_strdel(&(token->map[i]));
		i++;
	}
	token->map = NULL;
	token->lines = 0;
	token->columns = 0;
	token->columns = 0;
	if	(token->tiles)
		free(token->tiles);
	token->tiles = NULL;
}
