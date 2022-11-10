/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:39:13 by malord            #+#    #+#             */
/*   Updated: 2022/11/10 10:44:21 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_nb_eats(int argc, char **argv)
{
	t_philo	*philos;

	philos = get_data();
	if (argc == 6)
	{
		philos->nb_eats = ft_atol(argv[5]);
		if (philos->nb_eats <= 0)
		{
			printf("Error: All arguments must be a positive integer\n");
			return (false);
		}
	}
	else
		philos->nb_eats = -1;
	return (true);
}

bool	conversions(int argc, char **argv)
{
	t_philo	*philos;
	int		i;

	philos = get_data();
	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 10 || ft_atol(argv[i]) > INT_MAX)
		{
			printf("Error: All arguments must be a positive integer\n");
			return (false);
		}
		i++;
	}
	philos->nb_philos = ft_atol(argv[1]);
	philos->time_to_die = ft_atol(argv[2]);
	philos->time_to_eat = ft_atol(argv[3]);
	philos->time_to_sleep = ft_atol(argv[4]);
	philos->all_ate = 0;
	philos->dead = 0;
	if (check_nb_eats(argc, argv) == false)
		return (false);
	return (true);
}

bool	check_values(t_philo *philos)
{
	if (philos->nb_philos <= 0 || philos->time_to_die <= 0
		|| philos->time_to_eat <= 0 || philos->time_to_sleep <= 0)
	{
		printf("Error: All arguments must be a positive integer\n");
		return (false);
	}
	if (philos->nb_philos > 200 || philos->time_to_die < 60
		|| philos->time_to_eat < 60 || philos->time_to_sleep < 60)
	{
		printf("Error: This simulation works with a max of 200 ");
		printf("philosophers and timings of at least 60.\n");
		return (false);
	}
	return (true);
}
