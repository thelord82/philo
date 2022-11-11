/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:36:48 by malord            #+#    #+#             */
/*   Updated: 2022/11/11 12:12:47 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_sim(void)
{
	int		i;
	t_table	*table;
	t_philo	*philos;

	i = 0;
	philos = get_data();
	table = philos->philosophers;
	philos->f_timestamp = timestamp();
	while (i < philos->nb_philos)
	{
		if (pthread_create(&(table[i].thread_id), NULL, routine_phi,
				&(table[i])) != 0)
			return (1);
		pthread_mutex_lock(&(philos->meal_check));
		table[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&(philos->meal_check));
		i++;
	}
	dead_check(philos, philos->philosophers);
	exit_sim(philos, philos->philosophers);
	return (0);
}

static void	print_n_sleep(t_philo *philos, t_table *table)
{
	action_print(table->philo_id, "is sleeping");
	smart_sleep(philos->time_to_sleep);
	action_print(table->philo_id, "is thinking");
}

void	*routine_phi(void *void_philosopher)
{
	t_table			*table;
	t_philo			*philos;

	table = (t_table *)void_philosopher;
	philos = table->data_philo;
	if (table->philo_id % 2)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&(philos->mute_message));
		pthread_mutex_lock(&(philos->eat_check));
		if (philos->dead || philos->all_ate)
		{
			pthread_mutex_unlock(&(philos->mute_message));
			pthread_mutex_unlock(&(philos->eat_check));
			break ;
		}
		pthread_mutex_unlock(&(philos->mute_message));
		pthread_mutex_unlock(&(philos->eat_check));
		lets_eat(table);
		print_n_sleep(philos, table);
	}
	pthread_mutex_unlock(&(philos->eat_check));
	return (NULL);
}

void	lets_eat(t_table *table)
{
	t_philo	*philos;

	philos = table->data_philo;
	pthread_mutex_lock(&(philos->forks[table->left_fork_id]));
	action_print(table->philo_id, "has taken a fork");
	pthread_mutex_lock(&(philos->forks[table->right_fork_id]));
	action_print(table->philo_id, "has taken a fork");
	pthread_mutex_lock(&(philos->meal_check));
	action_print(table->philo_id, "is eating");
	table->t_last_meal = timestamp();
	pthread_mutex_unlock(&(philos->meal_check));
	smart_sleep(philos->time_to_eat);
	pthread_mutex_lock(&(philos->mx_ate));
	(table->x_ate)++;
	pthread_mutex_unlock(&(philos->mx_ate));
	pthread_mutex_unlock(&(philos->forks[table->left_fork_id]));
	pthread_mutex_unlock(&(philos->forks[table->right_fork_id]));
}
