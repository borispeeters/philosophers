/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 21:43:03 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/31 21:45:00 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>

typedef enum		e_state
{
	ALIVE,
	DEAD
}					t_state;

typedef struct		s_data
{
	int				philo_count;
	uint64_t		die_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	int				amount_to_eat;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	eat_lock;
	t_state			state;
	uint64_t		start_time;
}					t_data;

typedef struct		s_philo
{
	int				number;
	uint64_t		last_eaten;
	int				amount_eaten;
	int				lfork;
	int				rfork;
	t_data			*data;
}					t_philo;

/*
**	utils.c
*/

size_t				ft_strlen(char const *s);
uint64_t			ft_atoi(char const *str);
void				ft_putlong_fd(uint64_t n, int fd);

/*
**	get_time.c
*/

uint64_t			get_time(void);

/*
**	mutex.c
*/

int					initiate_mutexes(t_data *data);
void				destroy_mutexes(t_data *data, int length);

/*
**	initialize.c
*/

int					initialize_philo(t_data *data, t_philo **philo,
									pthread_t **pt);
int					initialize_data(t_data *data, char **argv,
									int eat_condition);

/*
**	philo_write.c
*/

void				philo_write(t_philo *philo, char const *str);
void				unlocked_message(char const *str);

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
int					first_fork(t_philo *philo);
int					second_fork(t_philo *philo);

/*
**	free_philo.c
*/

void				free_philo(t_data *data, t_philo **philo, pthread_t **pt);

#endif
