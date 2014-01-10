/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/10 17:14:30 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/10 17:16:32 by gpetrov          ###   ########.fr       */
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

int		is_rtn(char *buf)
{
	return (buf[0] == 10);
}

int		is_del(char *buf)
{
	return (buf[0] == 127 && buf[1] == 91);
}
