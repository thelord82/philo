/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:36:26 by malord            #+#    #+#             */
/*   Updated: 2022/11/04 13:02:25 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
