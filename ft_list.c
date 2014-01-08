/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 14:09:42 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/08 15:01:24 by gpetrov          ###   ########.fr       */
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

void		index_list(t_list **list)
{
	t_list	*tmp;
	int		i;

	i = 1;
	tmp = *list;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		tmp->index = i;
		i++;
	}
}

t_list		*ft_make_list(char **av)
{
	t_list	*ret;
	int		i;

	i = 1;
	ret = new_list(av[i]);
	while (av[++i] != 0)
		add_element_end(&ret, new_list(av[i]));
	index_list(&ret);
	return (ret);
}

t_list	*new_list(char *str)
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

void	print_list(t_list *list, t_data *d)
{
	t_list	*tmp;

	tmp = list;
	while (tmp->next != NULL)
	{
		ft_putstr(tmp->str);
		/* ft_putnbr(tmp->index); */
		ft_putchar('\n');
		tmp = tmp->next;
	}
	ft_putstr(tmp->str);
	/* ft_putnbr(tmp->index); */
	ft_putchar('\n');
	d->selected = 0;
}

void	print_list_if(t_list *list, t_data *d)
{
	t_list	*tmp;

	tmp = list;
	while (tmp->next != NULL)
	{
		if ((tmp->index + 1) == d->pos)
		{
			tputs(tgetstr("mr", NULL), 1, tputs_putchar);
			tputs(tgetstr("us", NULL), 1, tputs_putchar);
			ft_putstr(tmp->str);
			ft_putchar('\n');
			tputs(tgetstr("ue", NULL), 1, tputs_putchar);
			tputs(tgetstr("me", NULL), 1, tputs_putchar);
			tmp = tmp->next;
		}
		if (tmp->next != NULL)
		{
			ft_putstr(tmp->str);
			ft_putchar('\n');
			tmp = tmp->next;
		}
	}
	if ((tmp->index + 1) == d->pos && d->is == 1)
	{
		tputs(tgetstr("mr", NULL), 1, tputs_putchar);
		tputs(tgetstr("us", NULL), 1, tputs_putchar);
		ft_putstr(tmp->str);
		ft_putchar('\n');
		tputs(tgetstr("ue", NULL), 1, tputs_putchar);
		tputs(tgetstr("me", NULL), 1, tputs_putchar);
		tmp = tmp->next;
	}
	else
	{
		ft_putstr(tmp->str);
		ft_putchar('\n');
	}
	d->is = 1;
	d->selected = 1;
}
