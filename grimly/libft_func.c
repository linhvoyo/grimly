/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 05:40:59 by lilam             #+#    #+#             */
/*   Updated: 2018/01/22 05:56:30 by lilam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

void	ft_putnbr(int n)
{
	char tmp;

	if (n == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2", 1);
		n = (n % -1000000000) * -1;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = (n * -1);
	}
	if (n / 10 > 0)
		ft_putnbr(n / 10);
	tmp = n % 10 + 48;
	write(1, &tmp, 1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	if (!(s1 && s2))
		return (NULL);
	str = (char*)malloc(sizeof(char) * (i + j + 1));
	if (!(str))
		return (NULL);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int		ft_atoi(const char *str)
{
	long i;
	long val;
	long sign;

	sign = 1;
	i = 0;
	val = 0;
	while (DL(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (DL(str[i]) || (str[i] >= 0 && str[i] <= 31))
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			val = val * 10 + str[i++] - '0';
		else
			break ;
	}
	return (val * sign);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char*)s + i);
		i++;
	}
	if (c == '\0')
		return ((char*)s + i);
	return (NULL);
}
