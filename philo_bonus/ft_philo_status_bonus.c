/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 03:59:09 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 15:53:46 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print_action(t_info *info, t_ll time, char *str)
{
	sem_wait(info->stop_print);
	printf("%lld %d %s\n", time, info->ph.i + 1, str);
	sem_post(info->stop_print);
}

void	ft_one_fork(t_info *info)
{
	long long	time;

	time = ft_get_time(info);
	ft_print_action(info, time, "has token a fork");
	sem_wait(info->forks);
	while (1)
	{
		usleep(1000);
	}
}

int	ft_tinking(t_info *info)
{
	long long	time;

	sem_wait(info->print);
	time = ft_get_time(info);
	ft_print_action(info, time, "is tinking");
	sem_post(info->print);
	return (1);
}

int	ft_take_forks(t_info *info)
{
	long long	time;

	if (info->ph.first_meal == 0)
		if (ft_tinking(info) == 0)
			return (0);
	sem_wait(info->forks);
	sem_wait(info->print);
	time = ft_get_time(info);
	ft_print_action(info, time, "has token a fork");
	sem_post(info->print);
	sem_wait(info->forks);
	sem_wait(info->print);
	time = ft_get_time(info);
	ft_print_action(info, time, "has token a fork");
	sem_post(info->print);
	return (1);
}

int	ft_eat_and_sleep(t_info *info)
{
	long long	time;

	sem_wait(info->print);
	time = ft_get_time(info);
	info->ph.t_meal = time;
	ft_print_action(info, time, "is eating");
	sem_post(info->print);
	ft_deep_eat(info, time);
	sem_post(info->forks);
	sem_post(info->forks);
	if (info->ph.n_t_eat != -1 && ft_am_full(info) == 1)
		exit(1);
	sem_wait(info->print);
	time = ft_get_time(info);
	ft_print_action(info, time, "is sleeping");
	sem_post(info->print);
	if (ft_deep_sleep(info, time) == 0)
		return (1);
	return (1);
}
