/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 16:40:01 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 23:21:04 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*ft_multi_1(t_list *tmp, t_data *d)
{
	if ((tmp->index + 1) == d->pos)
		{
			if ((d->arg_printed + 10) == d->li)
			{
				d->printed_col++;
				d->arg_printed = 0;
			}
			put_tab(tmp->length, d);
			tputs(tgoto(tgetstr("cm", NULL), d->pos_t, PU);
			tputs(tgetstr("us", NULL), 1, tputs_putchar);
			if (tmp->is_selected == YES)
				tputs(tgetstr("mr", NULL), 1, tputs_putchar);
			ft_putstr_fd(tmp->str, isatty(STDOUT_FILENO));
			tputs(tgetstr("me", NULL), 1, tputs_putchar);
			d->arg_printed++;
			ft_putchar_fd('\n', FDD);
			tputs(tgetstr("ue", NULL), 1, tputs_putchar);
			tmp = tmp->next;
		}
	return (tmp);
}

t_list	*ft_multi_2(t_list *tmp, t_data *d)
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
			ft_putstr_fd(tmp->str, isatty(STDOUT_FILENO));
			tputs(tgetstr("me", NULL), 1, tputs_putchar);
			d->arg_printed++;
			ft_putchar_fd('\n', FDD);
			tmp = tmp->next;
		}
	return (tmp);
}

t_list	*ft_multi_3(t_list *tmp, t_data *d)
{
	if ((d->arg_printed + 10) == d->li)
	{
		d->printed_col++;
		d->arg_printed = 0;
	}
	put_tab(tmp->length, d);
	tputs(tgoto(tgetstr("cm", NULL), d->pos_t, PU);
	tputs(tgetstr("us", NULL), 1, tputs_putchar);
	if (tmp->is_selected == YES)
		tputs(tgetstr("mr", NULL), 1, tputs_putchar);
	ft_putstr_fd(tmp->str, isatty(STDOUT_FILENO));
	tputs(tgetstr("me", NULL), 1, tputs_putchar);
	d->arg_printed++;
	ft_putchar('\n');
	tputs(tgetstr("ue", NULL), 1, tputs_putchar);
	return (tmp);
}

t_list	*ft_multi_4(t_list *tmp, t_data *d)
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
	ft_putstr_fd(tmp->str, isatty(STDOUT_FILENO));
	tputs(tgetstr("me", NULL), 1, tputs_putchar);
	d->arg_printed++;
	return (tmp);
}

void	print_multi_tab(t_list *list, t_data *d)
{
	t_list	*tmp;

	tmp = list;
	d->arg_printed = 0;
	d->col_tmp = d->col / d->needed;
	d->first = YES;
	d->printed_col = 0;
	while (tmp->next != NULL)
	{
		tmp = ft_multi_1(tmp, d);
		tmp = ft_multi_2(tmp, d);
	}
	if (d->pos == 1 && (tmp != NULL))
		tmp = ft_multi_3(tmp, d);
	else if (tmp != NULL)
		tmp = ft_multi_4(tmp, d);
	d->is = 1;
	d->selected = 1;
}
