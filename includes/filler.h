/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:37:02 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/21 19:24:57 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define IS_DIGIT(x) (x >= 0 && x <= 9)

typedef struct	s_coords
{
	size_t	x;
	size_t	y;
}				t_coords;

typedef struct	s_token
{
	size_t lines;
	size_t columns;
	
}				t_token;

typedef struct	s_map
{
	int		lines;
	int		columns;
	char	**map;
	int		my_area;
	int		enemy_area;
	int		player;
}				t_map;


/*
** Fetch Information Functions
*/

void			fetch_player(t_map *map);
void			feed_data(t_map *map, t_token *token);
void			fetch_mapsize(t_map *map, char *str);
void			fetch_map(t_map *map);
void			fetch_tokensize(t_token *token, char *str);
void			fetch_token(t_token token);

/*
** Logic Functions
*/

/*
**	Print Functions
*/

void			print_map(t_map *map);
void			filler_error(char *str);

/*
** Supportive tools
*/

void			skip_line();

#endif
