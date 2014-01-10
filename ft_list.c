/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 14:09:42 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/10 16:52:43 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_new_element(t_list **list, t_list *new)
{
	t_list	*tmp;

	tmp = *list;
	new->next = *list;
	tmp->prev = new;
	*list = new;
}

void	add_element_end(t_list **list, t_list *new)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	put_tab(int length, t_data *d)
{
	int		i;
	int		j;

	i = 0;
	j = d->printed_col;
	d->pos_t = (d->col_tmp / 2) - (length / 2);
	if (d->printed_col > 0)
	{
		while (j != 0)
		{
			d->pos_t = d->pos_t + d->col_tmp;
			j--;
		}
	}
	while (i < d->pos_t)
		i++;
}

void	get_col_nb(t_data *d)
{
	int		k;

	d->needed = 1;
	k = d->nb_col;
	while (k >= d->li)
	{
		k = k / 2;
		d->needed++;
	}
}

void	put_arg_center(int len, t_data *d)
{
	int		pos;
	int		i;

	i = 0;
	pos = (d->col / 2) - (len / 2);
	while (i < pos)
	{
		ft_putchar(' ');
		i++;
	}
}

/* void	print_list(t_list *list, t_data *d) */
/* { */
/* 	t_list	*tmp; */

/* 	tmp = list; */
/* 	d->arg_printed = 0; */
/* 	d->col_tmp = d->col / d->needed; */
/* 	d->first = YES; */
/* 	d->printed_col = 0; */
/* 	while (tmp->next != NULL) */
/* 	{ */
/* 		if ((d->arg_printed + 10) == d->li) */
/* 		{ */
/* 			d->printed_col++; */
/* 			d->arg_printed = 0; */
/* 		} */
/* 		put_tab(tmp->length, d); */
/* 		tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar); */
/* 		ft_putstr(tmp->str); */
/* 		d->arg_printed++; */
/* 		/\* ft_putnbr(tmp->index); *\/ */
/* 		ft_putchar('\n'); */
/* 		tmp = tmp->next; */
/* 	} */
/* 	if ((d->arg_printed + 10) == d->li) */
/* 	{ */
/* 		d->printed_col++; */
/* 		d->arg_printed = 0; */
/* 	} */
/* 	put_tab(tmp->length, d); */
/* 	tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar); */
/* 	ft_putstr(tmp->str); */
/* 	d->arg_printed++; */
/* 	/\* ft_putnbr(tmp->index); *\/ */
/* 	ft_putchar('\n'); */
/* 	d->selected = 0; */
/* } */

/* void	print_list_us(t_list *list, t_data *d) */
/* { */
/* 	t_list	*tmp; */

/* 	tmp = list; */
/* 	while (tmp->next != NULL) */
/* 	{ */
/* 		if ((tmp->index + 1) == d->pos) */
/* 		{ */
/* 			put_arg_center(tmp->length, d); */
/* 			tputs(tgetstr("us", NULL), 1, tputs_putchar); */
/* 			ft_putstr(tmp->str); */
/* 			ft_putchar('\n'); */
/* 			tputs(tgetstr("ue", NULL), 1, tputs_putchar); */
/* 			tmp = tmp->next; */
/* 		} */
/* 		if (tmp->next != NULL) */
/* 		{ */
/* 			put_arg_center(tmp->length, d); */
/* 			ft_putstr(tmp->str); */
/* 			ft_putchar('\n'); */
/* 			tmp = tmp->next; */
/* 		} */
/* 	} */
/* 	if ((tmp->index + 1) == d->pos && d->us == 1) */
/* 	{ */
/* 		put_arg_center(tmp->length, d); */
/* 		tputs(tgetstr("us", NULL), 1, tputs_putchar); */
/* 		ft_putstr(tmp->str); */
/* 		ft_putchar('\n'); */
/* 		tputs(tgetstr("ue", NULL), 1, tputs_putchar); */
/* 		tmp = tmp->next; */
/* 	} */
/* 	else */
/* 	{ */
/* 		put_arg_center(tmp->length, d); */
/* 		ft_putstr(tmp->str); */
/* 		ft_putchar('\n'); */
/* 	} */
/* } */

