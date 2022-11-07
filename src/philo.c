/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:36:26 by malord            #+#    #+#             */
/*   Updated: 2022/11/07 18:54:35 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*init_sim(void *arg)
{
	t_table	*table;
	t_philo	*philos;

	table = (t_table *)arg;
	philos = get_data();
	if (table->philo_id % 2)
		usleep(15000);
	while (!(philos->dead))
	{
		lets_eat();
		if (philos->all_ate)
			break ;
		printf("%d is sleeping\n", table->philo_id);
		printf("%d is thinking\n", table->philo_id);
	}
	return (NULL);
}

void	action_print(int id, char *string)
{
	t_philo	*philos;

	philos = get_data();
	pthread_mutex_lock(&(philos->mute_message));
	if (!(philos->dead))
	{
		printf("%lli ", timestamp() - philos->f_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(philos->mute_message));
	return ;
}

void	lets_eat(void)
{
	t_philo	*philos;
	t_table	*table;

	philos = get_data();
	table = get_table();
	pthread_mutex_lock(&(philos->forks[table->left_fork_id]));
	action_print(table->philo_id, "has taken a fork");
	pthread_mutex_lock(&(philos->forks[table->right_fork_id]));
	action_print(table->philo_id, "has taken a fork");
	pthread_mutex_lock(&(philos->meal_check));
	action_print(table->philo_id, "is eating");
	table->t_last_meal = timestamp();
	pthread_mutex_unlock(&(philos->meal_check));
	smart_sleep(philos->time_to_eat);
	(table->x_ate)++;
	pthread_mutex_unlock(&(philos->forks[table->left_fork_id]));
	pthread_mutex_unlock(&(philos->forks[table->right_fork_id]));
}

void	exit_sim(void)
{
	int		i;
	t_philo	*philos;
	t_table	*table;

	i = 0;
	philos = get_data();
	table = get_table();
	while (i < philos->nb_philos)
	{
		pthread_join(table->thread_id, NULL);
		i++;
	}	
	i = 0;
	while (i < philos->nb_philos)
	{
		pthread_mutex_destroy(&(philos->forks[i]));
		i++;
	}	
	pthread_mutex_destroy(&(philos->mute_message));
}

void	dead_check(void)
{
	t_philo	*philos;
	t_table	*table;
	int		i;

	philos = get_data();
	table = get_table();
	while (!(philos->all_ate))
	{
		i = 0;
		while (i < philos->nb_philos && !(philos->dead))
		{
			if (time_diff(philos->philosophers[i].t_last_meal, timestamp())
				> philos->time_to_die)
			{
				action_print(i, "died");
				philos->dead = 1;
			}
			pthread_mutex_unlock(&(philos->meal_check));
			usleep(100);
			i++;
		}
		if (philos->dead)
			break ;
		i = 0;
		while (philos->nb_eats != -1 && 1 < philos->nb_philos
			&& table->x_ate >= philos->nb_eats)
			i++;
		if (i == philos->nb_philos)
			philos->all_ate = 1;
	}
}

int	philo_sim(void)
{
	int		i;
	t_table *table;
	t_philo	*philos;

	i = 0;
	philos = get_data();
	philos->philosophers = malloc(sizeof(p_thread) * philos->nb_philos);
	table = philos->philosophers;
	philos->f_timestamp = timestamp();
	while (i < philos->nb_philos)
	{
		if (pthread_create(&(table[i].thread_id), NULL, p_thread, &(table[i])))
			return (1);
		table[i].t_last_meal = timestamp();
		i++;
	}
	dead_check();
	exit_sim();
	return (0);
}

void	*p_thread(void *void_philosopher)
{
	int				i;
	t_table			*table;
	t_philo			*philos;

	i = 0;
	table = (t_table *)void_philosopher;
	philos = get_data();
	if (table->philo_id % 2)
		usleep(15000);
	while (!(philos->dead))
	{
		lets_eat();
		if (philos->all_ate)
			break ;
		action_print(philos->philo_id, "is sleeping");
		smart_sleep(philos->time_to_sleep);
		action_print(philos->philo_id, "is thinking");
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	//t_table	table;
	//t_philo	*philos;

	if (init_struct(argc, argv) == false)
		return (1);
	//philos = get_data();
	//philo_sim();
	//pthread_mutex_init(&philos->mute_message, NULL);
	//pthread_mutex_destroy(&philos->mute_message);
	//pthread_mutex_destroy(philos->forks);
	return (0);
}
