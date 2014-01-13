/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 16:50:02 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 23:32:15 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			max_lenght(t_list **list, int nb)
{
	int		*ta_b;
	int		i;
	t_list	*tmp;
	int		max;

	i = 0;
	ta_b = (int *)malloc(sizeof(int) * nb);
	tmp = *list;
	ta_b[i] = tmp->length;
	while (tmp->next != NULL)
	{
		i++;
		tmp = tmp->next;
		ta_b[i] = tmp->length;
	}
	i = 0;
	max = ta_b[0];
	while (i < nb)
	{
		i++;
		if (ta_b[i - 1] > ta_b[i])
			max = ta_b[i - 1];
	}
	return (max);
}

static int	ft_del_this_elem(t_list **list, t_list *elt, struct termios *term)
{
	if (*list == NULL)
	{
		ft_quit(term);
		exit(0);
	}
	if (elt->next == NULL)
	{
		if (*list == elt)
			*list = NULL;
		else
			(elt->prev)->next = NULL;
		free(elt);
		return (0);
	}
	else
	{
		if (*list == elt)
			*list = elt->next;
		if (elt->prev != NULL)
			elt->prev->next = elt->next;
		elt->next->prev = elt->prev;
		free(elt);
		return (1);
	}
}

t_list		*ft_del_elem(t_list *list, t_data *d, struct termios *term)
{
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->is_selected == YES)
		{
			if (tmp->index != 1)
				tputs(tgetstr("up", NULL), 1, tputs_putchar);
			ft_del_this_elem(&list, tmp, term);
			d->pos = d->pos % (d->tot + 1);
			if (d->pos >= d->pos_init || d->pos < 1)
				d->pos = d->pos_init - 1;
			d->pos_init--;
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
	if (list == NULL)
		return (0);
	index_list(&list, d);
	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	make_header(d);
	print_multi_tab(list, d);
	return (list);
}

void		index_list(t_list **list, t_data *d)
{
	t_list	*tmp;
	int		i;

	i = 1;
	tmp = *list;
	tmp->length = (int)ft_strlen(tmp->str);
	tmp->pos = (d->col / 2) - (tmp->length / 2);
	while (tmp->next != NULL)
	{
		tmp->length = (int)ft_strlen(tmp->str);
		tmp->pos = (d->col / 2) - (tmp->length / 2);
		tmp->index = i;
		tmp->is_selected = NO;
		i++;
		tmp = tmp->next;
	}
	d->tot = i;
	tmp->length = (int)ft_strlen(tmp->str);
	tmp->pos = (d->col / 2) - (tmp->length / 2);
	tmp->index = i;
	tmp->is_selected = NO;
	d->nb_col = d->max_row;
	d->max_length = max_lenght(list, i);
}

t_list		*ft_make_list(char **av, t_data *d)
{
	t_list	*ret;
	int		i;

	i = 1;
	ret = new_list(av[i]);
	while (av[++i] != 0)
		add_element_end(&ret, new_list(av[i]));
	index_list(&ret, d);
	return (ret);
}
