/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:25:47 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/26 18:06:38 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	skip_line()
{
	char *str;

	get_next_line(0, &str);
	ft_log("in>>%s\n", str);
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
	
	log_file = fopen("logs.txt", "a+");
	va_start(args, msg);
	vfprintf(log_file, msg, args);
	va_end(args);
	fclose(log_file);
}