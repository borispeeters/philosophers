/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 04:31:14 by anonymous     #+#    #+#                 */
/*   Updated: 2020/06/04 11:53:47 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include <stdio.h>




long	get_time(t_data *data)
{
	struct timeval	tv;
	long long		cur_time;

	gettimeofday(&tv, NULL);
	cur_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	// if (cur_time < data->start_time)
	// {
	// 	printf("YO WTH\nct: %lld\ndt: %ld\n", cur_time, data->start_time);
	// 	while (1);
	// }
	// cur_time = cur_time - data->start_time;
	// if (cur_time < 0)
	// {
	// 	printf("EYO WTF\nct: %lld\n", cur_time);
	// 	while (1);
	// }
	return (cur_time - data->start_time);
}

void	philo_write(t_philo *philo, char *str)
{
	t_data	*data;
	data = philo->data;
	pthread_mutex_lock(&data->write_lock);
	// write(1, "\n", 1);
	// if (data->isdead == 1)
	// 	write();
	// if (data->isdead == 2)
	// printf("data->isdead: %d\n", data->isdead);
	if (data->isdead < 2)
	{
		ft_putlong_fd(get_time(data), 1);
		write (1, "\t", 1);
		ft_putlong_fd(philo->num, 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		if (data->isdead == 1)
			data->isdead = 2;
	}
	pthread_mutex_unlock(&data->write_lock);
}

void	*monitor(void *v_philo)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo*)v_philo;
	data = philo->data;
	while (!data->isdead)
	{
		if (get_time(data) - philo->last_eaten > data->die_time)
		{
			data->isdead = 1;
			philo_write(philo, "died\n");
			// pthread_mutex_unlock(&data->dead);
			// usleep(10000);
		}
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
	philo->last_eaten = get_time(data);
	pthread_create(&pid, NULL, monitor, philo);
	while (!data->isdead)
	{
		philo_write(philo, "is thinking\n");
		pthread_mutex_lock(&(data->forks[philo->lfork]));
		philo_write(philo, "has taken a fork\n");
		pthread_mutex_lock(&(data->forks[philo->rfork]));
		philo_write(philo, "has taken a fork\n");

		philo->last_eaten = get_time(data);
		philo_write(philo, "is eating\n");
		usleep(data->eat_time * 1000);
		
		pthread_mutex_unlock(&(data->forks[philo->rfork]));
		pthread_mutex_unlock(&(data->forks[philo->lfork]));

		philo_write(philo, "is sleeping\n");
		usleep(data->sleep_time * 1000);
	}
	return (NULL);
}

void	philo_threads(t_data *data)
{
	pthread_t	*pt;
	t_philo		*philo;
	int			i;

	pt = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_num);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_num);
	philo = (t_philo*)malloc(sizeof(t_philo) * data->philo_num);
	i = 0;
	while (i < data->philo_num)
	{
		philo[i].data = data;
		philo[i].num = i;
		philo[i].lfork = i;
		philo[i].rfork = (i + 1) % data->philo_num;
		++i;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		++i;
	}
	// pthread_mutex_init(&data->dead, NULL);
	// pthread_mutex_lock(&data->dead);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_create(&(pt[i]), NULL, philosopher, &(philo[i]));
		++i;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(pt[i], NULL);
		++i;
	}
	i = 0;

	// pthread_mutex_lock(&data->dead);		
	// pthread_mutex_unlock(&data->dead);
	// pthread_mutex_destroy(&data->dead);
}

int	main(int argc, char **argv)
{
	t_data	data; 
	
	data.start_time = 0;
	data.start_time = get_time(&data);
	data.isdead = 0;
	if (argc == 5 || argc == 6)
	{
		data.philo_num = ft_atoi(argv[1]);
		data.die_time = ft_atoi(argv[2]);
		data.eat_time = ft_atoi(argv[3]);
		data.sleep_time = ft_atoi(argv[4]);
		data.eat_num = 0;
        printf("number_of_philosophers: %d\n", data.philo_num);
        printf("time_to_die: %d\n", data.die_time);
        printf("time_to_eat: %d\n", data.eat_time);
        printf("time_to_sleep: %d\n", data.sleep_time);
		if (argc == 6)
		{
			data.eat_num = ft_atoi(argv[5]);
			printf("amount_to_eat: %d\n", data.eat_num);
		}
		pthread_mutex_init(&data.write_lock, NULL);
		// pthread_mutex_init(&data.dead, NULL);
		// pthread_mutex_lock(&data.dead);
		philo_threads(&data);
		// pthread_mutex_lock(&data.dead);
		// pthread_mutex_unlock(&data.dead);
		int i = 0;
		while (i < data.philo_num)
		{
			pthread_mutex_destroy(&(data.forks[i]));
			++i;
		}
		// pthread_mutex_destroy(&data.dead);
		pthread_mutex_destroy(&data.write_lock);
        return (0);
	}
    printf("Invalid number of arguments\n");
	return (0);
}
