# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 19:04:31 by anmedyns          #+#    #+#              #
#    Updated: 2024/10/01 14:05:48 by anmedyns         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher

SRC		= main.c init_all.c check_err_atoi.c

OBJ		=	$(SRC:.c=.o)

CC		=	gcc -g

RM		=	rm -f

FLAGS	=	-Wall -Wextra -Werror

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\033[32mCompiled OK!\033[0m"
all:		$(NAME)

clean:
			${RM} $(OBJ)
	@echo "\033[33mclean OK!\033[0m"
fclean: 	clean
			${RM} $(NAME) $(NAME_BONUS) ${OBJ}

re:			fclean all

git:
	git add .
	git commit -m "update"
	git push

.PHONY:		all clean fclean re
