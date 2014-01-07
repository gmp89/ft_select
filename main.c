/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 17:00:24 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/07 22:27:05 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

void	ft_print_tab(char **tabs)
{
	int		i;

	i = 0;
	while (tabs[i] != 0)
	{
		ft_putstr(tabs[i]);
		ft_putchar('\n');
		i++;
	}
}

int		ft_store(t_data *d, char **av, int ac)
{
	d->i = 1;
	d->j = 0;
	d->arg = (char **)malloc(sizeof(char *) * ac);
	while (av[d->i] != 0)
	{
		d->arg[d->j] = av[d->i];
		d->i++;
		d->j++;
	}
	d->arg[d->j] = 0;
	return (0);
}

int		ft_get_size(t_list *size)
{
	if((size->co = tgetnum("co")) < 1)
		return (-1);
	if((size->li = tgetnum("li")) < 1)
		return (-1);
	return (1);
}

int tputs_putchar(int c)
{
    write(1, &c, 1);
    return (1);
}


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

void	print_list_us(t_list *list, t_data *d)
{
	t_list	*tmp;

	tmp = list;
	while (tmp->next != NULL)
	{
		if ((tmp->index + 1) == d->pos)
		{
			tputs(tgetstr("us", NULL), 1, tputs_putchar);
			ft_putstr(tmp->str);
			ft_putchar('\n');
			tputs(tgetstr("ue", NULL), 1, tputs_putchar);
			tmp = tmp->next;
		}
		if (tmp->next != NULL)
		{
			ft_putstr(tmp->str);
			ft_putchar('\n');
			tmp = tmp->next;
		}
	}
	if ((tmp->index + 1) == d->pos && d->us == 1)
	{
		tputs(tgetstr("us", NULL), 1, tputs_putchar);
		ft_putstr(tmp->str);
		ft_putchar('\n');
		tputs(tgetstr("ue", NULL), 1, tputs_putchar);
		tmp = tmp->next;
	}
	else
	{
		ft_putstr(tmp->str);
		ft_putchar('\n');
	}
}

int		is_arrow(char *buf, t_data *d, t_list *list)
{
	int		i;
	/* int	rslt; */
	if (buf[0] != 27 && buf[1] != 91)
		return (-1);
	if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 66) && d->pos == d->pos_init)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, tputs_putchar);
		d->pos = (d->pos + 1) - d->pos_init;
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header();
		print_list_us(list, d);
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
	{
		tputs(tgetstr("do", NULL), 1, tputs_putchar);
		d->pos += 1;
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header();
		print_list_us(list, d);
	}
	else if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 65) && d->pos == 1)
	{
		i = 1;
		while (++i <= d->pos_init)
			tputs(tgetstr("do", NULL), 1, tputs_putchar);
		d->pos = d->pos_init;
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header();
		print_list_us(list, d);
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
	{
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		tputs(tgetstr("up", NULL), 1, tputs_putchar);
		d->pos -= 1;
		make_header();
		print_list_us(list, d);
	}
	else
		return (-1);
	return (0);
}

void	ft_print_pos(t_data *d)
{
	ft_putstr("col = ");
	ft_putnbr(d->col);
	ft_putchar('\n');
	ft_putstr("li = ");
	ft_putnbr(d->li);
	ft_putchar('\n');
}

int		is_spc(char *buf, t_list *list, t_data *d)
{
	int		i;

	i = d->pos_init;
	if (buf[0] == 32 && buf[1] == 91)
	{
		tputs(tgetstr("cl", NULL), 1, tputs_putchar);
		make_header();
		/* tputs(tgetstr("us", NULL), 1, tputs_putchar); */
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

/* void	print_help(t_list **tmp, t_data *d) */
/* { */
/* } */


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

int		main(int ac, char **av/* , char **env */)
{
	struct termios	term;
	t_list			*size;
	t_data			d;
	t_list			*list;

	list = NULL;
	size = NULL;
	d.max_row = --ac;
	d.pos_init = d.max_row;
	d.pos = d.pos_init;
	list = ft_make_list(av);
	if(ft_set_stage(ac, &term))
	/* ft_get_size(size); */
	/* print_list(list); */
	/* print_list_if(list, &d); */
	make_header();
	print_list_us(list, &d);
	/* ft_print_tab(d.arg); */
	tputs(tgetstr("up", NULL), 1, tputs_putchar);
	d.us = 1;
	ft_while(&d, &term, list);
//	ft_set_tabs();
//	ft_print(argc, argv);
//	ft_wait_for_input();
	return (0);
}

int		is_rtn(char *buf)
{
	return (buf[0] == 10);
}

void	make_header(void)
{
	ft_putstr("              .__                 __   \n");
	ft_putstr("  ______ ____ |  |   ____   _____/  |_ \n");
	ft_putstr(" /  ___// __ \\|  | _/ __ \\_/ ___\\   __\\\n");
	ft_putstr(" \\___ \\\\  ___/|  |_\\  ___/\\  \\___|  |  \n");
	ft_putstr("/____  >\\___  >____/\\___  >\\___  >__|  \n");
	ft_putstr("     \\/     \\/          \\/     \\/      \n");
	ft_putstr("========================================\n");
}
