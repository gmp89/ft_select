/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 17:14:30 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 22:57:34 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_resize(char *buf, t_data *d, t_list *list, struct termios *term)
{
	if (buf[0] == -62)
	{
		unset_stage(term);
		set_stage(term);
		get_size(d);
		make_header(d);
		print_multi_tab(list, d);
		return (1);
	}
	return (0);
}

int		is_ctrl_z(char *buf, struct termios *term)
{
	if (buf[0] == -74)
	{
		ft_quit(term);
		exit(0);
		return (1);
	}
	return (0);
}

int		is_ctrl_c(char *buf, struct termios *term)
{
	if (buf[0] == -73)
	{
		ft_quit(term);
		exit(0);
		return (1);
	}
	return (0);
}

int		is_rtn(char *buf)
{
	return (buf[0] == 10);
}

int		is_del(char *buf)
{
	return ((buf[0] == 127 || buf[0] == 126) && buf[1] == 0 && buf[2] == 0);
}
