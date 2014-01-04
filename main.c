/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 17:00:24 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/04 17:05:01 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "header.h"

int		is_rtn(char *buf)
{
	return (buf[0] == 10);
}

int		is_arrow(char *buf)
{
	/* int	rslt; */
	if (buf[0] != 27 || buf[1] != 91)
		return (0);
	if (buf[2] == 65)
		return (1);
	if (buf[2] == 66)
		return (2);
	if (buf[2] == 67)
		return (3);
	if (buf[2] == 68)
		return (4);
	else
		return (0);
}

int		is_bgreq(char *buf)
{
	if (buf[0] == 26)
		return (1);
	else
		return (0);
}

int		 tputs_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int		main(void)
{
	char	buffer[2048];
	struct termios	term;
	char	read_char[4] = {0};

	if (tgetent(buffer, getenv("TERM")) < 1)
		return (-1);
	tcgetattr(0, &term);
	term.c_lflag &= ICANON; /* each char is treated independently */
	term.c_lflag &= ECHO; /* prevents a char from being output when pressed*/
	tcsetattr(0, 0, &term);
	tputs(tgetstr("ti", NULL), 1, tputs_putchar);
	tputs(tgetstr("mr", NULL), 1, tputs_putchar); /* turns on reverse video */
	write(1, "video", 13);
	tputs(tgetstr("me", NULL), 1, tputs_putchar); /* turns off all */
	tputs(tgetstr("do", NULL), 1, tputs_putchar); /* cursor down one line */
	write(1, "normal", 7);
	tputs(tgetstr("do", NULL), 1, tputs_putchar); /* cursor down one line */
	while (ft_strcmp(read_char, "exit") != 0)
	{
		read(0, read_char, 3);
		if (is_bgreq(read_char))
		{
			printf("Todo : put in background");
			/*
			  term.c_lflag |= ICANON;
			  term.c_lflag |= ECHO;
			  tcsetattr(0, 0, &term);
			  tputs(tgetstr("ti", NULL), 1, tputs_putchar);
			*/
		}
		if (is_rtn(read_char))
		{
			term.c_lflag |= ICANON;
			term.c_lflag |= ECHO;
			tcsetattr(0, 0, &term); /* back to default values */
			tputs(tgetstr("ti", NULL), 1, tputs_putchar);
			return (1);
		}
		if (is_arrow(read_char))
			printf("Todo\n");
		else
			printf("%d %d %d\n", read_char[0], read_char[1], read_char[2]);
	}
	return (0);
}
