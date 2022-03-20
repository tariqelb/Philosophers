/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_stats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:13:00 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/18 23:49:35 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_get_time(t_info *info)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = ft_get_milisec(tv) - info->ph.t_start;
	return (time);
}

int	ft_thinking(t_info *info, int trd_i)
{
	long int		time;

	if (info->end_simul == 1)
		return (0);
	pthread_mutex_lock(&info->p_mutex);
	if (info->end_simul == 1)
		return (0);
	time = ft_get_time(info);
	if (ft_print_act(info, time, trd_i + 1, "is thinking"))
		return (0);
	pthread_mutex_unlock(&info->p_mutex);
	if (info->end_simul == 1)
		return (0);
	return (1);
}

int	ft_end_lock(t_info *info, int trd_i)
{
	if (info->end_simul == 1)
	{
		pthread_mutex_unlock(&info->ph.mutex[trd_i]);
		pthread_mutex_unlock(&info->ph.mutex[(trd_i + 1) % info->n_ph]);
		return (1);
	}
	return (0);
}

int	ft_take_forks(t_info *info, int trd_i)
{
	if (info->n_ph == 1)
		return (ft_one_fork(info, trd_i));
	if (info->ph.first_meal[trd_i] == 0)
		if (ft_thinking(info, trd_i) == 0)
			return (0);
	if (info->end_simul == 1)
		return (0);
	pthread_mutex_lock(&info->ph.mutex[trd_i]);
	if (ft_end_lock(info, trd_i) == 1)
		return (0);
	pthread_mutex_lock(&info->p_mutex);
	info->time = ft_get_time(info);
	pthread_mutex_unlock(&info->p_mutex);
	if (ft_print_act(info, info->time, trd_i + 1, "has token a fork"))
		return (0);
	pthread_mutex_lock(&info->ph.mutex[(trd_i + 1) % info->n_ph]);
	if (ft_end_lock(info, trd_i) == 1)
		return (0);
	pthread_mutex_lock(&info->p_mutex);
	info->time = ft_get_time(info);
	pthread_mutex_unlock(&info->p_mutex);
	if (ft_print_act(info, info->time, trd_i + 1, "has token a fork"))
		return (0);
	return (1);
}

int	ft_eat_and_sleep(t_info *info, int trd_i)
{
	long int	time;

	time = 0;
	if (info->end_simul == 1)
		return (0);
	info->ph.t_meal[trd_i] = ft_get_time(info);
	time = info->ph.t_meal[trd_i];
	pthread_mutex_lock(&info->p_mutex);
	if (ft_print_act(info, time, trd_i + 1, "is eating"))
		return (0);
	pthread_mutex_unlock(&info->p_mutex);
	if (ft_deep_eat(info, time, trd_i) == 0)
		return (0);
	pthread_mutex_unlock(&info->ph.mutex[trd_i]);
	pthread_mutex_unlock(&info->ph.mutex[(trd_i + 1) % info->n_ph]);
	if (ft_end_simul(info, trd_i) == 0)
		return (0);
	pthread_mutex_lock(&info->p_mutex);
	time = ft_get_time(info);
	if (ft_print_act(info, time, trd_i + 1, "is sleeping"))
		return (0);
	pthread_mutex_unlock(&info->p_mutex);
	info->ph.first_meal[trd_i] = 0;
	return (ft_deep_sleep(info, time));
}
