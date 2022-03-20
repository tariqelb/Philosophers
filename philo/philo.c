/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:46:47 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 13:35:46 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_one_fork(t_info *info, int trd_i)
{
	long int		time;

	time = ft_get_time(info);
	printf("%ld %d %s", time, trd_i + 1, "has token a fork\n");
	pthread_mutex_lock(&info->ph.mutex[trd_i]);
	while (info->end_simul == 0)
		usleep(1000);
	return (0);
}

void	*ft_routine(void *arg)
{
	struct timeval	tv;
	t_info			*info;
	int				trd_i;

	info = (t_info *) arg;
	trd_i = info->curr_ph;
	info->index_barrier = 1;
	info->barrier--;
	while (info->barrier != 0)
		usleep(5);
	gettimeofday(&tv, NULL);
	if (info->ph.t_start == 0)
		info->ph.t_start = ft_get_milisec(tv);
	info->ph.t_meal[trd_i] = ft_get_time(info);
	if (trd_i % 2 == 0)
		usleep(10000);
	while (info->end_simul == 0)
	{
		if (ft_take_forks(info, trd_i) == 1)
		{
			if (ft_eat_and_sleep(info, trd_i) == 0)
				return (NULL);
		}
	}
	return (NULL);
}

int	ft_create_threads(t_info *info, int n_ph)
{
	int	i;

	i = 0;
	while (i < n_ph)
	{
		info->index_barrier = 0;
		info->curr_ph = i;
		if (pthread_create(&(info->ph.trd[i]), NULL, ft_routine, info))
		{
			printf("Fail in thread creation\n");
			return (1);
		}
		while (info->index_barrier == 0)
			usleep(5);
		i++;
	}
	return (0);
}

void	ft_philo(int *args)
{
	t_info	info;
	int		i;

	i = 0;
	if (ft_initialize(&info, args) != 0)
		return ;
	ft_set_arr(info.ph.n_t_eat, info.n_ph, args[4]);
	ft_set_arr(info.ph.first_meal, info.n_ph, 1);
	if (ft_manage_died(&info) != 0)
		return ;
	if (ft_initialize_mutex(&info, info.n_ph) == 1)
		return ;
	if (ft_create_threads(&info, info.n_ph) == 1)
		return ;
	ft_join_threads(&info, info.n_ph);
	ft_join_died_thread(&info);
	ft_destroy_mutex(&info, info.n_ph);
	ft_free(info);
}

int	main(int ac, char **av)
{
	int	*args;

	args = NULL;
	if (ac != 5 && ac != 6)
		return (printf("Invalid number of argument\n"));
	if (ft_valide_args(ac, av) == 0)
		return (printf("Invalid argument\n"));
	args = (int *) malloc(sizeof(int) * 5);
	if (args == NULL)
		return (printf("Memory allocation fail\n"));
	ft_convert_args_toint(ac, av, &args);
	if (args[0] == 0)
		return (printf("Invalid number of philosopers\n"));
	if (args[4] == 0)
		return (1);
	ft_philo(args);
	free(args);
	return (0);
}
