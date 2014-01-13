#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/03 17:21:43 by gpetrov           #+#    #+#              #
#    Updated: 2014/01/12 22:29:14 by gpetrov          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= ft_select
SRCS	= main.c ft_list.c ft_list2.c tools.c ft_multi.c ft_if.c ft_arrow.c\
		ft_is.c ft_is2.c tools2.c tools3.c signal.c more.c
OBJS	= ${SRCS:.c=.o}
INC		= ./
FLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	cc $(FLAGS) $(SRCS) -o $(NAME) -I libft/includes\
	 -L libft/ -lft -L /usr/lib -ltermcap
%.o: %.c
	cc -c $< -o $@ $(FLAGS) -I$(INC)
gdb:
	make -C libft
	cc -g $(FLAGS) $(SRCS) -o $(NAME) -I libft/includes\
	 -L libft/ -lft -L /usr/lib -ltermcap
	gdb $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
