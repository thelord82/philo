/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:33:44 by malord            #+#    #+#             */
/*   Updated: 2022/11/10 10:57:42 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*get_data(void)
{
	static t_philo	*data = NULL;

	if (data == NULL)
		data = (t_philo *)malloc(sizeof(t_philo));
	return (data);
}

t_table	*get_table(void)
{
	static t_table	*data = NULL;

	if (data == NULL)
		data = (t_table *)malloc(sizeof(t_table));
	return (data);
}

void	del_data(void)
{
	t_philo	*philos;
	t_table	*table;

	philos = get_data();
	table = get_table();
	if (philos)
		free(philos);
	if (table)
		free(table);
	return ;
}
