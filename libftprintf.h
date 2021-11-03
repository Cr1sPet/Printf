#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>

typedef struct s_flags
{
	int		null_filler;
	int		minus;
	int		width;
	int		plus;
	int		space;
	int		precision;
	int		hash;
	char	specifier;
}	t_flags;

int ft_printf(const char *f, ...);

#endif