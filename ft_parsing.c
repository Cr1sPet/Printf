#include "libftprintf.h"
#include "libft/libft.h"

int ft_isspecifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p'
			|| c == 'd' || c == 'i' || c == 'u'
			|| c == 'x' || c == 'X' || c == '%');
}


int num_proccessing (t_flags *flags, const char *f, int *i, int *num) // Get and Return num value from input string
{
	int	ok;
	char *num_str;
	int	j;

	j = *i;
	while(ft_isalnum(f[*i]) && f[*i])
		*i++;
	num_str = ft_substr(f, j, (*i - 1));
	if (NULL == num_str)
		return (-1);
	*num = ft_atoi (num_str);
	free (num_str);
}



int	check_flags(t_flags *flags, const char *f, int *i)
{
	int ok;
	int num;

	ok = 1;
	while(f[*i] && !ft_isspecifier(f[*i]))
	{
		if('.' == f[*i])
			ok = -1;
		if (ft_isdigit(f[*i]) || -1 == ok)
		{
			if(1 == ok )
			{
				if (-1 == num_proccessing(&flags, f, &(*i), &num))
					return (-1); // Fail of malloc()
				if ('.' == f[*i])
					ok = -1;
				if(ft_isspecifier(f[*i]) || -1 == ok)
				{
					flags->width = num;
					if (ft_isspecifier(f[*i]))
					{
						flags->specifier = f[*i];
						return (1);
					}
				}
				else 
					return (-2); // Fail of specifier sequense
			}
			if(-1 == ok && ft_isdigit(f[*i + 1])) // if num is presicion (we found '.', then digit)
			{
				ok = 1;
				if (-1 == num_proccessing(&flags, f, &(*i), &num))
					return (-1); // Fail f malloc()
				if(ft_isspecifier(f[*i]))
				{
					flags->specifier = f[*i];
					flags->precision = num;
					return (1);
				}
				else 
					return (-2); // Fail of specifier sequence
			}
		}	
		i++;
	}
	if(ft_isspecifier(f[*i])) // if we found specifier  
		return (1); 
	return (0);
}