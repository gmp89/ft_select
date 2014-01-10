/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 16:50:02 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/10 20:00:56 by gpetrov          ###   ########.fr       */
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
/*
t_list		*ft_del_elem(t_list *list, t_data *d)
{
	t_list	*tmp;

	if (list == NULL)
		return (NULL);
	if (list->is_selected == YES)
	{
		tmp = list->next;
		free(list);
		tmp = ft_del_elem(tmp, d);
		index_list(&list, d);
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header(d);
		print_multi_tab(list, d);
		return (tmp);
	}
	else
	{
		list->next = ft_del_elem(list->next, d);
		index_list(&list, d);
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header(d);
		print_multi_tab(list, d);
		return (list);
	}
}
*/

static int	ft_del_this_elem(t_list **list, t_list *elt)
{
	if (*list == NULL)
		return (0);
	if (elt->next == NULL)
	{
		if (*list == elt)
			*list = NULL;
		free(elt);
		return (0);
	}
	else
	{
		if (*list == elt)
			*list = elt->next;
		if (elt->prev != NULL)
		{
			elt->prev->next = elt->next;
		}
		elt->next->prev = elt->prev;
		free(elt);
        return (1);
    }
}

t_list		*ft_del_elem(t_list *list, t_data *d)
{
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->is_selected == YES)
		{
			ft_del_this_elem(&list, tmp);
			/* d->pos--; */
			/* d->pos_init--; */
		}
		tmp = tmp->next;
	}
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
	tmp->length = ft_strlen(tmp->str);
	tmp->pos = (d->col / 2) - (tmp->length / 2);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		tmp->length = ft_strlen(tmp->str);
		tmp->pos = (d->col / 2) - (tmp->length / 2);
		tmp->index = i;
		tmp->is_selected = NO;
		i++;
	}
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

t_list		*new_list(char *str)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (new_list == NULL)
		return (NULL);
	if (str == NULL)
		new_list->str = NULL;
	else
		new_list->str = ft_strdup(str);
	new_list->next = NULL;
	new_list->prev = NULL;
	return (new_list);
}
