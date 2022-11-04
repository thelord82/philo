/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:36:26 by malord            #+#    #+#             */
/*   Updated: 2022/11/04 14:26:54 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*init_sim(void *arg)
{
	int		*i;
	t_table	*table;
	t_philo	*philos;

	table = (t_table *)arg;
	philos = get_data();
	if (table->philo_id % 2)
		usleep(15000);
	while (!(philos->dead))
	{
		lets_eat(table);
		if (philos->all_ate)
			break ;
		printf("%d is sleeping\n", table->philo_id);
		//TODO smart sleep
		printf("%d is thinking\n", table->philo_id);
	}
	return (NULL);
}

// Refactoring in progress....
/*void	*p_thread(void *void_philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->dieded))
	{
		philo_eats(philo);
		if (rules->all_ate)
			break ;
		action_print(rules, philo->id, "is sleeping");
		smart_sleep(rules->time_sleep, rules);
		action_print(rules, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}*/

int	main(int argc, char **argv)
{
	//t_table	table;
	t_philo	*philos;

	if (init_struct(argc, argv) == false)
		return (1);
	philos = get_data();
	pthread_mutex_init(&philos->mute_message, NULL);
	pthread_mutex_destroy(&philos->mute_message);
	pthread_mutex_destroy(philos->forks);
	return (0);
}
