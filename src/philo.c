/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:36:05 by malord            #+#    #+#             */
/*   Updated: 2022/10/26 11:13:38 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int bcp = 0;
pthread_mutex_t mutex;
void	*imprime_beaucoup()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		bcp++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);	
}

int	main(void)
{
	pthread_t	test, test2, test3;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&test, NULL, &imprime_beaucoup, NULL) != 0)
		return (1);
	if (pthread_create(&test2, NULL, &imprime_beaucoup, NULL) != 0)
		return (2);
	if (pthread_create(&test3, NULL, &imprime_beaucoup, NULL) != 0)
		return (5);
	if (pthread_join(test, NULL) != 0)
		return (3);
	if (pthread_join(test2, NULL) != 0)
		return (4);
	if (pthread_join(test3, NULL) != 0)
		return (6);
	printf("Valeur de bcp = %d\n", bcp);
	pthread_mutex_destroy(&mutex);
	return (0);
}
