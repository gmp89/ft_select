/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 17:13:16 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 20:04:17 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_us(t_list *list, t_data *d)
{
	list->co = 1;
	if (d->us == 1)
		return (1);
	return (0);
}

int		is_select(t_list *list, t_data *d)
{
	list->co = 1;
	if (d->selected == 1)
		return (1);
	return (0);
}

void	is_spc_1(t_list *list, t_data *d)
{
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, tputs_putchar);
	d->pos = (d->pos + 1) - d->pos_init;
	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	make_header(d);
	print_multi_tab(list, d);
}

void	is_spc_2(t_list *list, t_data *d)
{
	tputs(tgetstr("do", NULL), 1, tputs_putchar);
	d->pos += 1;
	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	make_header(d);
	print_multi_tab(list, d);
}

int		is_spc(char *buf, t_list *list, t_data *d)
{
	int		i;

	i = d->pos_init;
	if (buf[0] == 32 && buf[1] == 0 && buf[2] == 0)
	{
		ft_putnbr(d->pos_init);
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header(d);
		print_list_if(list, d);
		if (d->pos == d->pos_init)
			is_spc_1(list, d);
		else
			is_spc_2(list, d);
		while (i-- >= d->pos)
			tputs(tgetstr("up", NULL), 1, tputs_putchar);
		return (0);
	}
	else
		return (-1);
}
