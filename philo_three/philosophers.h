/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 23:53:09 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/08/01 23:30:40 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include <stdint.h>

typedef enum	e_state
{
	ALIVE,
	DEAD
}				t_state;

typedef struct	s_data
{
	int			philo_count;
	uint64_t	die_time;
	uint64_t	eat_time;
	uint64_t	sleep_time;
	int			amount_to_eat;
	sem_t		*fork_sem;
	sem_t		*write_lock;
	sem_t		*eat_lock;
	sem_t		*dead_lock;
	pid_t		*pid;
	t_state		state;
	uint64_t	start_time;
}				t_data;

typedef struct	s_philo
{
	int			number;
	uint64_t	last_eaten;
	int			amount_eaten;
	t_data		*data;
}				t_philo;

/*
**	free_philo.c
*/

void			free_philo(t_philo **philo, t_data *data);

/*
**	ft_usleep.c
*/

void			ft_usleep(uint64_t wait_time);

/*
**	get_time.c
*/

uint64_t		get_time(void);

/*
**	initialize.c
*/

int				initialize_philo(t_data *data, t_philo **philo);
int				initialize_data(t_data *data, char **argv, int eat_condition);

/*
**	philo_eat.c
*/

void			philo_eat(t_philo *philo);

/*
**	philo_loop.c
*/

void			philo_loop(t_philo *philo);

/*
**	philo_write.c
*/

void			philo_write(t_philo *philo, char const *str);
void			unlocked_message(char const *str);

/*
**	philosophers.c
*/

void			philo_process(t_data *data, t_philo *philo);

/*
**	semaphore.c
*/

int				open_semaphores(t_data *data);
int				close_semaphores(t_data *data);

/*
**	utils.c
*/

uint64_t		ft_atoi(char const *str);
size_t			ft_strlen(char const *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putlong_fd(uint64_t n, int fd);

#endif
