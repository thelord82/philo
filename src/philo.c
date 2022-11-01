/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:36:26 by malord            #+#    #+#             */
/*   Updated: 2022/11/01 15:41:15 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	nombre;
	int	neg;

	nombre = 0;
	neg = 1;
	if (!*str)
		return (0);
	while (*str && (ft_isspace(*str) == 1))
		str++;
	if (*str == '-')
	{
		neg = -neg;
		str++;
	}
	else if (*str == '+')
		str++;
	while (str && ft_isdigit(*str) == 1)
	{
		nombre = nombre * 10 + (*str - '0');
		str++;
	}
	return (nombre * neg);
}

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

void	lets_eat(int philo)
{
	t_philo	*philos;

	philos = get_data();
	pthread_mutex_lock(&philos->forks[philo]);
	printf("philo %d has taken a fork\n", philo);
	pthread_mutex_lock(&philos->forks[philo + 1]);
	printf("philo %d has taken a fork\n", philo);
	printf("philo %d is eating\n", philo);
	pthread_mutex_unlock(&philos->forks[philo]);
	pthread_mutex_unlock(&philos->forks[philo + 1]);
	usleep(philos->time_to_eat * 1000);
	printf("philo %d is sleeping\n", philo);
	usleep(philos->time_to_sleep * 1000);
	printf("philo %d is thinking\n", philo);
	/* TODO Si le temps de manger + le temps de dormir + le temps de penser
	depasse le time_to_die, le philo doit mourir*/
}

void	*init_sim(void *arg)
{
	int		i;
	t_philo	*philos;

	philos = get_data();
	(void)arg;
	i = 1;
	while (i <= philos->nb_philos)
	{
		lets_eat(i);
		if (i + 2 < philos->nb_philos)
		{
			i++;
			lets_eat(i + 2);
		}
	}
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
	void *arg = NULL;
	if (init_struct(argc, argv) == false)
	{
		printf("Error : Wrong number of arguments\n");
		return (1);
	}
	while (1)
	{
		init_sim(arg);
	}
	/*pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&thread1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&thread2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_create(&thread3, NULL, &routine, NULL) != 0)
		return (3);
	if (pthread_create(&thread4, NULL, &routine, NULL) != 0)
		return (4);
	if (pthread_join(thread1, NULL) != 0)
		return (5);
	if (pthread_join(thread2, NULL) != 0)
		return (6);
	if (pthread_join(thread3, NULL) != 0)
		return (7);
	if (pthread_join(thread4, NULL) != 0)
		return (8);
	pthread_mutex_destroy(&mutex);*/
	return (0);
}
