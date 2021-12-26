/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:38:06 by jchopped          #+#    #+#             */
/*   Updated: 2021/11/16 16:49:52 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	default_init_flags(t_flags *flags)
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

static int	validated_flags(t_flags *flags)
{
	if (flags->plus
		&& ('i' != flags->specifier && 'd' != flags->specifier))
		return (0);
	if (flags->space && ('s' != flags->specifier
			&& 'i' != flags->specifier && 'd' != flags->specifier))
		return (0);
	if (flags->hash && ('x' != flags->specifier && 'X' != flags->specifier))
		return (0);
	if (flags->dot && ('p' == flags->specifier))
		return (0);
	if (flags->null_filler && 'p' == flags->specifier)
		return (0);
	return (1);
}

static int	parse_print_val(t_flags *flags, va_list fa)
{
	int			ret_value;
	char		*output_str;

	ret_value = 0;
	output_str = NULL;
	if ('c' == flags->specifier)
		ret_value = print_c(flags, fa);
	else if ('s' == flags->specifier)
		ret_value = print_s(flags, fa);
	else if ('%' == flags->specifier)
	{
		ft_putchar_fd ('%', 1);
		ret_value = 1;
	}
	else
		ret_value = parse_print_numb(flags, fa, output_str, ret_value);
	return (ret_value);
}

int	ft_printf(const char *f, ...)
{
	int		i;
	int		counter;
	t_flags	flags;
	va_list	fa;

	va_start(fa, f);
	i = 0;
	counter = 0;
	while (f[i])
	{
		if (f[i] != '%')
			counter += write(1, &f[i], 1);
		else
		{
			if (!f[++i])
				return (counter);
			default_init_flags(&flags);
			if (parsing(&flags, f, &i) && validated_flags(&flags))
				counter += parse_print_val(&flags, fa);
		}
		i++;
	}
	va_end (fa);
	return (counter);
}
