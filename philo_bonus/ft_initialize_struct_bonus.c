/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 22:17:08 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 15:45:54 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_kill_philo(t_info *info, int i)
{
	int	index;

	printf("Fail to create philo (process) nbr %d\n", i);
	index = 0;
	while (index < i)
	{
		if (kill(info->prc[index], SIGKILL) == -1)
			printf("And another fail to kill philo nbr %d\n", index);
		index++;
	}
	sem_close(info->forks);
	sem_unlink("/semforks");
	sem_close(info->died);
	sem_unlink("/semdied");
	sem_close(info->print);
	sem_unlink("/semprint");
	sem_close(info->died_print);
	sem_unlink("/semdiedprint");
}

int	ft_destroy_sem(t_info *info)
{
	sem_close(info->forks);
	sem_unlink("/semforks");
	sem_post(info->died);
	sem_close(info->died);
	sem_unlink("/semdied");
	sem_post(info->print);
	sem_close(info->print);
	sem_unlink("/semprint");
	sem_post(info->died_print);
	sem_close(info->died_print);
	sem_unlink("/semdiedprint");
	sem_close(info->stop_print);
	sem_unlink("/semstopprint");
	return (1);
}

int	ft_initialize_sem(t_info *info)
{
	info->forks = ((void *) 0);
	info->died = ((void *) 0);
	info->print = ((void *) 0);
	info->died_print = ((void *) 0);
	info->stop_print = ((void *) 0);
	sem_unlink("/semforks");
	sem_unlink("/semdied");
	sem_unlink("/semprint");
	sem_unlink("/semdiedprint");
	sem_unlink("/semstopprint");
	info->forks = sem_open("/semforks", O_CREAT | O_EXCL, 777, info->n_ph);
	info->died = sem_open("/semdied", O_CREAT | O_EXCL, 777, 0);
	info->print = sem_open("/semprint", O_CREAT | O_EXCL, 777, 1);
	info->died_print = sem_open("/semdiedprint", O_CREAT | O_EXCL, 777, 1);
	info->stop_print = sem_open("/semstopprint", O_CREAT | O_EXCL, 777, 1);
	if (info->forks == SEM_FAILED || info->died == SEM_FAILED
		|| info->print == SEM_FAILED || info->died_print == SEM_FAILED
		|| info->stop_print == SEM_FAILED)
	{
		free(info->prc);
		printf("Fail to create semaphore\n");
		return (1);
	}
	return (0);
}

int	ft_initialize_struct(t_info *info, int ac, char **av)
{
	info->n_ph = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	info->end_simul = 0;
	info->t_start = -1;
	info->m_id = 1;
	info->ph.id = -2;
	info->ph.i = -1;
	info->i = -1;
	if (ac == 6)
		info->ph.n_t_eat = ft_atoi(av[5]);
	else
		info->ph.n_t_eat = -1;
	if (info->ph.n_t_eat == 0)
		return (1);
	if (info->n_ph == 0)
		return (printf("inavlide number of philosophers\n"));
	info->prc = (long long *) malloc(sizeof(long long) * info->n_ph);
	if (info->prc == NULL)
		return (printf("Fail to allocte memory\n"));
	if (ft_initialize_sem(info))
		return (1);
	return (0);
}
