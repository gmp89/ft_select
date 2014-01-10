/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 14:11:35 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/10 17:30:23 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
