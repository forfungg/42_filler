/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_prec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:32:47 by jnovotny          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:01 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

long double	ft_sqrt_prec(long double nb, int prec)
{
	int			i;
	long double	p;
	long double	res;
	long double	l;
	long double	r;

	res = 0;
	if (nb <= 0)
		return (0);
	if (prec < 3)
		prec = 3;
	else if (prec > 20)
		prec = 20;
	p = 5;
	i = 0;
	while (i++ <= prec)
		p = p / 10;
	l = 0;
	r = nb;
	while (!(((res + p) * (res + p) > nb && res * res < nb) || \
		((res - p) * (res - p) < nb && res * res > nb) || res * res == nb))
	{
		res = l + (r - l) / 2;
		res * res > nb ? r = res : 0;
		res * res < nb ? l = res : 0;
	}
	return (res);
}
