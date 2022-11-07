/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:59:56 by malord            #+#    #+#             */
/*   Updated: 2022/11/07 10:47:44 by malord           ###   ########.fr       */
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

typedef struct s_table	t_table;

typedef struct s_philo {
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eats;
	int				dead;
	int				all_ate;
	int				philo_id;
	long long		f_timestamp;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	mute_message;
	pthread_mutex_t	meal_check;
	t_table			*philosophers;
}	t_philo;

typedef struct s_table {
	t_philo			*data_philo;
	int				philo_id;
	int				x_ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		t_last_meal;
	pthread_t		thread_id;
}	t_table;

t_philo		*get_data(void);
bool		check_numbers(char **argv);
bool		conversions(int argc, char **argv);
bool		init_struct(int argc, char **argv);
int			ft_isdigit(int n);
int			ft_isspace(char c);
int			init_mutex(void);
int			init_philos(void);
long		ft_atol(const char *str);
size_t		ft_strlen(const char *s);
t_table		*get_table(void);
void		*init_sim(void *arg);
void		*init_threads(int nb_philo);
void		*routine(void *arg);
void		smart_sleep(long long time);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
bool		init_rest(void);
int			philo_sim(void);
void		dead_check(void);
void		exit_sim(void);
void		lets_eat(void);
void		action_print(int id, char *string);
void		*p_thread(void *void_philosopher);

#endif