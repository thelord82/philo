/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:59:56 by malord            #+#    #+#             */
/*   Updated: 2022/11/10 14:10:56 by malord           ###   ########.fr       */
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

struct	s_philo;

typedef struct s_table {
	struct s_philo	*data_philo;
	int				philo_id;
	int				x_ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		t_last_meal;
	pthread_t		thread_id;
}	t_table;

typedef struct s_philo {
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eats;
	int				dead;
	int				all_ate;
	long long		f_timestamp;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	mute_message;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	eat_check;
	pthread_mutex_t	mx_ate;
	pthread_mutex_t	dead_lock;
	struct s_table	philosophers[200];
}	t_philo;

bool		check_nb_eats(int argc, char **argv);
bool		check_numbers(char **argv);
bool		check_values(t_philo *philos);
bool		conversions(int argc, char **argv);
bool		init_rest(void);
bool		init_struct(int argc, char **argv);
int			ft_isdigit(int n);
int			ft_isspace(char c);
int			init_mutex(void);
int			init_philos(void);
int			philo_sim(void);
long		ft_atol(const char *str);
long long	time_diff(long long past, long long pres);
long long	timestamp(void);
size_t		ft_strlen(const char *s);
t_philo		*get_data(void);
t_table		*get_table(void);
void		action_print(int id, char *string);
void		dead_check(t_philo *phi, t_table *table);
void		del_data(void);
void		exit_sim(t_philo *philos, t_table *table);
void		*init_sim(void *arg);
void		*init_threads(int nb_philo);
void		kill_philo(t_philo *phi, t_table *table, int i);
void		lets_eat(t_table *table);
void		*routine_phi(void *void_philosopher);
void		smart_sleep(long long time);

#endif