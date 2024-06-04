/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:14:31 by lumarque          #+#    #+#             */
/*   Updated: 2023/11/20 15:40:07 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
int		ft_putnbase(unsigned long nbr, const char *base, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_print_char(char c, int fd);
int		ft_print_percent(void);
int		ft_print_str(char *s, int fd);
int		ft_printnbr_fd(int n, int fd);
int		ft_nbrlen(long nbr, int base);
size_t	print_strlen(const char *str);

#endif