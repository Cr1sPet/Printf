/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numb_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:23:32 by jchopped          #+#    #+#             */
/*   Updated: 2021/11/15 15:22:26 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putstr_check_case(t_flags *flags, t_output *output)
{
	int	ok;

	ok = 0;
	if (!output->val)
		return (ok);
	if (flags->dot && !flags->precision && !('p' == flags->specifier))
	{
		if (!ft_strncmp(output->val, "0", output->len))
		{
			ok = 1;
			if (flags->null_filler)
				write(1, &" ", 1);
		}
	}
	if (!ok)
		write(1, output->val, output->len);
	return (ok);
}

int	check_plus_minus(t_flags *flags, t_output *output)
{
	int	ok;

	ok = 0;
	if (output->neg)
	{
		output->val++;
		ft_putchar_fd('-', 1);
	}
	else if (flags->plus)
	{
		ok = 1;
		ft_putchar_fd('+', 1);
	}
	else if (flags->space)
	{
		ok = 1;
		ft_putchar_fd(' ', 1);
	}
	return (ok);
}

int	check_hash_pointer(t_flags *flags)
{
	int	ok;

	ok = 0;
	if (flags->hash || 'p' == flags->specifier)
	{
		ok = 2;
		if ('X' == flags->specifier)
			ft_putstr_fd("0X", 1);
		else
			ft_putstr_fd("0x", 1);
	}
	return (ok);
}

void	check_neg(t_output *output)
{
	if (output->neg)
	{
		output->val++;
		ft_putchar_fd('-', 1);
	}
}

void	point_print(int len, char out)
{
	int	i;

	i = 0;
	while (i < len)
	{
		write(1, &out, 1);
		i++;
	}
}
