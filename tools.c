/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 14:11:35 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/08 15:55:00 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_print_tab(char **tabs)
{
	int		i;

	i = 0;
	while (tabs[i] != 0)
	{
		ft_putstr(tabs[i]);
		ft_putchar('\n');
		i++;
	}
}

int		ft_store(t_data *d, char **av, int ac)
{
	d->i = 1;
	d->j = 0;
	d->arg = (char **)malloc(sizeof(char *) * ac);
	while (av[d->i] != 0)
	{
		d->arg[d->j] = av[d->i];
		d->i++;
		d->j++;
	}
	d->arg[d->j] = 0;
	return (0);
}

int		ft_get_size(t_data *d)
{
	if((d->col = tgetnum("co")) < 1)
		return (-1);
	if((d->li = tgetnum("li")) < 1)
		return (-1);
	return (1);
}

int tputs_putchar(int c)
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

int		ft_calc_center(t_data *d)
{
	int		a;
	int		b;
	int		c;
	int		z;

	a = d->col / 4;
	b = a / 2;
	c = b / 2;
	z = a + (b / 2) - c;
	return (a);
}

void	ft_put_center(t_data *d)
{
	int		i;
	int		center;

	i = 0;
	center = ft_calc_center(d);
	while (i <= center)
	{
		ft_putchar(' ');
		i++;
	}
}
