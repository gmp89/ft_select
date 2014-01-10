/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 17:28:19 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/10 17:44:28 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_get_size(t_data *d)
{
	if((d->col = tgetnum("co")) < 1)
		return (-1);
	if((d->li = tgetnum("li")) < 1)
		return (-1);
	return (1);
}

int		tputs_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	make_header(t_data *d)
{
	ft_put_center(d);
	ft_putstr("              .__                 __   \n");
	ft_put_center(d);
	ft_putstr("  ______ ____ |  |   ____   _____/  |_ \n");
	ft_put_center(d);
	ft_putstr(" /  ___// __ \\|  | _/ __ \\_/ ___\\   __\\\n");
	ft_put_center(d);
	ft_putstr(" \\___ \\\\  ___/|  |_\\  ___/\\  \\___|  |  \n");
	ft_put_center(d);
	ft_putstr("/____  >\\___  >____/\\___  >\\___  >__|  \n");
	ft_put_center(d);
	ft_putstr("     \\/     \\/          \\/     \\/      \n");
	make_header_bot(d);
}

void	make_header_bot(t_data *d)
{
	int		i;

	i = 1;
	while (i <= d->col)
	{
		ft_putchar('=');
		i++;
	}
	ft_putchar('\n');
}

void	ft_print_pos(t_data *d)
{
	ft_putstr("col = ");
	ft_putnbr(d->col);
	ft_putchar('\n');
	ft_putstr("li = ");
	ft_putnbr(d->li);
	ft_putchar('\n');
}
