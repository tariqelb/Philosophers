# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 13:44:58 by tel-bouh          #+#    #+#              #
#    Updated: 2022/03/18 05:18:01 by tel-bouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./ft_check_args_get_value.c ./ft_initialize_struct_philo.c ./ft_manage_died.c \
	   ./ft_join_thread_init_destroy_mutex.c ./philo.c \
	   ./ft_manage_sleep.c ./ft_philo_stats.c

OBJS = ./ft_check_args_get_value.o ./ft_initialize_struct_philo.o ./ft_manage_died.o \
	   ./ft_join_thread_init_destroy_mutex.o ./philo.o \
	   ./ft_manage_sleep.o ./ft_philo_stats.o

FLAGS = -Wall -Wextra -Werror 

F_TRD = -pthread

CC = gcc

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(F_TRD) $(SRCS) -o $(NAME)

$(OBJS) : $(SRCS)
	$(CC) -c $(SRCS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
