/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 17:29:53 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 21:26:52 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
		ft_putchar_fd(' ', FDD);
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
