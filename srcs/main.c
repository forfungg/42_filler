/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:36:03 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/27 10:30:27 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(int ac, char **av)
{
	t_token	token;
	t_map	map;
	char	*str;

	ft_log("\n\n********START*******\n");
	ft_bzero((void*)&token, sizeof(t_token));
	ft_bzero((void*)&map, sizeof(t_map));
	fetch_player(&map);
	ft_log("Player symbol: %c\n", map.player);
	if (ac == 2)
	{
		map.fd = open(av[1], O_RDONLY);
		if (map.fd == -1)
			filler_error("Failed to open the map file");
		get_next_line(map.fd, &str);
		fetch_mapsize(&map, str);
		ft_log("Map dimensions: %d %d\n", map.lines, map.columns);
		fetch_map(&map);
		free(str);
		close(map.fd);
	}
	while(1)
	{
		feed_data(&map, &token);
	}

/*
	To-Do (Wed 27/11)
	+ change placing algorithm (fucked up atm)
	+ create test environment, copy-pasta is shit

	- evaluate strategy
	- place token
	
	- perror and strerror usage?
	 */
	return(0);
}