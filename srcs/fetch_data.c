/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:45:30 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/09 18:53:45 by jnovotny         ###   ########.fr       */
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

	skip_line(0);
	i = 0;
	if (!(map->map = (char **)malloc(sizeof(char *) * (map->lines + 1))))
		filler_error("malloc @fetch_map");
	map->map[map->lines] = NULL;
	while (i < map->lines)
	{
		get_next_line(0, &str);
		map->map[i] = ft_strdup(&str[4]);
		if ((int)ft_strlen(map->map[i]) != map->columns)
			filler_error("Map line lenght error");
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
	if (!(token->map = (char **)malloc(sizeof(char *) * (token->lines + 1))))
		filler_error("malloc @fetch_token");
	token->map[token->lines] = NULL;
	while (i < token->lines)
	{
		get_next_line(0, &str);
		token->map[i] = ft_strdup(str);
		ft_log("%s\n", str);
		if ((int)ft_strlen(token->map[i]) != token->columns)
			filler_error("Token line lenght error");
		i++;
	}
	ft_log("\n");
	transcribe_token(token);
}
