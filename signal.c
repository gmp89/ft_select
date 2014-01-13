/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 22:17:09 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 22:59:35 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	resize(int i)
{
	char	str[2];

	(void)i;
	str[0] = -62;
	str[1] = '\0';
	ioctl(FD, TIOCSTI, str);
}

void	interupt(int i)
{
	char	str[2];

	(void)i;
	str[0] = -73;
	str[1] = '\0';
	ioctl(FD, TIOCSTI, str);
}

void	suspend(int i)
{
	char	str[2];

	(void)i;
	str[0] = -74;
	str[1] = '\0';
	ioctl(FD, TIOCSTI, str);
}

int		is_esc(char *buf)
{
	return (buf[0] == 27 && buf[1] == 0 && buf[2] == 0);
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
