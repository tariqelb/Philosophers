/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bomus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:15:16 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 15:50:48 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/wait.h>

typedef struct s_philo
{
	long long	id;
	int			i;
	long int	t_meal;
	int			first_meal;
	int			n_t_eat;
}				t_philo;

typedef struct s_info
{
	int			n_ph;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			end_simul;
	long int	t_start;
	sem_t		*forks;
	sem_t		*died;
	sem_t		*print;
	sem_t		*died_print;
	sem_t		*stop_print;
	pid_t		m_id;
	long long	*prc;
	int			i;
	t_philo		ph;
}				t_info;

typedef long long	t_ll;

int		ft_is_digit(char *av);
int		ft_valide_args(int ac, char **av);
int		ft_atoi(char *av);

t_info	ft_create_philo(t_info info);
int		ft_basic_operation(int ac, char **av, t_info *info);
void	ft_philo_bonus(t_info *info);

void	ft_kill_philo(t_info *info, int i);
int		ft_destroy_sem(t_info *info);
int		ft_initialize_sem(t_info *info);
int		ft_initialize_struct(t_info *info, int ac, char **av);

void	ft_print_action(t_info *info, t_ll time, char *str);
void	ft_one_fork(t_info *info);
int		ft_tinking(t_info *info);
int		ft_take_forks(t_info *info);
int		ft_eat_and_sleep(t_info *info);

t_ll	ft_get_time(t_info *info);
t_ll	ft_get_milisec(void);
int		ft_deep_eat(t_info *info, long long time);
int		ft_deep_sleep(t_info *info, long long time);
int		ft_am_full(t_info *info);

void	*ft_track_died(void *arg);
int		ft_create_track_thread(pthread_t track_died, t_info *info);
void	*ft_kill(void	*args);
int		ft_create_kill_thread(pthread_t kill_philo, t_info *info);
#endif
