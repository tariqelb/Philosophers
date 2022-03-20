/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bomus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:09:50 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 14:43:53 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_philo_bonus(t_info *info)
{
	pthread_t	track_died;	

	track_died = NULL;
	if (ft_create_track_thread(track_died, info) != 0)
	{
		sem_post(info->died);
		while (1)
			;
	}
	if (info->ph.i % 2)
		usleep(30);
	while (1)
	{
		if (info->n_ph == 1)
		{
			ft_one_fork(info);
			return ;
		}
		if (ft_take_forks(info) == 1)
		{
			if (ft_eat_and_sleep(info) == 0)
				return ;
		}
		info->ph.first_meal = 0;
	}
}

t_info	ft_create_philo(t_info info)
{
	info.t_start = ft_get_milisec();
	while (info.m_id && ++info.i < info.n_ph)
	{
		info.prc[info.i] = fork();
		if (info.prc[info.i] == 0)
		{
			info.m_id = 0;
			info.ph.i = info.i;
			ft_philo_bonus(&info);
			return (info);
		}
		else if (info.prc[info.i] == -1)
		{
			ft_kill_philo(&info, info.i);
			free(info.prc);
			ft_destroy_sem(&info);
			exit(1);
		}
	}
	return (info);
}

int	main(int ac, char **av)
{
	pthread_t	kill_philo;
	t_info		info;
	int			i;
	int			status;

	kill_philo = NULL;
	status = -1;
	i = -1;
	if (ft_basic_operation(ac, av, &info) != 0)
		return (1);
	info = ft_create_philo(info);
	if (ft_create_kill_thread(kill_philo, &info) != 0)
		return (1);
	if (info.m_id == 1)
	{
		while (++i < info.n_ph)
		{
			waitpid(info.prc[i], &status, 0);
		}
		ft_destroy_sem(&info);
		free(info.prc);
	}
	return (0);
}
