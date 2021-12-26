/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:24:25 by jchopped          #+#    #+#             */
/*   Updated: 2021/11/16 17:17:20 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(t_flags *flags, va_list fa)
{
	if (flags->minus)
	{
		ft_putchar_fd (va_arg(fa, int), 1);
		point_print (flags->width - 1, ' ');
	}
	else
	{
		point_print (flags->width - 1, ' ');
		ft_putchar_fd (va_arg(fa, int), 1);
	}
	if (flags->width)
		return (flags->width);
	else
		return (1);
}

static void	ft_put_prec_str(t_flags *flags, char *s, int number)
{
	if (!s)
		return ;
	if (flags->minus)
	{
		write(1, s, number);
		point_print(flags->width - number, ' ');
	}
	else
	{
		point_print(flags->width - number, ' ');
		write(1, s, number);
	}
}

int	print_s(t_flags *flags, va_list fa)
{
	char	*output;
	int		strlen;
	int		number_out_len;

	output = va_arg(fa, char *);
	if (NULL == output)
		output = "(null)";
	strlen = ft_strlen(output);
	if (flags->dot && !flags->precision)
		return (0);
	if (flags->precision && flags->precision < strlen)
		number_out_len = flags->precision;
	else
		number_out_len = strlen;
	ft_put_prec_str(flags, output, number_out_len);
	if (flags->width > number_out_len)
		return (flags->width);
	else
		return (number_out_len);
}
