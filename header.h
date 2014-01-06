/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 17:22:25 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/06 19:59:54 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>
# include <term.h>
# include "libft/includes/libft.h"

typedef struct		s_data
{
	int				i;
	int				j;
	char			**arg;
	char			buffer[2048];
	char			read_char[4];
	int				max_row;
	int				col;
	int				li;
}					t_data;

typedef struct	s_window
{
	int	li;
	int	co;
}				t_window;

int		ft_get_size(t_window *size);
int		ft_set_stage(int argc, struct termios *term);
void	ft_print_tab(char **tabs);
int		ft_store(t_data *d, char **av, int ac);
int		 tputs_putchar(int c);
int		is_bgreq(char *buf);
int		is_arrow(char *buf);
int		is_rtn(char *buf);

#endif