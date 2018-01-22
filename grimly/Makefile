# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lilam <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/22 07:11:57 by lilam             #+#    #+#              #
#    Updated: 2018/01/22 07:15:42 by lilam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = grimly
FILES = grimly.c validation.c libft_func.c main.c build_queue.c

all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror $(FILES) -o $(NAME) 
	@gcc -c -Wall -Wextra -Werror $(FILES)

clean:
	@rm -rf *.o 

fclean: clean
	@rm -rf $(NAME)

re: fclean all
