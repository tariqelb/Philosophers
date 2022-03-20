/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_struct_philo.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:25:50 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 00:56:53 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_arr(int *n_t_eat, int n_ph, int n_times)
{
	int	i;

	i = 0;
	while (i < n_ph)
	{
		n_t_eat[i] = n_times;
		i++;
	}
}

void	ft_sub_initialize(t_info *info, int *args)
{
	info->ph.trd = NULL;
	info->ph.mutex = NULL;
	info->ph.t_meal = NULL;
	info->ph.first_meal = NULL;
	info->ph.n_t_eat = NULL;
	info->ph.t_start = 0;
	info->n_ph = args[0];
	info->t_die = args[1];
	info->t_eat = args[2];
	info->t_sleep = args[3];
	info->barrier = args[0];
	info->end_simul = 0;
	info->all_eat = 0;
	info->print_died = 0;
	info->joined = 0;
}

int	ft_initialize(t_info *info, int *args)
{
	int	nb;

	ft_sub_initialize(info, args);
	nb = info->n_ph;
	info->ph.trd = (pthread_t *) malloc(sizeof(pthread_t) * info->n_ph);
	info->ph.mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nb);
	info->ph.t_meal = (long long *) malloc(sizeof(long long) * nb);
	info->ph.first_meal = (int *) malloc(sizeof(int) * info->n_ph);
	info->ph.n_t_eat = (int *) malloc(sizeof(int) * info->n_ph);
	if (info->ph.trd == NULL || info->ph.mutex == NULL)
		return (printf("Memory allocation fail\n"));
	if (info->ph.t_meal == NULL || info->ph.first_meal == NULL)
		return (printf("Memory allocation fail\n"));
	if (info->ph.n_t_eat == NULL)
		return (printf("Memory allocation fail\n"));
	return (0);
}

void	ft_free(t_info info)
{
	free(info.ph.trd);
	free(info.ph.mutex);
	free(info.ph.t_meal);
	free(info.ph.first_meal);
	free(info.ph.n_t_eat);
}
