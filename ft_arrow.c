/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 17:10:42 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/10 17:11:17 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_arrow_1(t_list *list, t_data *d)
{
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, tputs_putchar);
	d->pos = (d->pos + 1) - d->pos_init;
	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	make_header(d);
	print_multi_tab(list, d);
}

void	ft_arrow_2(t_list *list, t_data *d)
{
	tputs(tgetstr("do", NULL), 1, tputs_putchar);
	d->pos += 1;
	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	make_header(d);
	print_multi_tab(list, d);
}

void	ft_arrow_3(t_list *list, t_data *d)
{
	int		i;

	i = 1;
	while (++i <= d->pos_init)
		tputs(tgetstr("do", NULL), 1, tputs_putchar);
	d->pos = d->pos_init;
	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	make_header(d);
	print_multi_tab(list, d);
}

void	ft_arrow_4(t_list *list, t_data *d)
{
	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	tputs(tgetstr("up", NULL), 1, tputs_putchar);
	d->pos -= 1;
	make_header(d);
	print_multi_tab(list, d);
}

int		is_arrow(char *buf, t_data *d, t_list *list)
{
	if (buf[0] != 27 && buf[1] != 91)
		return (-1);
	if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 66) && d->pos == d->pos_init)
		ft_arrow_1(list, d);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		ft_arrow_2(list, d);
	else if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 65) && d->pos == 1)
		ft_arrow_3(list, d);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		ft_arrow_4(list, d);
	else
		return (-1);
	return (0);
}
