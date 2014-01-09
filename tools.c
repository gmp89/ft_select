/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 14:11:35 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/09 21:11:09 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		ft_get_size(t_data *d)
{
	if((d->col = tgetnum("co")) < 1)
		return (-1);
	if((d->li = tgetnum("li")) < 1)
		return (-1);
	return (1);
}

int tputs_putchar(int c)
{
    write(1, &c, 1);
    return (1);
}

void	make_header(t_data *d)
{
	ft_put_center(d);
	ft_putstr("              .__                 __   \n");
	ft_put_center(d);
	ft_putstr("  ______ ____ |  |   ____   _____/  |_ \n");
	ft_put_center(d);
	ft_putstr(" /  ___// __ \\|  | _/ __ \\_/ ___\\   __\\\n");
	ft_put_center(d);
	ft_putstr(" \\___ \\\\  ___/|  |_\\  ___/\\  \\___|  |  \n");
	ft_put_center(d);
	ft_putstr("/____  >\\___  >____/\\___  >\\___  >__|  \n");
	ft_put_center(d);
	ft_putstr("     \\/     \\/          \\/     \\/      \n");
	make_header_bot(d);
}

void	make_header_bot(t_data *d)
{
	int		i;

	i = 1;
	while (i <= d->col)
	{
		ft_putchar('=');
		i++;
	}
	ft_putchar('\n');
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

int		ft_calc_center(t_data *d)
{
	int		a;
	int		b;
	int		c;
	int		z;

	a = (d->col / 2) - 20;
	b = a / 2;
	c = b / 2;
	z = a + (b / 2) - c;
	return (a);
}

void	ft_put_center(t_data *d)
{
	int		i;
	int		center;

	i = 0;
	center = ft_calc_center(d);
	while (i <= center)
	{
		ft_putchar(' ');
		i++;
	}
}

void	get_length(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp->next != NULL)
	{
		tmp->length = ft_strlen(tmp->str);
		ft_putnbr(tmp->length);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void	resize(int i)
{
	char	str[2];

	(void)i;
	str[0] = -62;
	str[1] = '\0';
	ioctl(FD, TIOCSTI, str);
}

void	cont(int i)
{
	char	str[2];
	char	str2[2];

	(void)i;
	str[0] = -62;
	str[1] = '\0';
	str2[0] = 10;
	str2[1] = '\0';
	ioctl(FD, TIOCSTI, str);
	ioctl(FD, TIOCSTI, str2);
}

void	ft_signals(void)
{
	void	*res;
	void	*con;

	con = &cont;
	res = &resize;
	signal(SIGWINCH, res);
	signal(SIGCONT, con);
}

int		set_stage(struct termios *term)
{
	char	buffer[2048];

	if (tgetent(buffer, getenv("TERM")) < 1)
		return (-1);
	tcgetattr(0, term);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	tcsetattr(0, 0, term);
	return (1);
}

int		unset_stage(struct termios *term)
{
	term->c_lflag |= ICANON;
	term->c_lflag |= ECHO;
	tcsetattr(0, 0, term);
	tputs(tgetstr("me", NULL), 1, tputs_putchar);
	tputs(tgetstr("cl", NULL), 1, tputs_putchar);
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	return (1);
}

int		get_size(t_data *d)
{
	struct winsize		ws;

	ioctl(FD, TIOCGWINSZ, &ws);
	if ((d->col = (int)ws.ws_col) < 0)
		return (-1);
	if ((d->li = ws.ws_row) < 0)
		return (-1);
	return (1);
}
