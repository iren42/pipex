# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iren <iren@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 17:41:07 by iren              #+#    #+#              #
#    Updated: 2022/03/08 22:22:25 by iren             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

LIBFT	= libft

LIBFTPRINTF	= ft_printf

HEADER	= include/pipex.h

DIR_SOURCES	= src/

SOURCES		=	pipex.c \
				utils.c

SRCS	=	$(addprefix $(DIR_SOURCES), $(SOURCES))

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= 
#-Wall -Wextra -Werror 

RM		= rm -f

all		: $(NAME)

%.o		: %.c $(HEADER)
		$(CC) $(CFLAGS) -Iinclude -g -c $< -o $@

$(NAME) : $(OBJS) $(HEADER) $(LIBFT)
		make -C $(LIBFT)
		make bonus -C $(LIBFT)
	  	$(CC) -o $@ $(OBJS) libft/libft.a
#	  $(CC) -o $@ $(OBJS) ft_printf/libftprintf.a
	

norm	:
		norminette $(SRCS)
		norminette -R CheckDefine $(HEADER)

clean	:
		$(RM) $(OBJS)
		make clean -C $(LIBFT)
		$(RM) $(OBJS:.o=.d)

fclean	: clean
		$(RM) $(NAME)

re		: fclean all

-include $(OBJS:.o=.d)

.PHONY:	all clean fclean re
