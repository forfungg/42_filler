/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datafeed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:45:30 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/07 19:21:18 by jnovotny         ###   ########.fr       */
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
		{
			map->player = 'O';
			map->enemy = 'X';
		}
		else if (ft_strstr(str, "p2"))
		{
			map->player = 'X';
			map->enemy = 'O';
		}
		else
			filler_error("Player order not found!");
	}
	if(str)
		free(str);
}

void	feed_data(t_map *map, t_token *token, t_brd *board)
{
	char *str;

	if (map->fd > 0 && map->map == NULL)
		grabmap_file(map);
	if (get_next_line(0, &str) < 0)
		filler_error("Read error!");
	if (ft_strnequ(str, "Plateau", 7))
	{	
		fetch_mapsize(map, str);
		ft_log("Map dimensions: %d %d\n", map->lines, map->columns);
		if (board->lines != map->lines || board->columns != map->columns)
			init_board(map, board);
		fetch_map(map);
		// map_to_visual(map, board);
	}
	else if (ft_strnequ(str, "Piece", 5))
	{
		fetch_tokensize(token, str);
		ft_log("Token dimensions: %d %d\n", token->lines, token->columns);
		fetch_token(token);
		place_token(map, token);
		// while(1){}
	}
	if(str)
		free(str);
}

void	fetch_mapsize(t_map *map, char *str)
{
	int	i;

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
	int		i;

	skip_line(map->fd);
	i = 0;
	map->map = (char **)malloc(sizeof(char *) * (map->lines + 1)); /*protect*/
	map->map[map->lines] = NULL;
	while (i < map->lines)
	{
		get_next_line(map->fd, &str);
		map->map[i] = ft_strdup(&str[4]);
		if ((int)ft_strlen(map->map[i]) != map->columns)
			filler_error("Map line lenght error");
		// ft_log("Free @fetch_map\n");
		if(str)
			free(str);
		i++;
	}
}

void	fetch_tokensize(t_token *token, char *str)
{
	int	i;

	i = 0;
	while (!IS_DIGIT(str[i]))
		i++;
	token->lines = ft_atoi(&str[i]);
	while (IS_DIGIT(str[i]))
		i++;
	token->columns = ft_atoi(&str[i]);
}

void	fetch_token(t_token *token)
{
	int		i;
	char	*str;

	i = 0;
	token->map = (char **)malloc(sizeof(char *) * (token->lines + 1)); /*protect*/
	token->map[token->lines] = NULL;
	while (i < token->lines)
	{
		get_next_line(0, &str);
		// if (str == NULL || str[0] == '\0')
		// 	continue;
		token->map[i] = ft_strdup(str);
		ft_log("%s\n", str);
		//free(str);
		// ft_log("-> DONE\n");
		if ((int)ft_strlen(token->map[i]) != token->columns)
			filler_error("Token line lenght error");
		i++;
	}
	ft_log("\n");
	transcribe_token(token);
}

void	transcribe_token(t_token *token)
{
	int i;
	int j;
	int	t;
	
	init_tiles(token);
	i = 0;
	t = 0;
	while (i < token->lines)
	{
		j = 0;
		while (j < token->columns)
		{
			if (token->map[i][j] == '*')
			{
				token->tiles[t].x = j;
				token->tiles[t].y = i;
				t++;
			}
			j++;
		}
		i++;
	}
	anchor_token(token, 0);
	get_deltas(token);
	token->best.x = -1;
	token->best.y = -1;
	token->best_dist = -1;
}

void	init_tiles(t_token *token)
{
	int i;
	int j;
	
	token->cnt_tiles = 0;
	i = 0;
	while (i < token->lines)
	{
		j = 0;
		while (j < token->columns)
		{
			token->map[i][j] == '*' ? token->cnt_tiles++ : 0;
			j++;
		}
		i++;
	}
	token->tiles = (t_coords *)malloc(sizeof(t_coords) * token->cnt_tiles);
}

void	grabmap_file(t_map *map)
{
	char	*str;

	ft_log("Fetching the map from a file\n");
	map->fd = open("my_map", O_RDONLY);
	if (map->fd == -1)
		filler_error("Unable to open my_map");
	get_next_line(map->fd, &str);
	fetch_mapsize(map, str);
	ft_log("Map dimensions: %d %d\n", map->lines, map->columns);
	fetch_map(map);
	ft_log("Free @grabmap_file\n");
	if(str)
		free(str);
	close(map->fd);
}