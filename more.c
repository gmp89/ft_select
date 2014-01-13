/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 22:28:16 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 22:52:57 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*ft_is_3_bis(t_list *tmp)
{
	if (tmp->is_selected == YES)
	{
		tmp->is_selected = NO;
		tputs(tgetstr("me", NULL), 1, tputs_putchar);
	}
	else if (tmp->is_selected == NO)
	{
		tmp->is_selected = YES;
		tputs(tgetstr("mr", NULL), 1, tputs_putchar);
	}
	return (tmp);
}

int		ft_while_help(t_data *d, struct termios *term, t_list *list, char *buf)
{

	if (is_resize(buf, d, list, term) == 1)
		;
	else if (is_ctrl_c(buf, term) == 1)
		;
	else if (is_esc(buf))
	{
		ft_quit(term);
		exit(0);
	}
	return (0);
}
