/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args_get_value.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:57:29 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/02/10 21:59:34 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_convert_args_toint(int ac, char **av, int **args)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		args[0][i - 1] = ft_atoi(av[i]);
		i++;
	}
	if (ac == 6)
		args[0][4] = ft_atoi(av[5]);
	else
		args[0][4] = -1;
}
