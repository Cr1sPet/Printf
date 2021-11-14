#include "ft_printf.h"
#include "libft/libft.h"

static int ft_isspecifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p'
			|| c == 'd' || c == 'i' || c == 'u'
			|| c == 'x' || c == 'X' || c == '%');
}

static void ft_check_flags(t_flags *flags, const char *f, int *i)
{
	while(1)
	{
		if ('#' == f[*i])
			flags->hash = 1;
		else if ('+' == f[*i])
			flags->plus = 1;
		else if (' ' == f[*i])
			flags->space = 1;
		else if ('-' == f[*i])
			flags->minus = 1;
		else if ('0' == f[*i])
			flags->null_filler = 1;
		else
			break;
		(*i)++;
	}
}

int ft_parsing(t_flags *flags, const char *f, int *i)
{
	ft_check_flags(flags, f, i);
	while(ft_isdigit(f[*i]))
		flags->width = (flags->width * 10) + (f[(*i)++] - 48);
	if ('.' == f[*i])
	{
		flags->dot = 1;
		(*i)++;
	}
	while(ft_isdigit(f[*i]))
		flags->precision = (flags->precision * 10) + (f[(*i)++] - 48);
	if (ft_isspecifier(f[*i]))
	{
		flags->specifier = f[*i];
		return (1);
	}
	return (0);
}