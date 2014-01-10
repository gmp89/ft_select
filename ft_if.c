/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 16:43:40 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/10 18:09:22 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


t_list	*ft_if_1(t_list *tmp, t_data *d)
{
	if (tmp->is_selected == YES)
	{
		tmp->is_selected = NO;
		tputs(tgetstr("me", NULL), 1, tputs_putchar);
	}
	else if (tmp->is_selected == NO)
	{
		tmp->is_selected = YES;
		tputs(tgetstr("mr", NULL), 1, tputs_putchar);
	}
	if ((d->arg_printed + 10) == d->li)
	{
		d->printed_col++;
		d->arg_printed = 0;
	}
	put_tab(tmp->length, d);
	tputs(tgoto(tgetstr("cm", NULL), d->pos_t, PU);
	tputs(tgetstr("us", NULL), 1, tputs_putchar);
	ft_putstr(tmp->str);
	d->arg_printed++;
	ft_putchar('\n');
	tputs(tgetstr("ue", NULL), 1, tputs_putchar);
	tputs(tgetstr("me", NULL), 1, tputs_putchar);
	tmp = tmp->next;
	return (tmp);
}

t_list	*ft_if_2(t_list *tmp, t_data *d)
{
	if (tmp->next != NULL)
	{
		if ((d->arg_printed + 10) == d->li)
		{
			d->printed_col++;
			d->arg_printed = 0;
		}
		put_tab(tmp->length, d);
		tputs(tgoto(tgetstr("cm", NULL), d->pos_t, PU);
		if (tmp->is_selected == YES)
			tputs(tgetstr("mr", NULL), 1, tputs_putchar);
		ft_putstr(tmp->str);
		tputs(tgetstr("me", NULL), 1, tputs_putchar);
		d->arg_printed++;
		ft_putchar('\n');
		tmp = tmp->next;
	}
	return (tmp);

}

t_list	*ft_if_3(t_list *tmp, t_data *d)
{
	if ((d->arg_printed + 10) == d->li)
	{
		d->printed_col++;
		d->arg_printed = 0;
	}
	put_tab(tmp->length, d);
	tputs(tgoto(tgetstr("cm", NULL), d->pos_t, PU);
	if (tmp->is_selected == YES)
		tputs(tgetstr("mr", NULL), 1, tputs_putchar);
	tputs(tgetstr("us", NULL), 1, tputs_putchar);
	ft_putstr(tmp->str);
	d->arg_printed++;
	ft_putchar('\n');
	tputs(tgetstr("ue", NULL), 1, tputs_putchar);
	tputs(tgetstr("me", NULL), 1, tputs_putchar);
	tmp = tmp->next;
	return (tmp);
}

t_list	*ft_if_4(t_list *tmp, t_data *d)
{
	if ((d->arg_printed + 10) == d->li)
	{
		d->printed_col++;
		d->arg_printed = 0;
	}
	put_tab(tmp->length, d);
	tputs(tgoto(tgetstr("cm", NULL), d->pos_t, PU);
	ft_putstr(tmp->str);
	d->arg_printed++;
	ft_putchar('\n');
	return (tmp);
}

void	print_list_if(t_list *list, t_data *d)
{
	t_list	*tmp;

	tmp = list;
	d->arg_printed = 0;
	d->col_tmp = d->col / d->needed;
	d->first = YES;
	d->printed_col = 0;
	while (tmp->next != NULL)
	{
		if ((tmp->index + 1) == d->pos)
			tmp = ft_if_1(tmp, d);
		tmp = ft_if_2(tmp, d);
	}
	if ((tmp->index + 1) == d->pos && d->is == 1)
		tmp = ft_if_3(tmp, d);
	else
		tmp = ft_if_4(tmp , d);
	d->is = 1;
	d->selected = 1;
}
