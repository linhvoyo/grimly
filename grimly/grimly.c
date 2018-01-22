/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:22:01 by linh              #+#    #+#             */
/*   Updated: 2018/01/22 07:05:49 by lilam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"
#define INIT_V int **visited=gen_visited_map(); int min_dist = INT_MAX;
#define INIT_Q t_queue *queue = construct_queue(66000); int i; t_node *node;
#define INIT INIT_V; INIT_Q; MOVE; t_node *tmp;

int		is_pos_valid(int **visited, int row, int col)
{
	if (row >= 0 && row < g_params.m && col >= 0 && col < g_params.n &&
		(g_board[row][col] == g_params.empty ||
		g_board[row][col] == g_params.exit) && visited[row][col] != 1)
		return (1);
	return (0);
}

int		**gen_visited_map(void)
{
	int **visited;
	int i;
	int j;

	visited = (int **)malloc(sizeof(int*) * g_params.m);
	i = 0;
	while (i < g_params.n)
		visited[i++] = (int *)malloc(sizeof(int) * g_params.n);
	i = 0;
	while (i < g_params.m)
	{
		j = 0;
		while (j < g_params.n)
			visited[i][j++] = 0;
		i++;
	}
	return (visited);
}

int		check_exits(int a, int b)
{
	int i;

	i = 0;
	while (i < g_params.n_exit)
	{
		if (a == g_params.exit_coor[i][0] && b == g_params.exit_coor[i][1])
			return (1);
		i++;
	}
	return (0);
}

int		plot_map(t_node *node, int dist)
{
	int i;

	i = 0;
	node = node->parent;
	while (node->parent)
	{
		g_board[node->x][node->y] = g_params.path;
		node = node->parent;
	}
	while (i < g_params.m)
	{
		ft_putstr(g_board[i++]);
		ft_putstr("\n");
	}
	ft_putstr("RESULT IN ");
	ft_putnbr(dist);
	ft_putstr(" STEPS!\n");
	return (1);
}

int		bfs(void)
{
	INIT;
	visited[g_params.ent_coor[0]][g_params.ent_coor[1]] = 1;
	push(queue, create_node(g_params.ent_coor[0], g_params.ent_coor[1], 0));
	while (!is_queue_empty(queue) && (node = queue->head))
	{
		pop(queue);
		if (check_exits(node->x, node->y) && (visited[node->x][node->y] = 1))
		{
			min_dist = node->dist;
			break ;
		}
		i = -1;
		while (++i < 4)
		{
			if (is_pos_valid(visited, node->x + row[i], node->y + col[i]))
			{
				visited[node->x + row[i]][node->y + col[i]] = 1;
				tmp = create_node(node->x + row[i], node->y + col[i],
						node->dist + 1);
				tmp->parent = node;
				push(queue, tmp);
			}
		}
	}
	return ((min_dist != INT_MAX && (plot_map(node, min_dist - 1)) ? 1 : 0));
}
