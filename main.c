/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 17:00:24 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 20:01:52 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

int		ft_set_stage(int ac, struct termios *term)
{
	char			buffer[2048];

	if (ac < 1)
	{
		ft_putstr("usage: ft_select, choice1 choice2 etc.");
		return (-1);
	}
	else
	{
		if (tgetent(buffer, getenv("TERM")) < 1)
			return (-1);
		tcgetattr(0, term);
		term->c_lflag &= ~(ICANON);
		term->c_lflag &= ~(ECHO);
		term->c_cc[VMIN] = 1;
		term->c_cc[VTIME] = 0;
		tcsetattr(0, 0, term);
		tputs(tgetstr("ti", NULL), 1, tputs_putchar);
	}
	return (1);
}

void	final_print(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	while (tmp->next != NULL)
	{
		if (tmp->is_selected == YES)
		{
			ft_putstr(tmp->str);
			ft_putchar(' ');
		}
		tmp = tmp->next;
	}
	if (tmp->is_selected == YES)
		ft_putstr(tmp->str);
	ft_putchar('\n');
}

int		ft_while(t_data *d, struct termios *term, t_list *list)
{
	while (42)
		{
			ft_bzero(d->read_char, 3);
			read(0, d->read_char, 3);
			if (is_rtn(d->read_char))
			{
				term->c_lflag |= ICANON;
				term->c_lflag |= ECHO;
				tcsetattr(0, 0, term);
				unset_stage(term);
				final_print(list);
				return (1);
			}
			if (is_resize(d->read_char, d, list, term) == 1)
				;
			else if (is_arrow(d->read_char, d, list) == 0)
					;
			else if (is_spc(d->read_char,  list, d) == 0)
				;
			else if (is_del(d->read_char))
				list = ft_del_elem(list, d);
			else
				printf("%d %d %d\n", d->read_char[0], d->read_char[1], d->read_char[2]);
			if (list == NULL)
				break ;
		}
		return (0);
}

int		main(int ac, char **av)
{
	struct termios	term;
	t_data			d;
	t_list			*list;

	if (ac <= 1)
		return (0);
	list = NULL;
	d.max_row = --ac;
	d.pos_init = d.max_row;
	d.pos = d.pos_init;
	list = ft_make_list(av, &d);
	if (ft_set_stage(ac, &term))
	ft_get_size(&d);
	make_header(&d);
	get_col_nb(&d);
	ft_signals();
	print_multi_tab(list, &d);
	/* tputs(tgetstr("vi", NULL), 1, tputs_putchar); */
	d.us = 1;
	ft_while(&d, &term, list);
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	/* unset_stage(&term); */
	return (0);
}
