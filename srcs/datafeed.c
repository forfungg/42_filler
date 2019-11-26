/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datafeed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:45:30 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/26 18:47:30 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	fetch_player(t_map *map)
{
	char *str;

	get_next_line(0, &str);
	ft_log("in>>%s\n", str);
	if (ft_strnequ(str, "$$$ exec", 8) && map->player == 0)
	{
		if (ft_strstr(str, "p1"))
			map->player = 'O';
		else if (ft_strstr(str, "p2"))
			map->player = 'X';
		else
			filler_error("Player order not found!");
	}
	free(str);
}

void	feed_data(t_map *map, t_token *token)
{
	char *str;

	if (get_next_line(0, &str) < 0)
		filler_error("Read error!");
	ft_log("in>>%s\n", str);
	if (ft_strnequ(str, "Plateau", 7))
	{	
		fetch_mapsize(map, str);
		ft_log("Map dimensions: %d %d\n", map->lines, map->columns);
		fetch_map(map);
	}
	else if (ft_strnequ(str, "Piece", 5))
	{
		fetch_tokensize(token, str);
		ft_log("Token dimensions: %d %d\n", token->lines, token->columns);
		fetch_token(token);
		print_map(map);
		place_token(map, token);
	}
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

	skip_line();
	i = 0;
	map->map = (char **)malloc(sizeof(char *) * (map->lines + 1)); /*protect*/
	map->map[map->lines] = NULL;
	while (i < map->lines)
	{
		get_next_line(0, &str);
		ft_log("in>>%s\n", str);
		map->map[i] = ft_strdup(&str[4]);
		if ((int)ft_strlen(map->map[i]) != map->columns)
			filler_error("Map line lenght error");
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
	int		i, ret, j, size;
	char	*buf;
	char	*res;
	char	*tmp;

	i = 0;
	token->map = (char **)malloc(sizeof(char *) * (token->lines + 1)); /*protect*/
	token->map[token->lines] = NULL;
	res = ft_strnew(1);
	ret = 0;
	// while (i < token->lines)
	// {
	// 	if (0 > get_next_line(0, &token->map[i]))
	// 		return;
	// 	ft_log("in>>%s\n", token->map[i]);
	// 	if ((int)ft_strlen(token->map[i]) != token->columns)
	// 		filler_error("Token line lenght error");
	// 	i++;
	// }
	size = token->lines * (token->columns + 1);
	buf = (char *)malloc(size);
	while ((ret = read(0, buf, size)) > 0)
	{
		buf[ret] = '\0';
		tmp = ft_strjoin(res, buf);
		free(res);
		res = ft_strdup(tmp);
		free(tmp);
		if ((int)ft_strlen(res) >= size - 1)
			break;
	}
	ft_log("res: %s\n", res);
	j = 0;
	while (i < token->lines)
	{
		token->map[i] = ft_strsub(res, j, token->columns);
		ft_log("in>>%s\n", token->map[i]);
		j += token->columns + 1;
		i++;
	}
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
				TX(i) = j;
				TY(i) = i;
			}
			j++;
		}
		i++;
	}
	anchor_token(token, 0);
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
