/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:36:26 by malord            #+#    #+#             */
/*   Updated: 2022/11/04 11:22:06 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lets_sleep(int philo)
{
	t_philo	*philos;

	philos = get_data();
	pthread_mutex_unlock(&philos->forks[philo]);
	pthread_mutex_unlock(&philos->forks[philo + 1]);
	printf("%d is sleeping\n", philo);
	usleep(philos->time_to_sleep * 1000);
	printf("%d is thinking\n", philo);
}

void	lets_eat(int philo)
{
	t_philo	*philos;
	t_table	*table;

	if (philo % 2 == 0)
		return ;
	philos = get_data();
	table = get_table();
	pthread_mutex_lock(&philos->forks[philo - 1]);
	pthread_mutex_lock(&table->mute_message);
	printf("%d has taken fork number %d\n", philo, philo);
	pthread_mutex_unlock(&table->mute_message);
	if (philo == 1)
	{
		pthread_mutex_lock(&table->mute_message);
		pthread_mutex_lock(&philos->forks[(philos->nb_philos) - 1]);
		printf("%d has taken fork number %d\n", philo, philos->nb_philos);
		printf("%d is eating\n", philo);
		pthread_mutex_unlock(&table->mute_message);
		pthread_mutex_unlock(&philos->forks[(philos->nb_philos) - 1]);
		usleep(philos->time_to_eat * 1000);
	}
	else
	{
		pthread_mutex_lock(&philos->forks[philo - 2]);
		pthread_mutex_lock(&table->mute_message);
		printf("%d has taken fork number %d\n", philo, philo - 1);
		printf("%d is eating\n", philo);
		pthread_mutex_unlock(&table->mute_message);
		pthread_mutex_unlock(&philos->forks[philo - 2]);
		usleep(philos->time_to_eat * 1000);
	}
	pthread_mutex_unlock(&philos->forks[philo - 1]);
	pthread_mutex_lock(&table->mute_message);
	printf("%d is sleeping\n", philo);
	pthread_mutex_unlock(&table->mute_message);
	usleep(philos->time_to_eat * 1000);
}

void	*init_sim(void *arg)
{
	int		*i;
	t_philo	*philos;

	philos = get_data();
	i = (int *)arg;
	lets_eat(*(i) + 1);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;

	if (init_struct(argc, argv) == false)
		return (1);
	philos = get_data();
	pthread_mutex_init(&table.mute_message, NULL);
	pthread_mutex_destroy(&table.mute_message);
	pthread_mutex_destroy(philos->forks);
	return (0);
}
