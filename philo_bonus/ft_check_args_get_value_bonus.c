/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args_get_value_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:17:57 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/03/19 14:22:41 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_is_digit(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] >= '0' && av[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_valide_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_is_digit(av[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(char *av)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (av[i])
	{
		nbr = nbr * 10;
		nbr = nbr + (av[i] - 48);
		i++;
	}
	return (nbr);
}

int	ft_basic_operation(int ac, char **av, t_info *info)
{
	if (ac != 5 && ac != 6)
		return (printf("Invalid number of argument\n"));
	if (ft_valide_args(ac, av) == 0)
		return (printf("Invalid argument\n"));
	info->ph.t_meal = 0;
	info->ph.first_meal = 1;
	if (ft_initialize_struct(info, ac, av) >= 1)
		return (1);
	return (0);
}
