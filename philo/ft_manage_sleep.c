/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:06:20 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 00:11:28 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_get_milisec(struct timeval tv)
{
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_deep_sleep(t_info *info, long int timestamp)
{
	long int		t_sleep;

	t_sleep = ft_get_time(info) + info->t_sleep;
	while (timestamp < t_sleep)
	{
		usleep(100);
		if (info->end_simul == 1)
			return (0);
		timestamp = ft_get_time(info);
	}
	return (1);
}

int	ft_deep_eat(t_info *info, long int timestamp, int trd_i)
{
	long int		t_eat;

	t_eat = ft_get_time(info) + info->t_eat;
	while (timestamp < t_eat)
	{
		usleep(100);
		if (info->end_simul == 1)
		{
			pthread_mutex_unlock(&info->ph.mutex[trd_i]);
			pthread_mutex_unlock(&info->ph.mutex[(trd_i + 1) % info->n_ph]);
			return (0);
		}
		timestamp = ft_get_time(info);
	}
	return (1);
}

void	ft_is_all_eat(t_info *info)
{
	int	i;
	int	flag;

	flag = 1;
	i = 0;
	while (i < info->n_ph)
	{
		if (info->ph.n_t_eat[i] > 0)
			flag = 0;
		i++;
	}
	info->end_simul = flag;
	info->all_eat = flag;
}

int	ft_print_act(t_info *info, long int time, int trd, char *act)
{
	if (info->end_simul == 0)
	{
		printf("%ld %d %s\n", time, trd, act);
		return (0);
	}
	pthread_mutex_unlock(&info->p_mutex);
	return (1);
}
