/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:06:54 by malord            #+#    #+#             */
/*   Updated: 2022/11/10 14:11:46 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		if (check_numbers(argv) == false
			|| conversions(argc, argv) == false)
			return (false);
		if (check_values(philos) == false)
			return (false);
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
	i = philos->nb_philos;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&philos->forks[i], NULL) != 0)
			return (1);
	}
	if (pthread_mutex_init(&philos->mute_message, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philos->meal_check, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philos->eat_check, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philos->mx_ate, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philos->dead_lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_philos(void)
{
	t_philo	*philos;
	int		i;

	philos = get_data();
	i = philos->nb_philos;
	while (--i >= 0)
	{
		philos->philosophers[i].philo_id = i;
		philos->philosophers[i].x_ate = 0;
		philos->philosophers[i].left_fork_id = i;
		philos->philosophers[i].right_fork_id = (i + 1) % philos->nb_philos;
		philos->philosophers[i].t_last_meal = 0;
		philos->philosophers[i].data_philo = philos;
	}
	return (0);
}
