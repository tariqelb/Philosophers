/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:29:17 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/18 03:53:52 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	ft_get_time(t_info *info)
{
	return (ft_get_milisec() - info->t_start);
}

long long	ft_get_milisec(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	ft_deep_eat(t_info *info, long long time)
{
	long long	t_eat;

	t_eat = ft_get_time(info) + info->t_eat;
	while (time < t_eat)
	{
		usleep(100);
		time = ft_get_time(info);
	}
	return (1);
}

int	ft_deep_sleep(t_info *info, long long time)
{
	long long	t_sleep;

	t_sleep = ft_get_time(info) + info->t_sleep;
	while (time < t_sleep)
	{
		usleep(100);
		time = ft_get_time(info);
	}
	return (1);
}

int	ft_am_full(t_info *info)
{
	info->ph.n_t_eat--;
	if (info->ph.n_t_eat == 0)
		return (1);
	return (0);
}
