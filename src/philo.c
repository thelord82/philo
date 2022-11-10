/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:36:26 by malord            #+#    #+#             */
/*   Updated: 2022/11/10 14:15:07 by malord           ###   ########.fr       */
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

void	exit_sim(t_philo *philos, t_table *table)
{
	int		i;

	i = -1;
	while (++i < philos->nb_philos)
		pthread_join(table[i].thread_id, NULL);
	i = -1;
	while (++i < philos->nb_philos)
		pthread_mutex_unlock(&(philos->forks[i]));
	i = -1;
	while (++i < philos->nb_philos)
		pthread_mutex_destroy(&(philos->forks[i]));
	pthread_mutex_destroy(&(philos->mute_message));
	pthread_mutex_destroy(&(philos->meal_check));
	pthread_mutex_destroy(&(philos->eat_check));
	pthread_mutex_destroy(&(philos->mx_ate));
	pthread_mutex_destroy(&(philos->dead_lock));
	del_data();
}

void	kill_philo(t_philo *phi, t_table *table, int i)
{
	pthread_mutex_lock(&(phi->meal_check));
	if (time_diff(table[i].t_last_meal, timestamp()) > phi->time_to_die)
	{
		action_print(i, "died");
		pthread_mutex_lock(&(phi->dead_lock));
		phi->dead = 1;
		pthread_mutex_unlock(&(phi->dead_lock));
	}
	pthread_mutex_unlock(&(phi->meal_check));
	usleep(100);
}

void	dead_check(t_philo *phi, t_table *table)
{
	int		i;

	while (!(phi->all_ate))
	{
		i = -1;
		while (++i < phi->nb_philos && !(phi->dead))
			kill_philo(phi, table, i);
		if (phi->dead != 0)
		{
			i = -1;
			while (++i < phi->nb_philos)
				pthread_mutex_unlock(&(phi->forks[i]));
			break ;
		}
		i = 0;
		while (phi->nb_eats != -1 && i < phi->nb_philos
			&& table[i].x_ate >= phi->nb_eats)
			i++;
		if (i == phi->nb_philos)
		{
			pthread_mutex_lock(&(phi->eat_check));
			phi->all_ate = 1;
			pthread_mutex_lock(&(phi->eat_check));
		}
	}
}

int	main(int argc, char **argv)
{
	if (init_struct(argc, argv) == false)
	{
		del_data();
		return (1);
	}
	return (0);
}
