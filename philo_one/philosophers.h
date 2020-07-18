/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 00:28:16 by anonymous      #+#    #+#                */
/*   Updated: 2020/03/20 00:28:16 by anonymous     ########   odam.nl         */
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
    int             *forks;
	pthread_mutex_t	dead;
    pthread_mutex_t write_lock;
    pthread_mutex_t eat_lock;
    int             isdead;
    uint64_t		start_time;
    // struct s_philo	*philo;
}               	t_data;

typedef struct      s_philo
{
	int				num;
    uint64_t		last_eaten;
	int				lfork;
	int				rfork;
    t_data          *data;
}                   t_philo;

size_t				ft_strlen(const char *s);
uint64_t			ft_atoi(const char *str);
void				ft_putlong_fd(uint64_t n, int fd);

#endif
