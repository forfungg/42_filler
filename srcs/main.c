/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:36:03 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/07 19:33:23 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(int ac, char **av)
{
	t_token	token;
	t_map	map;
	t_brd	*board;
	char	*str;

	board = (t_brd *)malloc(sizeof(t_brd));
	ft_log("\n************START***********\n");
	ft_bzero((void*)&token, sizeof(t_token));
	ft_bzero((void*)&map, sizeof(t_map));
	ft_bzero(board, sizeof(t_brd));
	board->mlx_p = mlx_init();
	board->win = mlx_new_window(board->mlx_p, 1200, 1000, "Filler Match - Drawn by jnovotny");
	fetch_player(&map);
	ft_log("Player symbol: %c\n", map.player);
	ft_log("-------------------------------\n");
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
	mlx_loop_hook()
	feed_data(&map, &token, board);
	mlx_loop(board->mlx_p);
	return(0);
}