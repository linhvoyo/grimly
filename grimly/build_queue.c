/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 06:25:33 by lilam             #+#    #+#             */
/*   Updated: 2018/01/22 06:32:02 by lilam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

t_queue		*construct_queue(int limit)
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

void		destroy_queue(t_queue *queue)
{
	t_node *node;

	while (!is_queue_empty(queue))
	{
		node = pop(queue);
		free(node);
	}
	free(queue);
}

int			push(t_queue *queue, t_node *node)
{
	if ((queue == NULL) || (node == NULL))
		return (0);
	if (queue->size >= queue->limit)
		return (0);
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

t_node		*pop(t_queue *queue)
{
	t_node *tmp;

	if (is_queue_empty(queue))
		return (NULL);
	tmp = queue->head;
	queue->head = (queue->head)->next;
	queue->size--;
	return (tmp);
}

int			is_queue_empty(t_queue *queue)
{
	if (queue == NULL)
		return (0);
	if (queue->size == 0)
		return (1);
	else
		return (0);
}
