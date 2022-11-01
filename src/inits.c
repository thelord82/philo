/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:16:29 by malord            #+#    #+#             */
/*   Updated: 2022/11/01 14:26:00 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*init_threads(int nb_philo)
{
	int			i;
	pthread_t	*philos;
	int			*res;

	i = 0;
	philos = malloc(sizeof(pthread_t) * nb_philo);
	while (i < nb_philo)
	{
		if (pthread_create(&philos[i], NULL, &init_sim, NULL) != 0)
		{
			printf("Error creating threads\n");
			return (NULL);
		}
		if (pthread_join(philos[i], (void **)&res) != 0)
		{
			printf("Error terminating thread\n");
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

bool	init_struct(int argc, char **argv)
{
	t_philo	*philos;

	philos = get_data();
	if (argc == 5 || argc == 6)
	{
		philos->nb_philos = ft_atoi(argv[1]);
		philos->time_to_die = ft_atoi(argv[2]);
		philos->time_to_eat = ft_atoi(argv[3]);
		philos->time_to_sleep = ft_atoi(argv[4]);
		philos->forks = malloc(sizeof(philos->forks) * philos->nb_philos);
		if (argc == 6)
			philos->nb_eats = ft_atoi(argv[5]);
		init_threads(philos->nb_philos);
		return (true);
	}
	return (false);
}

t_philo	*get_data(void)
{
	static t_philo	*data = NULL;

	if (data == NULL)
		data = (t_philo *)malloc(sizeof(t_philo));
	return (data);
}