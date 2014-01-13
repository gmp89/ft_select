/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 14:09:42 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 23:08:04 by gpetrov          ###   ########.fr       */
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

