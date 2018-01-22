/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:23:42 by linh              #+#    #+#             */
/*   Updated: 2018/01/22 07:24:14 by lilam            ###   ########.fr       */
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

typedef struct		s_node
{
	int				x;
	int				y;
	int				dist;
	struct s_node	*next;
	struct s_node	*parent;
}					t_node;

typedef struct		s_queue
{
	t_node			*head;
	t_node			*tail;
	int				size;
	int				limit;
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
	int				n_ent;
	int				**exit_coor;
	int				*ent_coor;
}					t_params;

extern				t_params g_params;
extern				char **g_board;

void				ft_putnbr(int n);
char				*ft_strjoin(char *s1, char *s2);
void				ft_putstr(char *str);
int					ft_atoi(const char *str);
char				*ft_strchr(const char *s, int c);

int					length_int(int num);
t_node				*create_node(int x, int y, int dist);

void				init_struct(void);
int					validate_str(char *str, int n);
int					validate_file(char *file);
int					find_params(char *file);
int					read_file(int fd);

t_queue				*construct_queue(int limit);
void				destroy_queue(t_queue *queue);
int					push(t_queue *queue, t_node *node);
t_node				*pop(t_queue *queue);
int					is_queue_empty(t_queue *queue);

int					is_pos_valid(int **visited, int row, int col);
int					**gen_visited_map();
int					check_exits(int a, int b);
int					plot_map(t_node *node, int dist);
int					bfs(void);

#endif
