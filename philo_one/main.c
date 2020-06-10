/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 04:31:14 by anonymous     #+#    #+#                 */
/*   Updated: 2020/06/10 08:47:39 by bpeeters      ########   odam.nl         */
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
		cur_time = get_time();
		// printf("\n\nget_time() = %llu, last_eaten = %llu\n\n", get_time(), philo->last_eaten);
		if ((cur_time - philo->last_eaten) > data->die_time)
		{
			philo_write(philo, "lol\n");
			printf("\n\ncur_time = %llu, last_eaten = %llu, die_time = %llu\n\n", cur_time, philo->last_eaten, data->die_time);
			printf("\n\ncur_time - last_eaten = %llu\n\n", cur_time - philo->last_eaten);
			pthread_mutex_lock(&data->dead);
			philo_write(philo, "died\n");
			data->isdead = 1;
			pthread_mutex_unlock(&data->dead);
		}
		// usleep(100);
	}
	return (NULL);
}

void	*philosopher(void *v_philo)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	pid;

	philo = (t_philo*)v_philo;
	data = philo->data;
	philo->last_eaten = get_time();
	pthread_create(&pid, NULL, monitor, philo);
	philo->lfork_bool = 0;
	philo->rfork_bool = 0;
	philo_write(philo, "is thinking\n");
	while (!data->isdead)
	{

		pthread_mutex_lock(&(data->fork_mutex[philo->lfork_i]));
		if (data->forks[philo->lfork_i] == 0 && philo->lfork_bool == 0)
		{
			data->forks[philo->lfork_i] = 1;
			philo->lfork_bool = 1;
			philo_write(philo, "has taken a left fork\n");
		}
		pthread_mutex_unlock(&(data->fork_mutex[philo->lfork_i]));
		pthread_mutex_lock(&(data->fork_mutex[philo->rfork_i]));
		if (data->forks[philo->rfork_i] == 0 && philo->rfork_bool == 0)
		{
			data->forks[philo->rfork_i] = 1;
			philo->rfork_bool = 1;
			philo_write(philo, "has taken a right fork\n");
		}
		pthread_mutex_unlock(&(data->fork_mutex[philo->rfork_i]));
		
		if (philo->lfork_bool == 0 || philo->rfork_bool == 0)
			continue ;

		philo->last_eaten = get_time();
		philo_write(philo, "is eating\n");
		usleep(data->eat_time * 1000);
		data->forks[philo->lfork_i] = 0;
		philo->lfork_bool = 0;
		data->forks[philo->rfork_i] = 0;
		philo->rfork_bool = 0;
		philo_write(philo, "is sleeping\n");
		usleep(data->sleep_time * 1000);
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
		philo[i].lfork_i = i;
		philo[i].rfork_i = (i + 1) % data->philo_count;
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
		philo_threads(&data);
		int i = 0;
		while (i < data.philo_count)
		{
			pthread_mutex_destroy(&(data.fork_mutex[i]));
			++i;
		}
		pthread_mutex_destroy(&data.dead);
		pthread_mutex_destroy(&data.write_lock);
        return (0);
	}
    printf("Invalid number of arguments\n");
	return (0);
}
