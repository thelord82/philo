/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:06:54 by malord            #+#    #+#             */
/*   Updated: 2022/11/03 10:32:31 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
// Contains functions : conversions, init_struct, init_threads and singletons

bool	conversions(int argc, char **argv)
{
	t_philo	*philos;

	philos = get_data();
	philos->nb_philos = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		philos->nb_eats = ft_atoi(argv[5]);
		if (philos->nb_eats <= 0)
		{
			printf("Error: All arguments must be more than zero\n");
			return (false);
		}
	}
	return (true);
}

bool	init_struct(int argc, char **argv)
{
	t_philo	*philos;

	philos = get_data();
	if (argc == 5 || argc == 6)
	{
		if (conversions(argc, argv) == false)
			return (false);
		if (philos->nb_philos <= 0 || philos->time_to_die <= 0
			|| philos->time_to_eat <= 0 || philos->time_to_sleep <= 0)
		{
			printf("Error: All arguments must be more than zero\n");
			return (false);
		}
		philos->forks = malloc(sizeof(pthread_mutex_t) * philos->nb_philos);
		pthread_mutex_init(philos->forks, NULL);
		init_threads(philos->nb_philos);
		return (true);
	}
	printf("Error: Wrong number of arguments\n");
	return (false);
}

void	*init_threads(int nb_philo)
{
	int			i;
	pthread_t	*philos;
	int			*res;

	i = 0;
	philos = malloc(sizeof(pthread_t) * nb_philo);
	while (i++ < nb_philo)
	{
		if (pthread_create(&philos[i], NULL, &init_sim, &i) != 0)
		{
			printf("Error creating threads\n");
			return (NULL);
		}
	}
	i = 0;
	while (i++ < nb_philo)
	{
		if (pthread_join(philos[i], (void **)&res) != 0)
		{
			printf("Error terminating thread\n");
			return (NULL);
		}
	}
	return (NULL);
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