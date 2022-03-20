/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:17:03 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 00:43:18 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		*trd;
	pthread_mutex_t	*mutex;
	long long		*t_meal;
	long int		t_start;
	int				*first_meal;
	int				*n_t_eat;
}				t_philo;

typedef struct s_info
{
	int				n_ph;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				curr_ph;
	int				end_simul;
	int				barrier;
	int				index_barrier;
	pthread_t		mng;
	pthread_t		die_trd;
	pthread_mutex_t	p_mutex;
	pthread_mutex_t	d_mutex;
	t_philo			ph;
	long int		time;
	int				joined;
	int				all_eat;
	int				print_died;
}				t_info;

typedef long int	t_lint;

// main program function create threads and call routine
int		ft_one_fork(t_info *info, int trd_i);
void	*ft_routine(void *arg);
int		ft_create_threads(t_info *info, int n_ph);
void	ft_philo(int *args);
// those function check if the argument is valide and get its value
int		ft_is_digit(char *av);
int		ft_valide_args(int ac, char **av);
int		ft_atoi(char *av);
void	ft_convert_args_toint(int ac, char **av, int **args);
// initialize struct philo and free after done
void	ft_set_arr(int *n_t_eat, int n_ph, int n_times);
void	ft_sub_initialize(t_info *info, int *args);
int		ft_initialize(t_info *info, int *args);
void	ft_free(t_info info);
// switch philo state
t_lint	ft_get_time(t_info *info);
int		ft_thinking(t_info *info, int trd_i);
int		ft_end_lock(t_info *info, int trd_i);
int		ft_take_forks(t_info *info, int trd_i);
int		ft_eat_and_sleep(t_info *info, int trd_i);
// manage usleep functions
t_lint	ft_get_milisec(struct timeval tv);
int		ft_deep_sleep(t_info *info, long int timestamp);
int		ft_deep_eat(t_info *info, long int timestamp, int trd_i);
void	ft_is_all_eat(t_info *info);
int		ft_print_act(t_info *info, long int time, int trd, char *act);
// joind thread and create, destroy mutex 
void	ft_join_threads(t_info *info, int n_ph);
void	ft_join_died_thread(t_info *info);
int		ft_initialize_mutex(t_info *info, int n_ph);
void	ft_unlock(t_info *info);
void	ft_destroy_mutex(t_info *info, int n_ph);
// manage died an check is all eat n time (ft_ead_simul)
int		ft_end_simul(t_info *info, int trd_i);
t_lint	ft_spend(t_info *info, int trd);
void	ft_print_died(t_info *info, long long time, int i);
void	*ft_died(void *arg);
int		ft_manage_died(t_info *info);

#endif
