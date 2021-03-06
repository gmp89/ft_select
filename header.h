/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 17:22:25 by gpetrov           #+#    #+#             */
/*   Updated: 2014/01/12 23:28:24 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define YES 1
# define NO 0
# define FD 2
# define FDD isatty(STDOUT_FILENO)
# define PU (d->arg_printed + 10)), 1, tputs_putchar

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
	int				tot;
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
t_list	*ft_make_list(char **av, t_data *d);
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
t_list	*ft_del_elem(t_list *list, t_data *d, struct termios *term);
int		is_del(char *buf);
int		is_resize(char *buf, t_data *d, t_list *list, struct termios *term);
t_list	*ft_multi_1(t_list *tmp, t_data *d);
t_list	*ft_multi_2(t_list *tmp, t_data *d);
t_list	*ft_multi_3(t_list *tmp, t_data *d);
t_list	*ft_multi_4(t_list *tmp, t_data *d);
t_list	*ft_if_1(t_list *tmp, t_data *d);
t_list	*ft_if_2(t_list *tmp, t_data *d);
t_list	*ft_if_3(t_list *tmp, t_data *d);
t_list	*ft_if_4(t_list *tmp, t_data *d);
void	is_spc_1(t_list *list, t_data *d);
void	is_spc_2(t_list *list, t_data *d);
void	ft_arrow_1(t_list *list, t_data *d);
void	ft_arrow_2(t_list *list, t_data *d);
void	ft_arrow_3(t_list *list, t_data *d);
void	ft_arrow_4(t_list *list, t_data *d);
void	final_print(t_list *list);
void	ft_quit(struct termios *term);
int		is_esc(char *buf);
void	interupt(int i);
void	suspend(int i);
int		is_ctrl_c(char *buf, struct termios *term);
int		is_ctrl_z(char *buf, struct termios *term);
t_list	*ft_is_3_bis(t_list *tmp);
int		ft_while_help(t_data *d, struct termios *term, t_list *list, char *buf);

#endif
