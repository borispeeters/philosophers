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

typedef struct		s_data
{
    int				philo_num;
    int				die_time;
    int				eat_time;
    int				sleep_time;
    int				eat_num;
	
    pthread_mutex_t	*forks;
	pthread_mutex_t	dead;
    pthread_mutex_t write_lock;
    int             isdead;
    long			start_time;
    // struct s_philo	*philo;
}               	t_data;

typedef struct      s_philo
{
	int				num;
    long			last_eaten;
	int				lfork;
	int				rfork;
    t_data          *data;
}                   t_philo;

size_t	ft_strlen(const char *s);
int	    ft_atoi(const char *str);
void    ft_putlong_fd(int n, int fd);

#endif
