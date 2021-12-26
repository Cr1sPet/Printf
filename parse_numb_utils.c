/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numb_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:24:09 by jchopped          #+#    #+#             */
/*   Updated: 2021/11/15 15:21:53 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_output	init_output(char *str)
{
	t_output	output;

	output.val = str;
	output.neg = ('-' == str[0]);
	output.len = ft_strlen(str) - output.neg;
	return (output);
}

static int	find_length(unsigned long long int n, unsigned long long base)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

static char	*ft_strrev(char *str, int is_neg)

{
	int		i;
	int		k;
	int		j;
	char	t;

	j = ft_strlen(str) - 1;
	k = j / 2;
	i = is_neg;
	while (i <= k)
	{
		t = str[j];
		str[j] = str[i];
		str[i] = t;
		i++;
		j--;
	}
	return (str);
}

char	*convert_base(unsigned long long int out, int base, char s, int shift)
{
	int		i;
	int		len;
	char	*num_str;

	i = 0;
	len = (find_length(out, base));
	num_str = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == num_str)
		return (NULL);
	if ('X' == s)
		shift = 'A';
	while (i < len)
	{
		if (out % base > 9)
			num_str[i++] = (out % base) - 10 + shift;
		else
			num_str[i++] = (out % base) + '0';
		out /= base;
	}
	num_str[i] = 0;
	return (ft_strrev(num_str, 0));
}

char	*ft_utoa(unsigned int n)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = (1 + find_length(n, 10)) * sizeof(char);
	res = (char *) malloc (len);
	if (NULL == res)
		return (NULL);
	while (i < len - 1)
	{
		res[i] = (n % 10) + 48;
		n /= 10;
		i++;
	}
	res[i] = 0;
	return (ft_strrev(res, 0));
}
