/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 04:31:14 by anonymous     #+#    #+#                 */
/*   Updated: 2020/06/11 11:32:01 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include <stdio.h>



uint64_t	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void		philo_write(t_philo *philo, char *str)
{
	t_data	*data;
	data = philo->data;
	pthread_mutex_lock(&data->write_lock);
	if (data->isdead != 1)
	{
		ft_putlong_fd(get_time() - data->start_time, 1);
		write (1, "\t", 1);
		ft_putlong_fd(philo->num, 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
	}
	pthread_mutex_unlock(&data->write_lock);
}

void	*monitor(void *v_philo)
{
	t_data		*data;
	t_philo		*philo;
	uint64_t	cur_time;
	
	philo = (t_philo*)v_philo;
	data = philo->data;
	while (!data->isdead)
	{
		pthread_mutex_lock(&data->eat_lock);
		cur_time = get_time();
		if ((get_time() - philo->last_eaten) > data->die_time)
		{
			// pthread_mutex_lock(&data->dead);
			philo_write(philo, "died\n");
			data->isdead = 1;
			// pthread_mutex_unlock(&data->dead);
		}
		pthread_mutex_unlock(&data->eat_lock);
		usleep(100);
	}
	return (NULL);
}

void	ft_usleep(uint64_t wait_time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < wait_time)
		usleep(100);
}

void	philo_take_fork(t_philo *philo, int ifork)
{
	if (pthread_mutex_lock(&(philo->data->fork_mutex[ifork])) != 0)
		return ;
	philo->data->forks[ifork] = 1;
	philo_write(philo, "has taken a fork\n");
}

static int		min(int lfork, int rfork)
{
	if (lfork < rfork)
		return lfork;
	else
		return rfork;
	
}

static int		max(int lfork, int rfork)
{
	if (lfork > rfork)
		return lfork;
	else
		return rfork;
	
}

void	*philosopher(void *v_philo)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	pid;
	int	first_fork;
	int	second_fork;

	philo = (t_philo*)v_philo;
	data = philo->data;
	philo->last_eaten = get_time();
	pthread_create(&pid, NULL, monitor, philo);
	first_fork = min(philo->lfork, philo->rfork);
	second_fork = max(philo->lfork, philo->rfork);
	philo_write(philo, "is thinking\n");
	while (!data->isdead)
	{
		philo_take_fork(philo, first_fork);
		philo_take_fork(philo, second_fork);

		pthread_mutex_lock(&data->eat_lock);
		philo_write(philo, "is eating\n");
		philo->last_eaten = get_time();
		pthread_mutex_unlock(&data->eat_lock);
		ft_usleep(data->eat_time);

		pthread_mutex_unlock(&(data->fork_mutex[first_fork]));
		pthread_mutex_unlock(&(data->fork_mutex[second_fork]));


		philo_write(philo, "is sleeping\n");
		ft_usleep(data->sleep_time);
		philo_write(philo, "is thinking\n");
	}
	pthread_join(pid, NULL);
	return (NULL);
}

void	philo_threads(t_data *data)
{
	pthread_t	*pt;
	t_philo		*philo;
	int			i;

	pt = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_count);
	data->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_count);
	data->forks = (int*)malloc(sizeof(int) * data->philo_count);
	memset(data->forks, 0, data->philo_count * 4);

	
	philo = (t_philo*)malloc(sizeof(t_philo) * data->philo_count);
	i = 0;
	while (i < data->philo_count)
	{
		philo[i].data = data;
		philo[i].num = i + 1;
		philo[i].lfork = i;
		philo[i].rfork = (i + 1) % data->philo_count;
		++i;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&(data->fork_mutex[i]), NULL);
		++i;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_create(&(pt[i]), NULL, philosopher, &(philo[i]));
		++i;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(pt[i], NULL);
		++i;
	}
	i = 0;
}

int	main(int argc, char **argv)
{
	t_data	data; 
	
	data.start_time = get_time();
	data.isdead = 0;
	if (argc == 5 || argc == 6)
	{
		data.philo_count = ft_atoi(argv[1]);
		data.die_time = ft_atoi(argv[2]);
		data.eat_time = ft_atoi(argv[3]);
		data.sleep_time = ft_atoi(argv[4]);
		data.eat_num = 0;
        printf("number_of_philosophers: %d\n", data.philo_count);
        printf("time_to_die: %llu\n", data.die_time);
        printf("time_to_eat: %llu\n", data.eat_time);
        printf("time_to_sleep: %llu\n", data.sleep_time);
		if (argc == 6)
		{
			data.eat_num = ft_atoi(argv[5]);
			printf("amount_to_eat: %d\n", data.eat_num);
		}
		pthread_mutex_init(&data.write_lock, NULL);
		pthread_mutex_init(&data.dead, NULL);
		pthread_mutex_init(&data.eat_lock, NULL);
		philo_threads(&data);
		int i = 0;
		while (i < data.philo_count)
		{
			pthread_mutex_destroy(&(data.fork_mutex[i]));
			++i;
		}
		pthread_mutex_destroy(&data.eat_lock);
		pthread_mutex_destroy(&data.dead);
		pthread_mutex_destroy(&data.write_lock);
        return (0);
	}
    printf("Invalid number of arguments\n");
	return (0);
}
