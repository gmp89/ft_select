/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 14:09:42 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/09 22:46:02 by gpetrov          ###   ########.fr       */
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
	{
		/* ft_putchar(' '); */
		i++;
	}
}

void	print_multi_tab(t_list *list, t_data *d)
{
	/* int		arg_printed; */
	t_list	*tmp;
	/* int		col_tmp; */

	tmp = list;
	d->arg_printed = 0;
	d->col_tmp = d->col / d->needed;
	d->first = YES;
	d->printed_col = 0;
	while (tmp->next != NULL)
	{
		if ((tmp->index + 1) == d->pos)
		{
			/* if ((arg_printed + 1) == d->li) */
			/* { */
			/* 	arg_printed = 0; */
			/* 	col_tmp = col_tmp * 2; */
			/* 	tputs(tgoto(tgetstr("cm", NULL), d->pos_tab, 0), 1, tputs_putchar); */
			/* } */
			if ((d->arg_printed + 10) == d->li)
			{
				d->printed_col++;
				d->arg_printed = 0;
			}
			put_tab(tmp->length, d);
			tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar);
			tputs(tgetstr("us", NULL), 1, tputs_putchar);
			if (tmp->is_selected == YES)
				tputs(tgetstr("mr", NULL), 1, tputs_putchar);
			ft_putstr(tmp->str);
			tputs(tgetstr("me", NULL), 1, tputs_putchar);
			d->arg_printed++;
			ft_putchar('\n');
			tputs(tgetstr("ue", NULL), 1, tputs_putchar);
			tmp = tmp->next;
		}
		if (tmp->next != NULL)
		{
			if ((d->arg_printed + 10) == d->li)
			{
				d->printed_col++;
				d->arg_printed = 0;
			}
			put_tab(tmp->length, d);
			tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar);
			if (tmp->is_selected == YES)
				tputs(tgetstr("mr", NULL), 1, tputs_putchar);
			ft_putstr(tmp->str);
			tputs(tgetstr("me", NULL), 1, tputs_putchar);
			d->arg_printed++;
			ft_putchar('\n');
			tmp = tmp->next;
		}
	}
	if ((tmp->index + 1) == d->pos && d->us == 1)
	{
		if ((d->arg_printed + 10) == d->li)
		{
			d->printed_col++;
			d->arg_printed = 0;
		}
		put_tab(tmp->length, d);
		tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar);
		tputs(tgetstr("us", NULL), 1, tputs_putchar);
		if (tmp->is_selected == YES)
				tputs(tgetstr("mr", NULL), 1, tputs_putchar);
			ft_putstr(tmp->str);
			tputs(tgetstr("me", NULL), 1, tputs_putchar);
		d->arg_printed++;
		ft_putchar('\n');
		tputs(tgetstr("ue", NULL), 1, tputs_putchar);
		tmp = tmp->next;
	}
	else
	{
		if ((d->arg_printed + 10) == d->li)
		{
			d->printed_col++;
			d->arg_printed = 0;
		}
		put_tab(tmp->length, d);
		tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar);
		if (tmp->is_selected == YES)
			tputs(tgetstr("mr", NULL), 1, tputs_putchar);
		ft_putstr(tmp->str);
		tputs(tgetstr("me", NULL), 1, tputs_putchar);
		d->arg_printed++;
		ft_putchar('\n');
	}
	d->is = 1;
	d->selected = 1;
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
	/* return (d->needed); */
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

int		max_lenght(t_list **list, int nb)
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

t_list		*ft_del_elem(t_list *list, t_data *d)
{
	t_list	*tmp;
    /* Liste vide, il n'y a plus rien à supprimer */
    if (list == NULL)
        return (NULL); 
    /* Si l'élément en cours de traitement doit être supprimé */
    if(list->is_selected == YES)
    {
        /* On le supprime en prenant soin de mémoriser 
		   l'adresse de l'élément suivant */
        tmp = list->next;
        free(list);
        /* L'élément ayant été supprimé, la liste commencera à l'élément suivant
		   pointant sur une liste qui ne contient plus aucun élément ayant la valeur recherchée */
        tmp = ft_del_elem(tmp, d);
        return tmp;
    }
    else
    {
        /* Si l'élement en cours de traitement ne doit pas être supprimé,
        alors la liste finale commencera par cet élément et suivra une liste ne contenant
        plus d'élément ayant la valeur recherchée */
        list->next = ft_del_elem(list->next, d);
        return (list);
    }
	index_list(&list, d);
	print_multi_tab(list, d);
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
	d->arg_printed = 0;
	d->col_tmp = d->col / d->needed;
	d->first = YES;
	d->printed_col = 0;
	while (tmp->next != NULL)
	{
		if ((d->arg_printed + 10) == d->li)
		{
			d->printed_col++;
			d->arg_printed = 0;
		}
		put_tab(tmp->length, d);
		tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar);
		ft_putstr(tmp->str);
		d->arg_printed++;
		/* ft_putnbr(tmp->index); */
		ft_putchar('\n');
		tmp = tmp->next;
	}
	if ((d->arg_printed + 10) == d->li)
	{
		d->printed_col++;
		d->arg_printed = 0;
	}
	put_tab(tmp->length, d);
	tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar);
	ft_putstr(tmp->str);
	d->arg_printed++;
	/* ft_putnbr(tmp->index); */
	ft_putchar('\n');
	d->selected = 0;
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
			tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar);
			tputs(tgetstr("us", NULL), 1, tputs_putchar);
			ft_putstr(tmp->str);
			d->arg_printed++;
			ft_putchar('\n');
			tputs(tgetstr("ue", NULL), 1, tputs_putchar);
			tputs(tgetstr("me", NULL), 1, tputs_putchar);
			tmp = tmp->next;
		}
		if (tmp->next != NULL)
		{
			if ((d->arg_printed + 10) == d->li)
			{
				d->printed_col++;
				d->arg_printed = 0;
			}
			put_tab(tmp->length, d);
			tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar);
			if (tmp->is_selected == YES)
				tputs(tgetstr("mr", NULL), 1, tputs_putchar);
			ft_putstr(tmp->str);
			tputs(tgetstr("me", NULL), 1, tputs_putchar);
			d->arg_printed++;
			ft_putchar('\n');
			tmp = tmp->next;
			}
		}
	if ((tmp->index + 1) == d->pos && d->is == 1)
	{
		if ((d->arg_printed + 10) == d->li)
		{
			d->printed_col++;
			d->arg_printed = 0;
		}
		put_tab(tmp->length, d);
		tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar);
		if (tmp->is_selected == YES)
			tputs(tgetstr("mr", NULL), 1, tputs_putchar);
		tputs(tgetstr("us", NULL), 1, tputs_putchar);
		ft_putstr(tmp->str);
		d->arg_printed++;
		ft_putchar('\n');
		tputs(tgetstr("ue", NULL), 1, tputs_putchar);
		tputs(tgetstr("me", NULL), 1, tputs_putchar);
		tmp = tmp->next;
	}
	else
	{
		if ((d->arg_printed + 10) == d->li)
		{
			d->printed_col++;
			d->arg_printed = 0;
		}
		put_tab(tmp->length, d);
		tputs(tgoto(tgetstr("cm", NULL), d->pos_t, (d->arg_printed + 10)), 1, tputs_putchar);
		ft_putstr(tmp->str);
		d->arg_printed++;
		ft_putchar('\n');
	}
	d->is = 1;
	d->selected = 1;
}

void	print_list_us(t_list *list, t_data *d)
{
	t_list	*tmp;

	tmp = list;
	while (tmp->next != NULL)
	{
		if ((tmp->index + 1) == d->pos)
		{
			put_arg_center(tmp->length, d);
			tputs(tgetstr("us", NULL), 1, tputs_putchar);
			ft_putstr(tmp->str);
			ft_putchar('\n');
			tputs(tgetstr("ue", NULL), 1, tputs_putchar);
			tmp = tmp->next;
		}
		if (tmp->next != NULL)
		{
			put_arg_center(tmp->length, d);
			ft_putstr(tmp->str);
			ft_putchar('\n');
			tmp = tmp->next;
		}
	}
	if ((tmp->index + 1) == d->pos && d->us == 1)
	{
		put_arg_center(tmp->length, d);
		tputs(tgetstr("us", NULL), 1, tputs_putchar);
		ft_putstr(tmp->str);
		ft_putchar('\n');
		tputs(tgetstr("ue", NULL), 1, tputs_putchar);
		tmp = tmp->next;
	}
	else
	{
		put_arg_center(tmp->length, d);
		ft_putstr(tmp->str);
		ft_putchar('\n');
	}
}

