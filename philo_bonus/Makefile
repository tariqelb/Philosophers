# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 18:49:50 by tel-bouh          #+#    #+#              #
#    Updated: 2022/03/18 05:17:35 by tel-bouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS = philo_bonus

SRCS_BONUS = ./ft_check_args_get_value_bonus.c ./ft_manage_sleep_bonus.c ./philo_bonus.c \
			 ./ft_initialize_struct_bonus.c ./ft_philo_status_bonus.c ./ft_manage_died_bonus.c

OBJS_BONUS = ./ft_check_args_get_value_bonus.o ./ft_manage_sleep_bonus.o ./philo_bonus.o \
			 ./ft_initialize_struct_bonus.o ./ft_philo_status_bonus.o ./ft_manage_died_bonus.o

FLAGS = -Wall -Wextra -Werror 

F_TRD = -pthread

CC = gcc

all : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJS_BONUS)
	$(CC) $(FLAGS) $(F_TRD) $(SRCS_BONUS) -o $(NAME_BONUS)

$(OBJS_BONUS) : $(SRCS_BONUS)
	$(CC) -c $(SRCS_BONUS)

clean :
	rm -rf $(OBJS_BONUS)

fclean : clean
	rm -rf $(NAME_BONUS)

re : fclean all
