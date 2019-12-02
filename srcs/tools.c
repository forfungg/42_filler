/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:25:47 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/02 11:39:44 by jnovotny         ###   ########.fr       */
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

void	ft_log(char *msg, ...)
{
	va_list	args;
	FILE	*log_file;
	
	log_file = fopen("jn_log.txt", "a+");
	va_start(args, msg);
	vfprintf(log_file, msg, args);
	fflush(log_file);
	va_end(args);
	fclose(log_file);
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

void	ft_log_status(t_map *map, t_token *token)
{
	ft_log("Pre-Placement Status\n");
	ft_log(">>main_v [%d; %d]->[%d; %d]\n", map->main_v.start.y, map->main_v.start.x, map->main_v.direction.y, map->main_v.direction.x);
	ft_log(">>left branch:\tedge[%d, %d]\n\t\t\t\tcrit_max[%d, %d]\n\t\t\t\tcrit_min[%d, %d]\n", map->left.edge.y, map->left.edge.x, map->left.crit_max.y, map->left.crit_max.x, map->left.crit_min.y, map->left.crit_min.x);
	ft_log(">>right branch:\tedge[%d, %d]\n\t\t\t\tcrit_max[%d, %d]\n\t\t\t\tcrit_min[%d, %d]\n", map->right.edge.y, map->right.edge.x, map->right.crit_max.y, map->right.crit_max.x, map->right.crit_min.y, map->right.crit_min.x);
	ft_log(">>Token h_delta = %d | v_delta = %d\n", token->h_delta, token->v_delta);
}