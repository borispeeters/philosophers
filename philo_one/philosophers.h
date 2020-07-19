/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 14:55:24 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/19 14:55:24 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>

typedef struct		s_data
{
	int				philo_count;
	uint64_t		die_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	int				eat_num;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	eat_lock;
	int				isdead;
	uint64_t		start_time;
}					t_data;

typedef struct		s_philo
{
	int				num;
	uint64_t		last_eaten;
	int				eaten;
	int				lfork;
	int				rfork;
	t_data			*data;
}					t_philo;

/*
**	utils.c
*/

size_t				ft_strlen(const char *s);
uint64_t			ft_atoi(const char *str);
void				ft_putlong_fd(uint64_t n, int fd);

/*
**	get_time.c
*/

uint64_t			get_time(void);

/*
**	mutex.c
*/

void				initiate_mutexes(t_data *data);
void				destroy_mutexes(t_data *data);

/*
**	initialize.c
*/

int					initialize_philo(t_data *data, t_philo **philo, pthread_t **pt);
void				initialize_data(t_data *data, char **argv, int eat_condition);

/*
**	philo_write.c
*/

void				philo_write(t_philo *philo, char *str);

/*
**	philo_eat.c
*/

void				philo_eat(t_philo *philo);

/*
**	philosophers.c
*/

void				philo_threads(t_data *data, t_philo *philo, pthread_t *pt);

/*
**	philo_utils.c
*/

void				ft_usleep(uint64_t wait_time);
int					min(int lfork, int rfork);
int					max(int lfork, int rfork);

#endif
