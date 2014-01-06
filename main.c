/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 17:00:24 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/06 22:25:31 by gpetrov          ###   ########.fr       */
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

int		ft_get_size(t_window *size)
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

int		is_arrow(char *buf, t_data *d)
{
	/* int	rslt; */
	if (buf[0] != 27 && buf[1] != 91)
		return (-1);
	if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 66) && d->pos == d->pos_init)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, tputs_putchar);
		d->pos = (d->pos + 1) - d->pos_init;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
	{
		tputs(tgetstr("do", NULL), 1, tputs_putchar);
		d->pos += 1;
	}
	else if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 65) && d->pos == 1)
	{
		int		i;

		i = 1;
		while (++i <= d->pos_init)
			tputs(tgetstr("do", NULL), 1, tputs_putchar);
		d->pos = d->pos_init;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
	{
		tputs(tgetstr("up", NULL), 1, tputs_putchar);
		d->pos -= 1;
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

int		ft_while(t_data *d, struct termios *term)
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
			if (is_arrow(d->read_char, d) == 0)
				;
			else
				printf("%d %d %d\n", d->read_char[0], d->read_char[1], d->read_char[2]);
		}
		return (0);
}
int		main(int ac, char **av/* , char **env */)
{
	struct termios	term;
	t_window		size;
	t_data			d;

	d.max_row = --ac;
	d.pos_init = d.max_row;
	d.pos = d.pos_init;
	ft_store(&d, av, ac);
	if(ft_set_stage(ac, &term))
	ft_get_size(&size);
	ft_print_tab(d.arg);
	tputs(tgetstr("up", NULL), 1, tputs_putchar);
	ft_while(&d, &term);
//	ft_set_tabs();
//	ft_print(argc, argv);
//	ft_wait_for_input();
	return (0);
}

int		is_rtn(char *buf)
{
	return (buf[0] == 10);
}

/* int		is_bgreq(char *buf) */
/* { */
/* 	if (buf[0] == 26) */
/* 		return (1); */
/* 	else */
/* 		return (0); */
/* } */

/* int		 tputs_putchar(int c) */
/* { */
/* 	write(1, &c, 1); */
/* 	return (1); */
/* } */

/* int		main(int ac, char **av, char **env) */
/* { */
/* 	t_data			d; */
/* 	struct termios	term; */
/* 	char			buffer[2048]; */
/* 	char			read_char[4] = {0}; */
/* 	(void)env; */

/* 	if (ac > 0) */
/* 	{ */
/* 		ft_store(&d, av, ac); */
/* 		/\* ft_print_tab(d.arg); *\/ */
/* 		if (tgetent(buffer, getenv("TERM")) < 1) */
/* 			return (-1); */
/* 		tcgetattr(0, &term); */
/* 		term.c_lflag &= ICANON; /\* each char is treated independently *\/ */
/* 		term.c_lflag &= ECHO; /\* prevents a char from being output when pressed*\/ */
/* 		tcsetattr(0, 0, &term); */
/* 		tputs(tgetstr("ti", NULL), 1, tputs_putchar); */
/* 		tputs(tgetstr("mr", NULL), 1, tputs_putchar); /\* turns on reverse video *\/ */
/* 		write(1, "Menu", 4); */
/* 		ft_putchar('\n'); */
/* 		tputs(tgetstr("me", NULL), 1, tputs_putchar); */
/* 		ft_print_tab(d.arg); */
/* 		/\* tputs(tgetstr("me", NULL), 1, tputs_putchar); /\\* turns off all *\\/ *\/ */
/* 		/\* tputs(tgetstr("do", NULL), 1, tputs_putchar); /\\* cursor down one line *\\/ *\/ */
/* 		/\* write(1, "normal", 7); *\/ */
/* 		/\* tputs(tgetstr("do", NULL), 1, tputs_putchar); /\\* cursor down one line *\\/ *\/ */
/* 		while (ft_strcmp(read_char, "exit") != 0) */
/* 		{ */
/* 			read(0, read_char, 3); */
/* 			if (is_bgreq(read_char)) */
/* 			{ */
/* 				/\* printf("Todo : put in background"); *\/ */
/* 				term.c_lflag |= ICANON; */
/* 				term.c_lflag |= ECHO; */
/* 				tcsetattr(0, 0, &term); */
/* 				tputs(tgetstr("ti", NULL), 1, tputs_putchar); */
/* 			} */
/* 			if (is_rtn(read_char)) */
/* 			{ */
/* 				term.c_lflag |= ICANON; */
/* 				term.c_lflag |= ECHO; */
/* 				tcsetattr(0, 0, &term); /\* back to default values *\/ */
/* 				tputs(tgetstr("ti", NULL), 1, tputs_putchar); */
/* 				return (1); */
/* 			} */
/* 			if (is_arrow(read_char) != -1) */
/* 			{ */
/* 				; */
/* 				/\* printf("Todo\n"); *\/ */
/* 				/\* tputs(tgetstr("do", NULL), 1, tputs_putchar); *\/ */
/* 				/\* printf("%d %d %d\n", read_char[0], read_char[1], read_char[2]); *\/ */
/* 			} */
/* 			else */
/* 				printf("%d %d %d\n", read_char[0], read_char[1], read_char[2]); */
/* 		} */
/* 		free(d.arg); */
/* 	} */
/* 	return (0); */
/* } */
