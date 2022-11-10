/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:36:48 by malord            #+#    #+#             */
/*   Updated: 2022/11/10 11:27:07 by malord           ###   ########.fr       */
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
		table[i].t_last_meal = timestamp();
		i++;
	}
	dead_check(philos, philos->philosophers);
	exit_sim(philos, philos->philosophers);
	return (0);
}

void	*routine_phi(void *void_philosopher)
{
	int				i;
	t_table			*table;
	t_philo			*philos;

	i = 0;
	table = (t_table *)void_philosopher;
	philos = table->data_philo;
	if (table->philo_id % 2)
		usleep(15000);
	while (!(philos->dead))
	{
		pthread_mutex_lock(&(philos->eat_check));
		if (philos->all_ate)
			break ;
		pthread_mutex_unlock(&(philos->eat_check));
		lets_eat(table);
		action_print(table->philo_id, "is sleeping");
		smart_sleep(philos->time_to_sleep);
		action_print(table->philo_id, "is thinking");
		i++;
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
	(table->x_ate)++;
	pthread_mutex_unlock(&(philos->forks[table->left_fork_id]));
	pthread_mutex_unlock(&(philos->forks[table->right_fork_id]));
}
