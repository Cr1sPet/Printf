/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:38:06 by jchopped          #+#    #+#             */
/*   Updated: 2021/11/02 15:02:19 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft/libft.h"
// size_t	ft_strlen(const char *str)
// {
// 	size_t	l;

// 	l = 0;
// 	while (str[l] != '\0')
// 	{
// 		l++;
// 	}
// 	return (l);
// }


void default_init_flags(t_flags *flags)
{
	flags->null_filler = 0;
	flags->minus = 0;
	flags->width = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->precision = 0;
	flags->hash= 0;
}

int format_processing (t_flags flags, va_list fa, const char *f)
{
	int	i;
	int ok;
	int counter;

	i = 0;
	counter = 0;
	while(f[i])
	{
		if (f[i] != '%')
			counter += write (1 , &f[i++], 1);
		else
		{
			if (!f[++i])
				return(counter);
			
			if(check_flags(&flags, f, &i))
				counter += ft_print_value(&flags, &fa);
		}
	}
	return (counter);	
}

int ft_printf(const char *f, ...)
{
	int		ret; 
	va_list	fa;
	t_flags	flags;

	default_init_flags(&flags);
	if (f && !f[0])
		return(0);
	if(1 == ft_strlen(f) && f[0] == '%')
		return (-1);	
	va_start(fa, f);
	ret = format_processing(flags, fa, f);
	va_end (fa);
	return (ret);
}