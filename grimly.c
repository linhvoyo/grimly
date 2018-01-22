/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:22:01 by linh              #+#    #+#             */
/*   Updated: 2018/01/22 05:21:26 by linh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

t_node *create_node(int x, int y, int dist)
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


void destroy_queue(t_queue *queue)
{
	t_node *node;
	while(!is_queue_empty(queue))
	{
		node = pop(queue);
		free(node);
	}
	free(queue);
}


t_queue *construct_queue(int limit)
{
	t_queue *tmp;

	tmp = (t_queue*)malloc(sizeof(t_queue));
	if (!tmp)
		return (NULL);
	if (limit <= 0)
		limit = 65535;
	tmp->limit = limit;
	tmp->size = 0;
	tmp->head = NULL;
	tmp->tail = NULL;

	return (tmp);
}

int push(t_queue *queue, t_node *node)
{
	if ((queue == NULL) || (node == NULL))
		return 0;
	if (queue->size >= queue->limit)
		return 0;
	node->next = NULL;
	if (queue->size == 0)
	{
		queue->head = node;
		queue->tail = node;
	}
	else
	{
		queue->tail->next = node;
		queue->tail = node;
	}
	queue->size++;
	return (1);
}

int is_queue_empty(t_queue *queue)
{
	if (queue == NULL)
		return (0);
	if (queue->size == 0)
		return (1);
	else
		return (0);
}

t_node *pop(t_queue *queue)
{
	t_node *tmp;
	if (is_queue_empty(queue))
		return (NULL);
	tmp = queue->head;
	queue->head = (queue->head)->next;
	queue->size--;
	return (tmp);

}

int		is_pos_valid(int **visited, int row, int col)
{
		if (row >= 0 && row < g_params.m  && col >= 0 && col < g_params.n
						&& (g_board[row][col] == g_params.empty ||
								g_board[row][col] == g_params.exit) 
						&& visited[row][col] != 1)
			return (1);

		return (0);

}

int **gen_visited_map()
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

int check_exits(int a, int b)
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

void plot_map(t_node *node, int dist)
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
}

int bfs()
{
	int **visited;
	t_node *node;
	t_queue *queue;
	int i;
	int min_dist;

	visited = gen_visited_map();	
	visited[g_params.ent_coor[0]][g_params.ent_coor[1]] = 1;;
	queue = construct_queue(30000);
	push(queue, create_node(g_params.ent_coor[0], g_params.ent_coor[1], 0));
	MOVE;
	min_dist = INT_MAX;
	while (!is_queue_empty(queue))
	{
		node = queue->head;
		pop(queue);
		if (check_exits(node->x, node->y))
		{
			visited[node->x][node->y] = 1;
			min_dist = node->dist;
			break;
		}
		i = 0;
		while (i < 4)
		{
			if (is_pos_valid(visited, node->x + row[i], node->y + col[i]))
			{
				visited[node->x + row[i]][node->y + col[i]] = 1;
				t_node *tmp = create_node(node->x + row[i], node->y + col[i],
								node->dist + 1);
				tmp->parent = node;
				push(queue, tmp);
			}
			i++;
		}
	}
	if (min_dist != INT_MAX)
	{
		plot_map(node, min_dist - 1);
		return (1);
	}
	return (0);
}

char **g_board;
t_params g_params = {0, 0, '\0', '\0', '\0', '\0', 0,'\0', 0, NULL, NULL };

int main(int argc, char **argv)
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
