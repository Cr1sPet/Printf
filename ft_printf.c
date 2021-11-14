/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:38:06 by jchopped          #+#    #+#             */
/*   Updated: 2021/11/14 16:57:40 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"


void default_init_flags(t_flags *flags)
{
	flags->specifier = 0;
	flags->null_filler = 0;
	flags->minus = 0;
	flags->width = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->precision = 0;
	flags->hash = 0;
	flags->dot = 0;
}

int format_processing (va_list fa, const char *f)
{
	int	i;
	int counter;
	t_flags	flags;

	i = 0;
	counter = 0;
	while(f[i])
	{
		if (f[i] != '%')
			counter += write (1 , &f[i], 1);
		else
		{
			if (!f[++i])
				return(counter);
			default_init_flags(&flags);
			if (1 == ft_parsing(&flags, f, &i))
				counter += ft_print_value(&flags, fa);
		}
		i++;
	}
	return (counter);	
}

int ft_printf(const char *f, ...)
{
	int		ret; 
	va_list	fa;

	if (f && !f[0])
		return(0);
	if (1 == ft_strlen(f) && f[0] == '%')
		return (-1);	
	va_start(fa, f);
	ret = format_processing(fa, f);
	va_end (fa);
	return (ret);
}