# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iren <iren@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 17:41:07 by iren              #+#    #+#              #
#    Updated: 2022/03/10 09:50:56 by iren             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

HEADER	= include/pipex.h

DIR_SOURCES	= src/

SOURCES		=	pipex.c \
				utils.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strjoin.c \
				ft_strncmp.c 


SRCS	=	$(addprefix $(DIR_SOURCES), $(SOURCES))

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= 
#-Wall -Wextra -Werror 

RM		= rm -f

all		: $(NAME)

%.o		: %.c $(HEADER)
		$(CC) $(CFLAGS) -Iinclude -g -c $< -o $@

$(NAME) : $(OBJS) $(HEADER)
	  	$(CC) -o $@ $(OBJS)
	

norm	:
		norminette $(SRCS)
		norminette -R CheckDefine $(HEADER)

clean	:
		$(RM) $(OBJS)
		$(RM) $(OBJS:.o=.d)

fclean	: clean
		$(RM) $(NAME)

re		: fclean all

-include $(OBJS:.o=.d)

.PHONY:	all clean fclean re
