/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:37:02 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/26 17:40:08 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define IS_DIGIT(x) (x >= '0' && x <= '9')
# define IS_MINE(x) (x == map->player || x == map->player + 32)
# define IS_ANCHOR(i) (token->tiles[i].x == 0 && token->tiles[i].y == 0)
# define IS_FREE(x,y) (map->map[y][x] == '.')
# define IS_STAR(x,y) (token->map[y][x] == '*')
# define TX(i) (token->tiles[i].x)
# define TY(i) (token->tiles[i].y)

typedef struct	s_coords
{
	int	x;
	int	y;
}				t_coords;


typedef struct	s_token
{
	int lines;
	int columns;
	char **map;
	int	cnt_tiles;
	t_coords *tiles;
	
}				t_token;

typedef struct	s_map
{
	int		lines;
	int		columns;
	char	**map;
	int		my_area;
	int		enemy_area;
	char	player;
}				t_map;


/*
** Fetch Information Functions
*/

void			fetch_player(t_map *map);
void			feed_data(t_map *map, t_token *token);
void			fetch_mapsize(t_map *map, char *str);
void			fetch_map(t_map *map);
void			fetch_tokensize(t_token *token, char *str);
void			fetch_token(t_token *token);
void			transcribe_token(t_token *token);
void			init_tiles(t_token *token);

/*
** Logic Functions
*/

void			place_token(t_map *map, t_token *token);
void			find_place(t_map *map, t_token *token, t_coords *i);
int				check_place(t_map *map, t_token *token, int y, int x);
int				is_fit(t_map *map, t_token *token, int y, int x);

/*
**	Print Functions
*/

void			print_map(t_map *map);
void			place_token(t_map *map, t_token *token);
void			filler_error(char *str);

/*
** Supportive tools
*/

void			skip_line();
void			anchor_token(t_token *token, int i);
void			adjust_out(t_token *token, t_coords *place);
void			ft_log(char *msg, ...);

#endif
