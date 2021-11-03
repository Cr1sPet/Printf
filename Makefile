NAME	=	libftprintf.a

SRCS	=	ft_printf.c ft_parsing.c \
			ft_print_val.c

HEADER	=	libftprintf.h

OBJS	=	$(SRCS:%.c=%.o)

CC		=	gcc

FLAGS	=	-Wall -Werror -Wextra -I $(HEADER)

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADER)
	$(MAKE) all -C ./libft
	$(MAKE) bonus -C ./libft
	cp libft/libft.a $(NAME)
	@ar rcs $(NAME) $?

%.o : &.c $(HEADER)
	@$(CC) $(CFLAGS) -CC $< -O $@

clean	:	
	@$(MAKE) clean -C ./libft
	@rm -f $(OBJS) $(OBJS_B)

fclean	:	clean
	@rm -f $(NAME)
re		: fclean all