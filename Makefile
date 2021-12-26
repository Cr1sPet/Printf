# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 14:23:46 by jchopped          #+#    #+#              #
#    Updated: 2021/11/16 17:56:23 by jchopped         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

SRCS	=	ft_printf.c parsing.c\
			parse_numb_utils.c print_char.c\
			parse_print_numb.c print_numb_utils.c

HEADER	=	ft_printf.h

%.o : &.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -O $@

OBJ	=	$(SRCS:%.c=%.o)


CC		=	gcc

FLAGS	=	-Wall -Werror -Wextra

.PHONY	:	all bonus clean fclean re

all		:	$(NAME)

bonus	:	$(NAME)

$(NAME)	:	$(OBJ)
	@$(MAKE) all -C ./libft
	@$(MAKE) bonus -C ./libft
	@cp libft/libft.a $(NAME)
	@ar rcs $(NAME) $(OBJ)


clean	:	
	@$(MAKE) clean -C ./libft
	@rm -f $(OBJ)

fclean	:	clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
re		: fclean all