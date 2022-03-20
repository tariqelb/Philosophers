/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_died_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 04:00:55 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 15:54:53 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_track_died(void *arg)
{
	t_info		*info;
	long long	time;

	info = (t_info *) arg;
	while (1)
	{
		time = ft_get_time(info);
		if (time >= info->ph.t_meal + info->t_die)
		{
			sem_wait(info->stop_print);
			sem_wait(info->died_print);
			printf("%lld %d %s\n", time, info->ph.i + 1, "died");
			sem_post(info->died);
			break ;
		}
		else
			usleep(100);
	}
	return (0);
}

int	ft_create_track_thread(pthread_t track_died, t_info *info)
{
	if (pthread_create(&track_died, NULL, ft_track_died, info) != 0)
	{
		return (printf("Fail to create thread\n"));
	}
	if (pthread_detach(track_died) != 0)
	{
		return (printf("Fail to detach thread\n"));
	}
	return (0);
}

void	*ft_kill(void	*args)
{
	t_info	*info;
	int		i;

	i = 0;
	info = (t_info *) args;
	usleep(100);
	sem_wait(info->died);
	while (i < info->n_ph)
	{
		kill(info->prc[i], SIGKILL);
		i++;
	}
	return (0);
}

int	ft_create_kill_thread(pthread_t kill_philo, t_info *info)
{
	if (pthread_create(&kill_philo, NULL, ft_kill, info) != 0)
	{
		ft_destroy_sem(info);
		free(info->prc);
		return (printf("Fail to create thread\n"));
	}
	if (pthread_detach(kill_philo) != 0)
	{
		ft_destroy_sem(info);
		free(info->prc);
		return (printf("Fail to detach thread\n"));
	}
	return (0);
}
