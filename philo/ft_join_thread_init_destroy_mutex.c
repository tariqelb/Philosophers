/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_thread_init_destroy_mutex.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:41:46 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 01:09:11 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_join_threads(t_info *info, int n_ph)
{
	int	i;

	info->joined = 0;
	while (info->joined < n_ph)
	{
		if (pthread_join(info->ph.trd[info->joined], NULL) != 0)
		{
			printf("Fail to join thread %d\n", info->joined);
			return ;
		}
		info->joined++;
		if (info->end_simul == 1 || info->all_eat == 1)
		{
			i = 0;
			while (i < info->n_ph)
			{
				pthread_mutex_unlock(&(info->p_mutex));
				pthread_mutex_unlock(&(info->ph.mutex[i]));
				i++;
			}
		}
	}
}

void	ft_join_died_thread(t_info *info)
{
	if (pthread_join(info->die_trd, NULL) != 0)
	{
		printf("Fail to join manage thread\n");
		return ;
	}
}

int	ft_initialize_mutex(t_info *info, int n_ph)
{
	int	i;

	i = 0;
	while (i < n_ph)
	{
		if (pthread_mutex_init(&(info->ph.mutex[i]), NULL) != 0)
		{
			printf("Fail to initialize ph mutex\n");
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&(info->p_mutex), NULL) != 0)
	{
		printf("Fail to initialize p mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&(info->d_mutex), NULL) != 0)
	{
		printf("Fail to initialize died mutex\n");
		return (1);
	}
	return (0);
}

void	ft_unlock(t_info *info)
{
	int	i;

	while (info->joined < info->n_ph)
	{
		i = 0;
		while (i < info->n_ph)
		{	
			pthread_mutex_unlock(&(info->p_mutex));
			pthread_mutex_unlock(&(info->d_mutex));
			pthread_mutex_unlock(&(info->ph.mutex[i]));
			i++;
		}
	}
}

void	ft_destroy_mutex(t_info *info, int n_ph)
{
	int	index;

	index = 0;
	pthread_mutex_unlock(&info->p_mutex);
	while (pthread_mutex_destroy(&(info->p_mutex)) != 0)
	{
		printf("Fail to destroy p mutex %d\n", index);
		return ;
	}
	while (pthread_mutex_destroy(&(info->d_mutex)) != 0)
	{
		printf("Fail to destroy d mutex %d\n", index);
		return ;
	}
	while (index < n_ph)
	{
		pthread_mutex_unlock(&info->ph.mutex[index]);
		if (pthread_mutex_destroy(&(info->ph.mutex[index])) != 0)
		{
			printf("Fail to destroy ph mutex %d\n", index);
			return ;
		}
		index++;
	}
}
