/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 14:11:35 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 22:54:44 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_signals(void)
{
	void	*res;
	void	*con;
	void	*inter;
	void	*susp;

	susp = &suspend;
	con = &cont;
	res = &resize;
	inter = &interupt;
	signal(SIGWINCH, res);
	signal(SIGCONT, con);
	signal(SIGINT, inter);
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
