/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:59:56 by malord            #+#    #+#             */
/*   Updated: 2022/11/01 14:24:28 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo {
	int				nb_philos;
	pthread_mutex_t	*forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eats;
}	t_philo;

t_philo	*get_data(void);
int		ft_atoi(const char *str);
int		ft_isdigit(char c);
int		ft_isspace(char c);
bool	init_struct(int argc, char **argv);
void	*init_sim(void *arg);
void	*init_threads(int nb_philo);
void	*routine(void *arg);

#endif