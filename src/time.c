/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 08:57:48 by malord            #+#    #+#             */
/*   Updated: 2022/11/11 11:59:44 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time)
{
	long long	i;
	t_philo		*philos;

	philos = get_data();
	i = timestamp();
	while (1)
	{
		pthread_mutex_lock(&(philos->mute_message));
		if (philos->dead)
		{
			pthread_mutex_unlock(&(philos->mute_message));
			break ;
		}
		pthread_mutex_unlock(&(philos->mute_message));
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}
