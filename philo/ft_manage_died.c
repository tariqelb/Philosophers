/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_died.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:02:55 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 01:22:11 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_end_simul(t_info *info, int trd_i)
{
	if (info->ph.n_t_eat[trd_i] != -1)
	{
		info->ph.n_t_eat[trd_i]--;
		ft_is_all_eat(info);
		if (info->ph.n_t_eat[trd_i] == 0)
			return (0);
	}
	if (info->end_simul == 1)
	{
		pthread_mutex_unlock(&info->p_mutex);
		return (0);
	}
	return (1);
}

long int	ft_spend(t_info *info, int i)
{
	long int		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = ft_get_time(info) - info->ph.t_meal[i];
	return (time);
}

void	ft_print_died(t_info *info, long long time, int i)
{
	if (info->print_died == 1)
		return ;
	pthread_mutex_lock(&info->d_mutex);
	if (info->print_died == 0)
	{
		printf("%lld %d %s\n", time, i + 1, "died");
		info->print_died = 1;
	}
	else
	{
		pthread_mutex_unlock(&info->d_mutex);
		return ;
	}
	pthread_mutex_unlock(&info->d_mutex);
	ft_unlock(info);
}

void	*ft_died(void *arg)
{
	long int		time;
	t_info			*info;
	int				i;

	info = (t_info *) arg;
	while (info->ph.t_start == 0)
		usleep(50000);
	time = 0;
	while (info->end_simul == 0)
	{
		i = -1;
		while (++i < info->n_ph)
		{
			time = ft_spend(info, i);
			if (info->t_die <= time && info->end_simul == 0)
			{
				info->end_simul = 1;
				time = ft_get_time(info);
				ft_print_died(info, time, i);
			}
		}
	}
	return (NULL);
}

int	ft_manage_died(t_info *info)
{
	if (pthread_create(&info->die_trd, NULL, ft_died, info))
		return (printf("Fail in thread creation\n"));
	return (0);
}
