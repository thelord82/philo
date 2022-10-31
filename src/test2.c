/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:00:29 by malord            #+#    #+#             */
/*   Updated: 2022/10/31 12:04:46 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TEST DE RETURN VALUE FROM THREAD ! 
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

void *routine(void *arg)
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
	return ((void *)result);
}

void	*init_threads(int nb_philo)
{
	int			i;
	pthread_t	*philos;

	i = 0;
	philos = malloc(sizeof(pthread_t) * nb_philo);
	int *res;
	while (i < nb_philo)
	{
		if (pthread_create(&philos[i], NULL, &routine, NULL) != 0)
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
		printf("Valeur de result final = %d\n", *res);
		free(res);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_times;
	//pthread_mutex_t *mutex;
	//mutex = malloc(sizeof(mutex) * ft_atoi(argv[1]));
	//pthread_mutex_t mutex;
	//pthread_t thread1, thread2, thread3, thread4;
	if (argc == 5 || argc == 6)
	{
		nb_philo = ft_atoi(argv[1]);
		time_to_die = ft_atoi(argv[2]);
		time_to_eat = ft_atoi(argv[3]);
		time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			eat_times = ft_atoi(argv[5]);
		init_threads(nb_philo);
	}
	else
		printf("Error : Wrong number of arguments\n");
	/*(void)argc;
	(void)argv;
	pthread_mutex_init(&mutex, NULL);
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
