/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 05:57:55 by lilam             #+#    #+#             */
/*   Updated: 2018/01/22 07:08:46 by lilam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

int			length_int(int num)
{
	int i;

	i = 0;
	while (num)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

t_node		*create_node(int x, int y, int dist)
{
	t_node *tmp;

	tmp = malloc(sizeof(t_node));
	if (tmp)
	{
		tmp->x = x;
		tmp->y = y;
		tmp->dist = dist;
		tmp->next = NULL;
		tmp->parent = NULL;
	}
	return (tmp);
}

char		**g_board;
t_params	g_params = {0, 0, '\0', '\0', '\0', '\0', 0, '\0', 0, NULL, NULL};

int			main(int argc, char **argv)
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2 || !fd)
		return (-1);
	if (!read_file(fd) || !bfs())
	{
		ft_putstr("MAP ERROR\n");
		return (-1);
	}
	close(fd);
	return (0);
}
