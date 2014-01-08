/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 17:00:24 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/08 23:17:16 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"


int		ft_set_stage(int ac, struct termios *term)
{
	char			buffer[2048];

	if (ac < 2)
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

int		is_us(t_list *list, t_data *d)
{
	list->co = 1;
	if (d->us == 1)
		return (1);
	return (0);
}

int		is_select(t_list *list, t_data *d)
{
	list->co = 1;
	if (d->selected == 1)
		return (1);
	return (0);
}

int		is_arrow(char *buf, t_data *d, t_list *list)
{
	int		i;

	if (buf[0] != 27 && buf[1] != 91)
		return (-1);
	if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 66) && d->pos == d->pos_init)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, tputs_putchar);
		d->pos = (d->pos + 1) - d->pos_init;
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header(d);
		print_list_us(list, d);
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
	{
		tputs(tgetstr("do", NULL), 1, tputs_putchar);
		d->pos += 1;
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header(d);
		print_list_us(list, d);
	}
	else if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 65) && d->pos == 1)
	{
		i = 1;
		while (++i <= d->pos_init)
			tputs(tgetstr("do", NULL), 1, tputs_putchar);
		d->pos = d->pos_init;
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header(d);
		print_list_us(list, d);
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
	{
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		tputs(tgetstr("up", NULL), 1, tputs_putchar);
		d->pos -= 1;
		make_header(d);
		print_list_us(list, d);
	}
	else
		return (-1);
	return (0);
}

int		is_spc(char *buf, t_list *list, t_data *d)
{
	int		i;

	i = d->pos_init;
	if (buf[0] == 32 && buf[1] == 91)
	{
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header(d);
		if (is_select(list, d) == 0)
			print_list_if(list, d);
		else
			print_list(list, d);
		while (i-- >= d->pos)
			tputs(tgetstr("up", NULL), 1, tputs_putchar);
		return (0);
	}
	else
		return (-1);
}

int		ft_while(t_data *d, struct termios *term, t_list *list)
{
		while (ft_strcmp(d->read_char, "exit") != 0)
		{
			read(0, d->read_char, 3);
			/* if (is_bgreq(d->read_char)) */
			/* { */
			/* 	/\* printf("Todo : put in background"); *\/ */
			/* 	term.c_lflag |= ICANON; */
			/* 	term.c_lflag |= ECHO; */
			/* 	tcsetattr(0, 0, &term); */
			/* 	tputs(tgetstr("ti", NULL), 1, tputs_putchar); */
			/* } */
			if (is_rtn(d->read_char))
			{
				term->c_lflag |= ICANON;
				term->c_lflag |= ECHO;
				tcsetattr(0, 0, term); /* back to default values */
				tputs(tgetstr("ti", NULL), 1, tputs_putchar);
				return (1);
			}
			if (is_arrow(d->read_char, d, list) == 0)
				;
			else if (is_spc(d->read_char, list, d) == 0)
				;
			else
				printf("%d %d %d\n", d->read_char[0], d->read_char[1], d->read_char[2]);
		}
		return (0);
}

int		main(int ac, char **av/* , char **env */)
{
	struct termios	term;
	/* t_list			size; */
	t_data			d;
	t_list			*list;

	list = NULL;
	d.max_row = --ac;
	d.pos_init = d.max_row;
	d.pos = d.pos_init;
	list = ft_make_list(av, &d);
	if(ft_set_stage(ac, &term))
	ft_get_size(&d);
	make_header(&d);
	get_col_nb(&d);
	print_list_us(list, &d);
	/* print_multi_tab(list, &d); */
	/* tputs(tgetstr("vi", NULL), 1, tputs_putchar); */
	/* d.us = 1; */
	ft_while(&d, &term, list);
//	ft_set_tabs();
//	ft_wait_for_input();
	return (0);
}

int		is_rtn(char *buf)
{
	return (buf[0] == 10);
}

