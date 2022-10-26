/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:36:05 by malord            #+#    #+#             */
/*   Updated: 2022/10/26 08:45:09 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*imprime()
{
	printf("Confiture\n");
	sleep(2);
	printf("Tarminé\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	test;

	if (pthread_create(&test, NULL, &imprime, NULL) != 0)
		return (1);
	if (pthread_join(test, NULL) != 0)
		return (2);
	return (0);
}
