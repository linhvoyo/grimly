/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 02:13:46 by linh              #+#    #+#             */
/*   Updated: 2018/01/22 06:23:44 by lilam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"
#define INT_I int i = 0;
#define VARS int i = -1; int n = 0; int j; char *str;
#define INIT int i = 0; int j = -1; int tmp = ft_atoi(file);

void	init_struct(void)
{
	int i;

	i = 0;
	g_params.exit_coor = malloc(sizeof(int*) * 1000);
	while (i < 1000)
		g_params.exit_coor[i++] = malloc(sizeof(int) * 2);
	g_params.ent_coor = malloc(sizeof(int) * 2);
	g_board = (char **)malloc(sizeof(char *) * g_params.m);
}

int		validate_str(char *str, int n)
{
	INT_I;
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

int		validate_file(char *file)
{
	VARS;
	init_struct();
	while (file[++i] && (i < g_params.m * g_params.n + g_params.m))
	{
		if (i % (g_params.n + 1) == 0)
		{
			if (file[i + g_params.n] != '\n')
				return (0);
			str = (char *)malloc(sizeof(str) * (g_params.n + 1));
			j = -1;
			while (++j < g_params.n)
				str[j] = file[i + j];
			str[j] = '\0';
			if (validate_str(str, n))
				g_board[n++] = str;
			else
				return (0);
		}
	}
	while (file[i])
		if (file[i++] != '\n')
			return (0);
	if (g_params.n_exit < 1)
		return (0);
	return (1);
}

int		find_params(char *file)
{
	INIT;
	while (file[i] != '\n')
		i++;
	i--;
	g_params.exit = file[i--];
	g_params.ent = file[i--];
	g_params.path = file[i--];
	g_params.empty = file[i--];
	g_params.full = file[i--];
	while (++j <= i)
	{
		if (file[j] == 'x')
		{
			if (length_int(tmp) == j)
				g_params.m = tmp;
			else
				return (0);
			tmp = ft_atoi(file + j + 1);
			break ;
		}
	}
	if (!(length_int(tmp) == i - j && (g_params.n = tmp)))
		return (0);
	return (1);
}

int		read_file(int fd)
{
	char	buf[BUFF_SIZE + 1];
	char	*file;
	char	*tmp;
	int		ret;

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
	return (1);
}
