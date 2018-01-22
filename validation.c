/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 02:13:46 by linh              #+#    #+#             */
/*   Updated: 2018/01/22 05:19:26 by linh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void    ft_putnbr(int n)
{
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
		char tmp;
		
		tmp = n % 10 + 48;
		write(1, &tmp, 1);
}

char    *ft_strjoin(char *s1, char *s2)
{
		char    *str;
		int        i;

		if (!(s1 && s2))
				return (NULL);
		i = 0;
		str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (!(str))
				return (NULL);
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
int    ft_atoi(const char *str)
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

char    *ft_strchr(const char *s, int c)
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

char *locate_params(char *str)
{
		int i;
		char *new;
		i = 0;
		while (str[i])
		{
				if (str[i] == '\n')
						break;
				i++;
		}
		new = (char*)malloc(sizeof(char) * (i + 1));
		new[i] = '\0';
		i = i - 1;
		while (i >= 0)
		{
				new[i] = str[i];
				i--;
		};
		return (new);
}

int length_int(int num)
{
	int i;

	i = 0;

	while (num)
	{
		num = num/10;
		i++;
	}
	return (i);
}

void init_exits_entrance()
{
	int i;
	i = 0;

	g_params.exit_coor = malloc(sizeof(int*) * 1000);
	while(i < 1000)
		g_params.exit_coor[i++] = malloc(sizeof(int) * 2);	
	g_params.ent_coor = malloc(sizeof(int) * 2);
}

int validate_str(char *str, int n)
{
	int i;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!(str[i] == g_params.full || str[i] == g_params.empty ||
					str[i] == g_params.path || str[i] == g_params.empty ||
					str[i] == g_params.path || str[i] == g_params.exit ||
					str[i] == g_params.ent))
			return (0);
		if (str[i] == g_params.ent)
		{
			g_params.n_ent++;
			g_params.ent_coor[0] = n;
			g_params.ent_coor[1] = i;
			if (g_params.n_ent > 1)
				return (0);
		}
		if (str[i] == g_params.exit)
		{
			g_params.exit_coor[g_params.n_exit][0] = n;
			g_params.exit_coor[g_params.n_exit][1] = i;
			g_params.n_exit++;
		}
		i++;
	}
	return (1);	
}

int	validate_file(char *file)
{
	g_board = (char **)malloc(sizeof(char *) * g_params.m);
	init_exits_entrance();
	int i;
	int j;
	int n;

	n = 0;
	i = 0;
	while (file[i] && (i < g_params.m * g_params.n + g_params.m))
	{
		
		if (i % (g_params.n + 1)  == 0 )
		{
			if (file[i + g_params.n] != '\n')
				return (0);	
			char *str = (char *)malloc(sizeof(str) * (g_params.n + 1));
			j = -1;
			while (++j < g_params.n)
				str[j] = file[i + j];
			str[j] = '\0';
			if (validate_str(str, n))
				g_board[n++] = str;
			else
				return (0);
		}
		i++;
	}
	while (file[i])
		if (file[i++] != '\n')
			return (0);
	if (g_params.n_exit < 1)
		return (0);
	return (1);	
}

int find_params(char *file)
{
	int i = 0;
	int j = 0;	
	while (file[i] != '\n')
		i++;
	i--;
   	g_params.exit = file[i--];
	g_params.ent = file[i--];
	g_params.path = file[i--];
	g_params.empty = file[i--];
	g_params.full = file[i--];
	int tmp = ft_atoi(file);
	while (j <= i)
	{
		if (file[j] == 'x')
		{
			if (length_int(tmp) == j)
				g_params.m = tmp;
			else
				return (0);
			tmp = ft_atoi(file + j + 1);
			break;
		}
		j++;
	}
	if (length_int(tmp) == i - j)
		g_params.n = tmp;
	else
		return (0);	
	return (1);
}

int read_file(int fd)
{
	char buf[BUFF_SIZE + 1];
	char *file;
	char *tmp;
	int ret;

	file = malloc(sizeof(char) + 1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (0);
		buf[ret] = '\0';
		tmp = file;
		file = ft_strjoin(tmp, buf);
		free(tmp);
	}
	
	if (!find_params(file))
		return (0);
	if (!validate_file(ft_strchr(file, '\n') + 1))
		return (0);
	free(file);	
	return(1);
}
