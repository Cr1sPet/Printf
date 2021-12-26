/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:23:40 by jchopped          #+#    #+#             */
/*   Updated: 2021/11/16 12:17:03 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_flags
{
	int		hash;
	int		plus;
	int		space;
	int		minus;
	int		null_filler;
	int		width;
	int		precision;
	int		dot;
	char	specifier;
}	t_flags;

typedef struct s_output
{
	char	*val;
	int		len;
	int		neg;
}	t_output;

int			ft_printf(const char *f, ...);
int			print_c(t_flags *flags, va_list fa);
int			print_s(t_flags *flags, va_list fa);
int			parsing(t_flags *flags, const char *f, int *i);
int			parse_print_numb(t_flags *flags, va_list fa,
				char *output_str, int len);
char		*ft_utoa(unsigned int n);
char		*convert_base(unsigned long long int out, int base,
				char s, int len);
void		check_neg(t_output *output);
int			check_plus_minus(t_flags *flags, t_output *output);
void		point_print(int len, char out);
int			check_hash_pointer(t_flags *flags);
int			putstr_check_case(t_flags *flags, t_output *output);
t_output	init_output(char *str);
#endif