/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:59:56 by malord            #+#    #+#             */
/*   Updated: 2022/11/04 10:39:38 by malord           ###   ########.fr       */
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
# include <limits.h>

typedef struct s_philo {
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eats;
	int				dead;
	int				all_ate;
	long long		f_timestamp;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_check;
	//t_table			philosophers[200];
}	t_philo;

typedef struct s_table {
	t_philo			*data_philo;
	pthread_mutex_t	mute_message;
}	t_table;

t_philo	*get_data(void);
long	ft_atol(const char *str);
int		ft_isdigit(int n);
int		ft_isspace(char c);
bool	conversions(int argc, char **argv);
bool	init_struct(int argc, char **argv);
void	*init_sim(void *arg);
void	*init_threads(int nb_philo);
void	*routine(void *arg);
t_table	*get_table(void);
bool	check_numbers(char **argv);
size_t	ft_strlen(const char *s);

#endif