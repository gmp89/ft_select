/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 17:29:53 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/10 17:30:24 by gpetrov          ###   ########.fr       */
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
