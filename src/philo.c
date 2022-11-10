/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:36:26 by malord            #+#    #+#             */
/*   Updated: 2022/11/09 19:53:04 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	printf("Valeur de x_ate = %d\n", table->x_ate);
	printf("Valeur de nb_eats = %d\n", philos->nb_eats);
	pthread_mutex_unlock(&(philos->forks[table->left_fork_id]));
	pthread_mutex_unlock(&(philos->forks[table->right_fork_id]));
}

void	exit_sim(t_philo *philos, t_table *table)
{
	int		i;

	i = -1;
	while (++i < philos->nb_philos)
		pthread_join(table[i].thread_id, NULL);
	i = -1;
	while (++i < philos->nb_philos)
		pthread_mutex_destroy(&(philos->forks[i]));
	pthread_mutex_destroy(&(philos->mute_message));
}

void	dead_check(t_philo *phi, t_table *table)
{
	int		i;

	while (!(phi->all_ate))
	{
		i = -1;
		while (++i < phi->nb_philos && !(phi->dead))
		{
			pthread_mutex_lock(&(phi->meal_check));
			if (time_diff(table[i].t_last_meal, timestamp()) > phi->time_to_die)
			{
				action_print(i, "died");
				phi->dead = 1;
			}
			pthread_mutex_unlock(&(phi->meal_check));
			usleep(50);
		}
		if (phi->dead)
			break ;
		i = 0;
		while (phi->nb_eats != -1 && i < phi->nb_philos
			&& table[i].x_ate >= phi->nb_eats)
			i++;
		if (i == phi->nb_philos - 1)
			phi->all_ate = 1;
	}
}

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
		lets_eat(table);
		if (philos->all_ate)
			break ;
		action_print(table->philo_id, "is sleeping");
		smart_sleep(philos->time_to_sleep);
		action_print(table->philo_id, "is thinking");
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	if (init_struct(argc, argv) == false)
		return (1);
	return (0);
}

//TODO Verifier si une integration de x_ate et nb_eats dans philo_sim peut fonctionner
//TODO leaks
//TODO 1 seul philo, il meurt mais hang
//TODO Plus de 2 philos et un nb_eats defini, fonctionne pas