/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:23:42 by linh              #+#    #+#             */
/*   Updated: 2018/01/22 05:19:54 by linh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRIMLY_H
# define GRIMLY_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# define INT_MAX 2147483647
# define DL(x) (x=='\t'||x=='\n'||x =='\v'||x == '\r'||x=='\f'||x==' ')
# define BUFF_SIZE 1000
# define MOVE int row[] = {-1, 0, 0, 1}; int col[] = {0, -1, 1, 0};

# include <stdio.h>


typedef struct		s_node
{
	int				x;
	int				y;
	int				dist;
	struct s_node	*next;
	struct s_node 	*parent;
}					t_node;

typedef struct		s_queue
{
	t_node	*head;
	t_node	*tail;
	int		size;
	int		limit;
}					t_queue;

typedef struct		s_params
{
	int				m;
	int				n;
	char			full;
	char			empty;
	char			path;
	char			exit;
	int				n_exit;
	char			ent;
	int 			n_ent;
	int				**exit_coor;
	int				*ent_coor;
}					t_params;

extern            t_params g_params;
extern				char **g_board;

int bfs();
int is_queue_empty(t_queue *queue);
t_node *pop(t_queue *queue);
int  read_file(int fd);

int **array_join(int *arr1, int arr1_len, int *arr2, int arr2_len);
void    print_array(int *arr, int len);
int **arr_expand(int **arr, int num_pointer, int *elem, int elem_len);
int **arr_delete_front(int **arr, int num_pointer);
void print_map(int **map, int m, int n);
int **append_arr(int **arr, int n1, int **arr2, int n2);

void ft_putstr(char *str);
void ft_putnbr(int n);
#endif
