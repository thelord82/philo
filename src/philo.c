/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:36:26 by malord            #+#    #+#             */
/*   Updated: 2022/11/04 08:42:04 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*test_function(void *arg)
{
	(void)arg;
	printf("et voila!\n");
	return (NULL);
}

/*void *routine(void *arg)	// TEST FUNCTION
{
	pthread_mutex_t mutex;
	int *result = malloc(sizeof(int));
	int mails = 0;
	(void)arg;
	for (int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	*result = mails;
	printf("Valeur de result = %d\n", *result);
	usleep(500000);
	return ((void *)result);
}*/

void	lets_sleep(int philo)
{
	t_philo *philos;

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
	t_table *table;

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
	/* TODO Si le temps de manger + le temps de dormir + le temps de penser
	depasse le time_to_die, le philo doit mourir*/
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
	//pthread_mutex_t *mutex;
	//mutex = malloc(sizeof(mutex) * ft_atoi(argv[1]));
	//pthread_mutex_t mutex;
	//pthread_t thread1, thread2, thread3, thread4;
	//t_philo	*philos;

	//philos = get_data();
	//void *arg = NULL;
	t_table table;
	t_philo *philos;
	if (init_struct(argc, argv) == false)
		return (1);
	philos = get_data();
	pthread_mutex_init(&table.mute_message, NULL);
	pthread_mutex_destroy(&table.mute_message);
	pthread_mutex_destroy(philos->forks);
	return (0);
}
