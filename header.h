
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 17:22:25 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/09 22:43:08 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define YES 1
# define NO 0
# define FD 2

# include <sys/ioctl.h>
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
	int				pos_init;
	int				pos;
	int				is;
	int				selected;
	int				save_selected;
	int				us;
	int				save_us;
	int				max_length;
	int				nb_arg_init;
	int				nb_col;
	int				needed;
	int				pos_tab;
	int				printed_col;
	int				first;
	int				arg_printed;
	int				col_tmp;
	int				pos_t;
}					t_data;

typedef struct		s_list
{
	int				is_selected;
	int				pos;
	int				index;
	int				length;
	char			*str;
	int				li;
	int				co;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

int		ft_get_size(t_data *d);
int		ft_set_stage(int argc, struct termios *term);
void	ft_print_tab(char **tabs);
int		ft_store(t_data *d, char **av, int ac);
int		tputs_putchar(int c);
int		is_bgreq(char *buf);
int		is_arrow(char *buf, t_data *d, t_list *list);
int		is_rtn(char *buf);
void	add_element_end(t_list **list, t_list *new);
t_list 	*ft_make_list(char **av, t_data *d);
void	print_list(t_list *list, t_data *d);
void	add_new_element(t_list **list, t_list *new);
t_list	*new_list(char *str);
int		is_spc(char *buf, t_list *list, t_data *d);
void	print_list_if(t_list *list, t_data *d);
int		is_select(t_list *list, t_data *d);
int		is_us(t_list *list, t_data *d);
void	print_list_us(t_list *list, t_data *d);
void	make_header(t_data *d);
void	make_header_bot(t_data *d);
int		ft_calc_center(t_data *d);
void	ft_put_center(t_data *d);
int		max_lenght(t_list **list, int nb);
void	index_list(t_list **list, t_data *d);
void	get_col_nb(t_data *d);
void	put_tab(int pos_t, t_data *d);
void	print_multi_tab(t_list *list, t_data *d);
void	ft_signals(void);
void	cont(int i);
void	resize(int i);
int		get_size(t_data *d);
int		unset_stage(struct termios *term);
int		set_stage(struct termios *term);
t_list 	*ft_del_elem(t_list *list, t_data *d);
int		is_del(char *buf);

#endif
