/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:06:54 by malord            #+#    #+#             */
/*   Updated: 2022/11/08 13:49:38 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
// Contains functions : conversions, init_struct, init_threads and singletons

bool	conversions(int argc, char **argv)
{
	t_philo	*philos;
	int		i;

	i = 1;
	philos = get_data();
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
	if (argc == 6)
		philos->nb_eats = ft_atol(argv[5]);
	return (true);
}

bool	init_rest(void)
{
	if (init_mutex())
		return (false);
	init_philos();
	return (true);
}

bool	init_struct(int argc, char **argv)
{
	t_philo	*philos;

	philos = get_data();
	if (argc == 5 || argc == 6)
	{
		if (check_numbers(argv) == false || conversions(argc, argv) == false)
			return (false);
		if (philos->nb_philos <= 0 || philos->time_to_die <= 0
			|| philos->time_to_eat <= 0 || philos->time_to_sleep <= 0)
		{
			printf("Error: All arguments must be a positive integer\n");
			return (false);
		}
		if (philos->nb_eats != 0 && philos->nb_eats <= 0)
		{
			printf("Error: All arguments must be a positive integer\n");
			return (false);
		}
		init_rest();
		philo_sim();
		return (true);
	}
	printf("Error: Wrong number of arguments\n");
	return (false);
}

int	init_mutex(void)
{
	t_philo	*philos;
	int		i;

	philos = get_data();
	i = 0;
	while (i < philos->nb_philos)
	{
		if (pthread_mutex_init(&philos->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&philos->mute_message, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philos->meal_check, NULL) != 0)
		return (1);
	return (0);
}

int	init_philos(void)
{
	t_philo	*philos;
	int		i;

	philos = get_data();
	philos->philosophers = malloc(sizeof(t_table) * 200);
	i = 0;
	while (i < philos->nb_philos)
	{
		philos->philosophers[i].philo_id = i;
		philos->philosophers[i].x_ate = 0;
		philos->philosophers[i].left_fork_id = i;
		if (i == 0)
			philos->philosophers[i].right_fork_id = philos->nb_philos - 1;
		else
			philos->philosophers[i].right_fork_id = i - 1;
		philos->philosophers[i].t_last_meal = 0;
		philos->philosophers[i].data_philo = philos;
		i++;
	}
	return (0);
}

t_philo	*get_data(void)
{
	static t_philo	*data = NULL;

	if (data == NULL)
		data = (t_philo *)malloc(sizeof(t_philo));
	return (data);
}

t_table	*get_table(void)
{
	static t_table	*data = NULL;

	if (data == NULL)
		data = (t_table *)malloc(sizeof(t_table));
	return (data);
}