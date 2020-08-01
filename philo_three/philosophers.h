/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 23:53:09 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/31 23:57:12 by bpeeters      ########   odam.nl         */
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


#endif
